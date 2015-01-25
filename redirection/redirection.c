/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/26 00:07:56 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriate redirection function
*/

#include "header.h"

void	redirect(char **cmd, t_env *e, int i)
{
	while (cmd[i])
		if (ft_strstr(cmd[i], ">>"))
		{
			double_right(cmd, e);
			return ;
		}
		else if (ft_strstr(cmd[i], "<<"))
		{
			double_left(cmd, e);
			return ;
		}
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