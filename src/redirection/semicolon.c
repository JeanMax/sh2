/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:47:57 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/11 00:54:11 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handle splitting commands around ";" semicolon
*/

#include "header.h"

void	semicolon(char *line, t_env *e)
{
	char	**sc_tab;
	char	**cmd;
	int		i;

	sc_tab = ft_strsplit(line, ';');
	i = 0;
	while (sc_tab[i])
	{
		cmd = split_it(sc_tab[i]);
		launch_cmd(cmd, e);
		ft_freestab(cmd);
		i++;
	}
	ft_freestab(sc_tab);
	ft_memdel((void *)&line);
}
