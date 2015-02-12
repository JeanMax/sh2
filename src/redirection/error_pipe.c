/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 23:21:24 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/12 19:49:46 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stderr pipe handler (|&)
** this is also redirecting stdout
*/

#include "header.h"

extern pid_t	g_pid2;

static void		child(int *pipe_fd, char **cmd2, t_env *e)
{
	int			save_fd0;

	save_fd0 = dup(0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	launch_cmd(cmd2, e);
	dup2(save_fd0, 0);
	close(save_fd0);
	exit(0);
}

static void		father(int *pipe_fd, char **cmd1, t_env *e)
{
	int			save_fd1;
	int			save_fd2;

	save_fd1 = dup(1);
	save_fd2 = dup(2);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	dup2(pipe_fd[1], 2);
	close(pipe_fd[1]);
	launch_cmd(cmd1, e);
	dup2(save_fd1, 1);
	dup2(save_fd2, 2);
	close(save_fd1);
	close(save_fd2);
	wait(NULL);
}

static void		fork_that(char **cmd1, char **cmd2, t_env *e)
{
	int			pipe_fd[2];

	pipe(pipe_fd) < 0 ? error("Pipe", NULL) : NULL;
	(g_pid2 = fork()) < 0 ? error("Fork", NULL) : NULL;
	if (!g_pid2)
		child(pipe_fd, cmd2, e);
	else
		father(pipe_fd, cmd1, e);
}

void			error_pipe(char **cmd, t_env *e)
{
	int			i;
	char		**new_cmd;

	//cmd = check_cmd(cmd); //TODO
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "|&"))
		i++;
	if (!ft_strcmp(cmd[0], "|&") || !cmd[i + 1])
		ft_putendl_fd("Invalid null command.", 2);
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], "|&"))
		return ;
	new_cmd = ft_cpystab(&cmd[i + 1], NULL);
	while (cmd[i])
		ft_memdel((void *)&cmd[i++]);
	fork_that(cmd, new_cmd, e);
	ft_freestab(new_cmd);
}
