/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 22:07:36 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/13 04:32:46 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne un maillon “frais”. Les champs content
** et content_size du nouveau maillon sont initialisés par copie des paramètr
** de la fonction. Si le paramètre content est nul, le champs content es
** initialisé à NULL et le champs content_size est initialisé à 0 que
** la valeur du paramètre content_size. Le champ next est initialisé à N.
** Si l’allocation échoue, la fonction renvoie NULL
*/

#include "libft.h"
#include <stdlib.h>

t_lst	*ft_lnew(char *env_var)
{
	t_lst	*new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	if (env_var)
		if (!(new->env = ft_strdup(env_var)))
			return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
