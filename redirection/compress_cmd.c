/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 14:21:43 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/04 14:53:04 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** edit the cmd array for smooth multi redirection
*/

#include "header.h"

void			compress_cmd(char **cmd, int i)
{
	int			j;

	j = i + 1;
	while (cmd[j] && !ft_strchr(cmd[j], '>') && !ft_strchr(cmd[j], '<')\
			&& !ft_strchr(cmd[j], '|'))
		j++;
	j = cmd[j] ? j - 1 : 0;
	i = j ? i - 1 : i;
	while (j && cmd[i++ + j])
		cmd[i] = cmd[i + j];
	i--;
	while (cmd[++i])
		cmd[i] = NULL;
}
