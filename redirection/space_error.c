/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 18:44:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/10 22:00:56 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handle spaces error in cmd tabs :
** "X>", "Y" wille be corrected in "X", ">", "Y"
** same idea for ">Y" and "X>Y"
** also working for any other str than ">" (basically ">>", ">", "|", "<", "<<")
*/

#include "header.h"
/*
	static int	spaces_error_aux_b(char **cmd, char **new_cmd, char *c)
	{
	DEBUG;	//debug
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
	DEBUG;	//debug
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

	char		**spaces_error(char **cmd, char *c)
	{
	char	**new_cmd;
	int		i;
	int		j;

	//debug
	i = 0;
	while (cmd[i])
	ft_debugstr("cmd", cmd[i++]);
//	exit(0);
//debug

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
new_cmd[j + i] = NULL;
spaces_error_aux_a(cmd, new_cmd, c);

//debug
i = 0;
while (new_cmd[i])
ft_debugstr("new_cmd", new_cmd[i++]);
exit(0);
//debug
return (new_cmd);
}
*/

static int					tab_len(char **c, int len)
{
	char			*s;

	while (*c)
	{
		s = *c;
		if ((ft_strchr(s, '>') || ft_strchr(s, '<') || ft_strchr(s, '|')))
		{
			len += (*s != '>' && *s != '<' && *s != '|') ? 1 : 0;
			s += (*(s + 1) == *s && *s == '>') ||\
				(*(s + 1) == *s && *s == '<') ? 1 : 0;
			while (*s)
			{
				if (*s == '>' || *s == '<' || *s == '|')
					len += *(s + 1) ? 2 : 1;
				s += (*(s + 1) == *s && *s == '>') ||\
					(*(s + 1) == *s && *s == '<') ? 2 : 1;
			}
			len -= (*(s - 1) == *(s - 2) &&\
					(*(s - 1) == '>' || *(s - 1) == '<' || *(s - 1) == '|')) ? 1 : 0;
		}
		else
			len++;
		c++;
	}
	return (len);
}
char		**spaces_error(char **cmd, char *c)
{
	c = c;
	ft_debugnbr("len", tab_len(cmd));
	exit(0);
	return (NULL);
}
