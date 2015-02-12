/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:29 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/12 20:04:23 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** here document (<<) handler
*/

#include "header.h"

extern pid_t		g_pid2;

static void			fork_that(char **cmd, t_env *e, int *pipe_fd, char *all)
{
	int				save_fd0;
	int				save_fd1;

	((g_pid2 = fork()) < 0) ? error("Fork", NULL) : NULL;
	if (!g_pid2)
	{
		save_fd0 = dup(0);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		launch_cmd(cmd, e);
		dup2(save_fd0, 0);
		close(save_fd0);
		exit(0);
	}
	else
	{
		save_fd1 = dup(1);
		close(pipe_fd[0]);
		ft_putstr_fd(all, pipe_fd[1]);
		close(pipe_fd[1]);
		dup2(save_fd1, 1);
		close(save_fd1);
		wait(NULL);
	}
}

static int			get_that_line(int const fd, char **a)
{
	int				i;
	int				stop;
	int				n;
	char			buf[BUFF_SIZE];

	if (!a || fd < 0)
		return (0);
	n = 0;
	*a = ft_strnew(1);
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

static void			get_text(char **a, char *here)
{
	char			*tmp;
	char			*to_free;
	size_t			len;

	to_free = ft_strjoin(here, "\n");
	*a = ft_strnew(1);
	ft_putstr("? ");
	while (get_that_line(0, &tmp) && ft_strcmp(tmp, to_free))
	{
		ft_putstr("? ");
		len = ft_strlen(*a);
		*a = (char *)ft_realloc((void *)*a, len, len + ft_strlen(tmp));
		ft_strcat(*a, tmp);
		ft_memdel((void *)&tmp);
	}
	ft_memdel((void *)&tmp);
	ft_memdel((void *)&to_free);
}

static void			compress_cmd(char **cmd, int i)
{
	int				j;

	j = i + 1;
	while (cmd[j] && !ft_strchr(cmd[j], '>') && !ft_strchr(cmd[j], '<')\
			&& !ft_strchr(cmd[j], '|'))
		j++;
	j = cmd[j] ? j - i : 0;
	i = j ? i - 1 : i;
	while (j && cmd[i++ + j])
		cmd[i] = cmd[i + j];
	while (cmd[i])
		ft_memdel((void *)&cmd[i++]);
}

void				doble_left(char **cmd, t_env *e)
{
	int				i;
	char			*all;
	int				pipe_fd[2];

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
	get_text(&all, cmd[i + 1]);
	compress_cmd(cmd, i);
	pipe(pipe_fd) < 0 ? error("Pipe", NULL) : NULL;
	fork_that(cmd, e, pipe_fd, all);
	ft_memdel((void *)&all);
}
