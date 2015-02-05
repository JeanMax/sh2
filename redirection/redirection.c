/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/05 17:48:38 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriate redirection function
*/

#include "header.h"

void	redirect(char **cmd, t_env *e, int i)
{
	while (cmd[i])
	{
		ft_strstr(cmd[i], ">>") ? doble_right(cmd, e) : NULL;
		ft_strstr(cmd[i], "<<") ? doble_right(cmd, e) : NULL;
		if (ft_strstr(cmd[i], ">>") || ft_strstr(cmd[i], "<<"))
			return ;
		else if (ft_strchr(cmd[i], '>'))
		{
			simple_right(cmd, e);
			return ;
		}
		else if (ft_strchr(cmd[i], '<'))
		{
			simple_left(cmd, e);
			return ;
		}
		else if (ft_strchr(cmd[i++], '|'))
		{
			simple_pipe(cmd, e);
			return ;
		}
	}
}
