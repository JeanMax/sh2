/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:44 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/28 17:18:54 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** append output (>>) handler
** usage : "cmd >> file"
*/

#include "header.h"

static void	check_error(char **cmd, char *pgm)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_strcmp(">>", cmd[i - 1]) && ft_strcmp(">>", cmd[i]))
		{
			ft_putstr_fd(pgm, 2);
			if (!ft_strcmp("ls", pgm))
			{
				ft_putstr_fd(": cannot access ", 2);
			}
			else
				ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd(": No such file or directory ", 2);
		}
		i++;
	}
}

static char	**check_cmd(char **cmd)
{
	int	i;
	int	j;
	int	ac;

	cmd = spaces_error(cmd, ">>");
	ac = 0;
	while (cmd[ac])
		ac++;
	i = 0;
	while (cmd[i] && ft_strcmp(">>", cmd[i]))
		i++;
	check_error(&cmd[i], cmd[0]);
	j = ac - 1;
	while (cmd[j] && ft_strcmp(">>", cmd[j]))
		j--;
	if (i == j)
		return (cmd);
	cmd[i + 1] = cmd[j + 1];
	i += 2;
	while (cmd[i])
	{
		cmd[i] = NULL;
		i++;
	}
	return (cmd);
}

void	doble_right(char **cmd, t_env *e)
{
	int		file_fd;
	int		base_fd;
	int		i;

	cmd = check_cmd(cmd);
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], ">>"))
		i++;
	if (!cmd[i + 1])
		ft_putendl_fd("Missing name for redirect.", 2);
	else if (!ft_strcmp(cmd[0], ">>"))
		ft_putendl_fd("Invalid null command.", 2);
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], ">>"))
		return ;
	if ((file_fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664)) < 0)
		error("open", cmd[i + 1]);
	i--;
	while (cmd[++i])
		cmd[i] = NULL;
	base_fd = dup(1);
	dup2(file_fd, 1);
	launch_cmd(cmd, e);
	dup2(base_fd, 1);
	close(file_fd);
	close(base_fd);
}
