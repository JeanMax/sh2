/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 08:00:25 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/28 17:40:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriatte builtin function
*/

#include "header.h"

static void	handle_echo(char **av, t_env *e)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '$')
			av[i] = get_env(av[i] + 1, e);
		i++;
	}
	fork_it(av, e);
}

int			is_builtin(char **cmd, t_env *e)
{
	int		i;

	i = 7;
	while (i && cmd[0] && ft_strcmp((e->builtin)[i - 1], cmd[0]))
		i--;
	return (i ? 1 : 0);
}

void		launch_builtin(char **av, t_env *e)
{
	if (!ft_strcmp(av[0], "echo"))
		handle_echo(av, e);
	else if (!ft_strcmp(av[0], "exit"))
		ft_exit(0, av);
	else if (!ft_strcmp(av[0], "env"))
		ft_env(av, e);
	else if (!ft_strcmp(av[0], "unsetenv"))
		ft_unsetenv(av, e);
	else if (!ft_strcmp(av[0], "setenv"))
		ft_setenv(av, e);
	else if (!ft_strcmp(av[0], "cd"))
		ft_cd(av, e);
}
