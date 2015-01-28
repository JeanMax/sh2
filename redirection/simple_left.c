/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:20 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/28 20:46:31 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** input redirection (<) handler
** usage : "cmd < file"
*/

#include "header.h"

extern pid_t	g_pid2;

static void		fork_that(char **cmd, t_env *e, char *all)
{
	int			pipe_fd[2];

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

void			simple_left(char **cmd, t_env *e)
{
	int			i;
	int			file_fd;
	char		*all;

	//cmd = check_cmd(cmd); //TODO
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "<"))
		i++;
	if (!cmd[i + 1])
		ft_putendl_fd("Missing name for redirect.", 2);
	else if (!ft_strcmp(cmd[0], "<"))
		ft_putendl_fd("Invalid null command.", 2);
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], "<"))
		return ;
	if ((file_fd = open(cmd[i + 1], O_RDONLY)) < 0)
		error("open", cmd[i + 1]); //to edit
	i--;
	while (cmd[++i])
		cmd[i] = NULL;
	get_all(file_fd, &all); //check return ?
	close(file_fd);
	fork_that(cmd, e, all);
	ft_memdel((void *)&all);
}
