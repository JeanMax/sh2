/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 21:32:33 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/25 00:04:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** execute commands and signal handling
** also managing the prompt loop
*/

#include "header.h"

pid_t			g_pid1;
pid_t			g_pid2;
t_env			*g_env;

void			call_execve(char **cmd, t_env *e)
{
	int		i;
	char	*join;
	char	*tmp;

	if (!(g_pid2 = fork()))
	{
		if ((execve(cmd[0], cmd, e->env)) < 0)
		{
			(cmd[0][0] == '.' && cmd[0][1] == '/') ? error("exe", cmd[0]) : 0;
			i = 0;
			while ((e->path)[i])
			{
				tmp = ft_strjoin((e->path)[i++], "/");
				join = ft_strjoin(tmp, cmd[0]);
				ft_memdel((void *)&tmp);
				execve(join, cmd, e->env) >= 0 ? ft_memdel((void *)&join) : 0;
				if ((execve(join, cmd, e->env)) >= 0)
					break ;
				ft_memdel((void *)&join);
			}
			error("cmd", cmd[0]);
		}
	}
	else
		wait(NULL);
}

static void		sig_handl(int sig)
{
	if (sig == SIGBUS)
		error("bus", NULL);
	else if (sig == SIGSEGV)
		error("seg", NULL);
	else if (sig == SIGFPE)
		error ("fpe", NULL);
	else if (sig == SIGINT)
	{
		ft_putstr("\b \b\b \b\n");
		if (g_pid1 == g_pid2 || !g_pid1)
			prompt(g_env);
		g_pid1 = g_pid2;
	}
	else if (sig == 29)
		prompt(g_env);
}

void	init(int ac, char **ae, t_env *e)
{
	ac > 1 ? error("arg", NULL) : 0;
	signal(SIGINT, sig_handl);
	signal(SIGFPE, sig_handl);
	signal(29, sig_handl);
	signal(SIGSEGV, sig_handl);
	signal(SIGBUS, sig_handl);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	e->env = ae;
	get_path(e);
	get_builtin(e);
	g_env = e;
	ft_putstr("\033[2J\033[1;1H");
}

void		launch_cmd(char **cmd, t_env *e)
{
	int	i;

	i = 0;
	while (cmd[i])
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<')\
			|| ft_strchr(cmd[i++], '|'))
		{
			redirect(cmd, e);
			return ;
		}
	i = 7;
	while (i && cmd[0] && ft_strcmp((e->builtin)[i - 1], cmd[0]))
		i--;
	i ? launch_builtin(i, &cmd[0], e) : NULL;
	cmd && !i ? call_execve(&cmd[0], e) : NULL;
}

void		prompt_loop(char **av, t_env *e)
{
	char	*line;
	char	**cmd;

	while (42)
	{
		prompt(e);
		g_pid1 = g_pid2;
		get_line(0, &line) ? NULL : ft_exit(0, av);
		if (ft_strindex(line, ';') != -1)
		{
			semicolon(line, e);
			continue ;
		}
		cmd = ft_strsplit(line, ' ');		
		launch_cmd(cmd, e);
		ft_memdel((void *)&line);
		ft_freetab(cmd);
	}
}
