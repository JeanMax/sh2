/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 18:44:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/05 17:58:01 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handle spaces error in cmd tabs :
** "X>", "Y" wille be corrected in "X", ">", "Y"
** same idea for ">Y" and "X>Y"
** also working for any other str than ">" (basically ">>", ">", "|", "<", "<<")
*/

#include "header.h"

static int	spaces_error_aux_b(char **cmd, char **new_cmd, char *c)
{
	int	k;

	while (cmd[0][k] && cmd[0][k] != c[0])
		k++;
	new_cmd[0] = ft_strdup(cmd[0]);
	new_cmd[0][k] = '\0';
	new_cmd[1] = ft_strdup(c);
	new_cmd[2] = ft_strdup(cmd[0] + k + (c[1] ? 2 : 1));
	return (2);
}

static void	spaces_error_aux_a(char **cmd, char **new_cmd, char *c)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[i], c[0]))
			new_cmd[j] = ft_strdup(cmd[i]);
		else if (ft_strindex(cmd[i], c[0]) == 0)
		{
			new_cmd[j] = ft_strdup(c);
			j++;
			new_cmd[j] = ft_strdup(cmd[i] + (c[1] ? 2 : 1));
		}
		else if (ft_strrindex(cmd[i], c[0]) == (int)ft_strlen(cmd[i]) - 1)
		{
			new_cmd[j] = ft_strdup(cmd[i]);
			new_cmd[j][ft_strlen(new_cmd[j]) - (c[1] ? 2 : 1)] = '\0';
			j++;
			new_cmd[j] = ft_strdup(c);
		}
		else
			j += spaces_error_aux_b(&cmd[i], &new_cmd[j], c);
		j++;
	}
}

static void	del_multi(char **cmd, char *c)
{
	int		last;
	int		first;

	last = ft_strrindex(cmd[0], c[0]) - (c[1] ? 1 : 0);
	first = ft_strindex(cmd[0], c[0]);
	ft_strcpy(cmd[0] + first, cmd[0] + last);
}

static char	**check_multi(char **cmd, char *c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		count = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == c[0])
				count++;
			if (count > 1)
			{
				del_multi(&cmd[i], c);
				break ;
			}
			j += (c[1] ? 2 : 1);
		}
		i++;
	}
	return (cmd);
}

char		**spaces_error(char **cmd, char *c)
{
	char	**new_cmd;
	int		i;
	int		j;

	cmd = check_multi(cmd, c);
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], c))
		i++;
	if (cmd[i])
		return (cmd);
	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (ft_strindex(cmd[i], c[0]) != 0 && ft_strindex(cmd[i], c[0]) != -1\
			&& ft_strrindex(cmd[i], c[0]) != (int)ft_strlen(cmd[i]) - 1)
			j += 2;
		else if (ft_strchr(cmd[i], c[0]))
			j += 1;
	}
	new_cmd = malloc(sizeof(char *) * (j + i + 1));
	new_cmd[j + i] = ft_strnew(1);
	new_cmd[j + i] = NULL;
	spaces_error_aux_a(cmd, new_cmd, c);
	return (new_cmd);
}
