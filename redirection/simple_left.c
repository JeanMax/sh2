/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:20 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/26 00:07:07 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** input redirection (<) handler
** usage : "cmd < file"
*/

#include "header.h"

void    simple_left(char **cmd, t_env *e)
{
    cmd = cmd;
    e = e;
    ft_debugstr("simple_left", "hey!");
}
