/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 17:02:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/15 01:12:20 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handle prompt loop
** print a pretty prompt
** split line in a tab (space and tab as separators, handle ; " and ')
*/

#include "header.h"

extern pid_t	g_pid1;
extern pid_t	g_pid2;

void			prompt(t_env *e)
{
	char		*user;
	char		*pwd;
	char		*home;
	int			i;

	i = 0;
	user = get_env("USER", e);
	pwd = get_env("PWD", e);
	home = get_env("HOME", e);
	i += ft_strnstr(pwd, "/private/", 9) ? 8 : 0;
	i += ft_strnstr(pwd, "/Volumes/Data/", 14) ? 13 : 0;
	if (ft_strnstr(pwd, home, ft_strlen(home)))
	{
		i += ft_strlen(home) - 1;
		pwd[ft_strlen(home) - 1] = '~';
	}
	ft_putstr_clr(user, "red");
	ft_putstr_clr("@sh2", "yellow");
	ft_putchar_clr(':', "white");
	ft_putendl_clr(pwd + i, "green");
	ft_putstr_clr("> ", "green");
	ft_memdel((void *)&user);
	ft_memdel((void *)&pwd);
	ft_memdel((void *)&home);
}

static char		**split_that(char *s)
{
	int			i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
		{
			s[i] = -42;
			while (s[++i] != '\'')
				if (!s[i])
					return (failn("Unmatched \'."));
			s[i] = -42;
		}
		else if (s[i] == '\"')
		{
			s[i] = -42;
			while (s[++i] != '\"')
				if (!s[i])
					return (failn("Unmatched \"."));
			s[i] = -42;
		}
		else if (s[i] == ' ' || s[i] == '\t')
			s[i] = -42;
	}
	return (ft_strsplit(s, -42));
}

static void		semicolon(char *line, t_env *e)
{
	char		**sc_tab;
	char		**cmd;
	int			i;

	sc_tab = ft_strsplit(line, ';');
	i = 0;
	while (sc_tab[i])
	{
		if ((cmd = split_that(sc_tab[i])))
			launch_cmd(cmd, e), ft_freestab(cmd);
		i++;
	}
	ft_freestab(sc_tab);
	ft_memdel((void *)&line);
}

void			prompt_loop(char **av, t_env *e)
{
	char		*line;
	char		**cmd;

	while (42)
	{
		prompt(e);
		g_pid1 = g_pid2;
		get_line(0, &line) ? (void)0 : ft_exit(0, av);
		if (ft_strindex(line, ';') != -1)
		{
			semicolon(line, e);
			continue ;
		}
		if ((cmd = split_that(line)))
			launch_cmd(cmd, e), ft_freestab(cmd);
		ft_memdel((void *)&line);
	}
}
