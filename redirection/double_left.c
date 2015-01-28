/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:29 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/28 23:26:51 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** here document (<<) handler
*/

#include "header.h"

extern pid_t	g_pid2;

static void		fork_that(char **cmd, t_env *e, char *all)
{
	int		pipe_fd[2];

	pipe(pipe_fd) < 0 ? error("Pipe", NULL) : NULL;
	if ((g_pid2 = fork()) < 0)
		error("Fork", NULL);
	else if (!g_pid2)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		is_builtin(cmd, e) ? launch_builtin(cmd, e) : call_execve(cmd, e);
	}
	else
	{
		close(pipe_fd[0]);
		ft_putstr_fd(all, pipe_fd[1]);
		close(pipe_fd[1]);
		wait(NULL);
	}
}

static int	get_that_line(int const fd, char **a)
{
	int		i;
	int		stop;
	int		n;
	char	buf[BUFF_SIZE];

	if (!a || fd < 0)
		return (0);
	*a = ft_strnew(1);
	n = 0;
	while ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		*a = (char *)ft_realloc((void *)*a, ft_strlen(*a), ft_strlen(*a) + i);
		ft_strcat(*a, buf);
		if ((stop = ft_strindex(*a, '\n')) != -1)
		{
			n = 1;
			break ;
		}
	}
	*a = ft_realloc((void *)*a, ft_strlen(*a), stop + 1);
	if (!*a || i < 0 || !n)
		return (0);
	return (1);
}

static void	get_text(char **a, char *here)
{
	char	*tmp;
	char	*to_free;
	int		len;

	to_free = ft_strjoin(here, "\n"); //tofree
	while (get_that_line(0, &tmp))
	{
		if (!ft_strcmp(tmp, to_free))
		{
			ft_memdel((void *)&to_free);
			break ;
		}
		len = ft_strlen(*a);
		*a = ft_realloc((void *)*a, len, len + ft_strlen(tmp));
		ft_strcat(*a, tmp);
	}
	ft_memdel((void *)&to_free);
}

void		doble_left(char **cmd, t_env *e)
{
	int			i;
	char		*all;

	//cmd = check_cmd(cmd); //TODO
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "<<"))
		i++;
	if (!cmd[i + 1])
		ft_putendl_fd("Missing name for redirect.", 2);
	else if (!ft_strcmp(cmd[0], "<<"))
		ft_putendl_fd("Invalid null command.", 2);
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], "<<"))
		return ;
	get_text(&all, cmd[i + 1]); //check return ?
	i--;
	while (cmd[++i])
		cmd[i] = NULL;
	fork_that(cmd, e, all + 2);
	ft_memdel((void *)&all);
}
