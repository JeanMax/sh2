/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:08:46 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/05 19:17:06 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipe (|) handler
** usage "cmd | cmd"
*/

#include "header.h"

extern pid_t	g_pid2;

static void		fork_that(char **cmd1, char **cmd2, int *pipe_fd, t_env *e)
{
	int			save_fd0;
	int			save_fd1;

	if (!g_pid2)
	{
		save_fd0 = dup(0);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		launch_cmd(cmd2, e);
		dup2(save_fd0, 0);
		close(save_fd0);
		exit(0);
	}
	else
	{
		save_fd1 = dup(1);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		launch_cmd(cmd1, e);
		dup2(save_fd1, 1);
		close(save_fd1);
		wait(NULL);
	}
}

void			simple_pipe(char **cmd, t_env *e)
{
	int		i;
	char	**new_cmd;
	int		pipe_fd[2];

	//cmd = check_cmd(cmd); //TODO
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
		i++;
	if (!ft_strcmp(cmd[0], "|") || !cmd[i + 1])
		ft_putendl_fd("Invalid null command.", 2);
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], "|"))
		return ;
	new_cmd = cpy_env(&cmd[i + 1], NULL);
	i--;
	while (cmd[++i])
		cmd[i] = NULL;
	pipe(pipe_fd) < 0 ? error("Pipe", NULL) : NULL;
	(g_pid2 = fork()) < 0 ? error("Fork", NULL) : NULL;
	fork_that(cmd, new_cmd, pipe_fd, e);
	ft_freetab(new_cmd);
}
