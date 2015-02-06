/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/06 22:16:15 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriate redirection function
*/

#include "header.h"

void	redirect(char **c, t_env *e, int i)
{
	while (c[i])
	{
		if (ft_strchr(c[i], '>'))
		{
			ft_strstr(c[i], ">>") ? doble_right(c, e) : simple_right(c, e);
			return ;
		}
		else if (ft_strchr(c[i], '<'))
		{
			ft_strstr(c[i], "<<") ? doble_left(c, e) : simple_left(c, e);
			return ;
		}
		else if (ft_strchr(c[i++], '|'))
		{
			simple_pipe(c, e);
			return ;
		}
	}
}
