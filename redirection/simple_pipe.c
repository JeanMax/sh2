/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:08:46 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/28 21:01:23 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipe (|) handler
** usage "cmd | cmd"
*/

#include "header.h"

extern pid_t	g_pid2;

static void		fork_that(char **cmd1, char **cmd2, t_env *e)
{
	int			pipe_fd[2];

	(pipe(pipe_fd) < 0) ? error("Pipe", NULL) : NULL;
	if ((g_pid2 = fork()) < 0)
		error("Fork", NULL);
	else if (!g_pid2)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		is_builtin(cmd2, e) ? launch_builtin(cmd2, e) : call_execve(cmd2, e);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		is_builtin(cmd1, e) ? launch_builtin(cmd1, e) : call_execve(cmd1, e);
		wait(NULL);
	}
}

void		simple_pipe(char **cmd, t_env *e)
{
	int		i;
	char	**new_cmd;

	//cmd = check_cmd(cmd); //TODO
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
		i++;
	if (!cmd[i + 1])
		ft_putendl_fd("Missing name for redirect.", 2);
	else if (!ft_strcmp(cmd[0], "|"))
		ft_putendl_fd("Invalid null command.", 2);
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], "|"))
		return ;
	new_cmd = cpy_env(&cmd[i + 1], NULL);
	i--;
	while (cmd[++i])
		cmd[i] = NULL;
	fork_that(cmd, new_cmd, e);
	ft_freetab(new_cmd);
}
