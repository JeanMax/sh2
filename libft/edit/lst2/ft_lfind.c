/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 04:58:45 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/13 04:34:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retourne l’adresse du premier élément dont la donnée est
** "égale" à la donnée de référence
*/

#include "libft.h"

t_lst *ft_lfind(t_lst **alst, char *data)
{
	t_lst	*tmp;

	if (!alst || !data)
		return (NULL);
	tmp = *alst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env, data))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
