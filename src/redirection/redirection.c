/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/12 01:23:32 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriate redirection function
*/

#include "header.h"

static	char **check_cmd(char **c)
{
	if (!need_space(c))
		return (c);
	return (spaces_error(c));
}

void	redirect(char **c, t_env *e, int i)
{
	c = check_cmd(c);
	while (c[++i])
		if (ft_strchr(c[i], '>'))
		{
			if (ft_strstr(c[i], ">>&"))
				error_d_right(c, e);
			else if (ft_strchr(c[i], '&'))
				error_s_right(c, e);
			else
				ft_strstr(c[i], ">>") ? doble_right(c, e) : simple_right(c, e);
			return ;
		}
		else if (ft_strchr(c[i], '<'))
		{
			ft_strstr(c[i], "<<") ? doble_left(c, e) : simple_left(c, e);
			return ;
		}
		else if (ft_strchr(c[i], '|'))
		{
			ft_strstr(c[i], "|&") ? error_pipe(c, e) : simple_pipe(c, e);
			return ;
		}
}
