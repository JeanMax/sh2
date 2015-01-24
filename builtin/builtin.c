/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 08:00:25 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/24 22:59:44 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriatte builtin function
** b: cd = 1, setenv = 2, unsetenv = 3, env = 4, exit = 5, echo = 6;
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
	call_execve(av, e);
}

void		launch_builtin(int b, char **av, t_env *e)
{
	if (b == 6)
		handle_echo(av, e);
	else if (b == 5)
		ft_exit(0, av);
	else if (b == 4)
		ft_env(av, e);
	else if (b == 3)
		ft_unsetenv(av, e);
	else if (b == 2)
		ft_setenv(av, e);
	else if (b == 1)
		ft_cd(av, e);
}
