/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:40:00 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/15 01:17:59 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** cd builtin
*/

#include "header.h"

static void	go_home(t_env *e)
{
	char	**av;
	char	*home;
	char	*pwd;

	!ft_strlen(home = get_env("HOME", e)) ? failn("cd: No home directory.") : 0;
	if (!ft_strlen(home))
		return ;
	pwd = get_env("PWD", e);
	if (!(av = set_av("OLDPWD", pwd, e, 0)))
		return ;
	launch_builtin(av, e);
	ft_freestab(av);
	av = ft_strcmp(pwd, home) ? set_av("PWD", home, e, 1) : NULL;
	ft_strcmp(pwd, home) ? ft_freestab(av) : (void)0;
	ft_memdel((void *)&home);
	ft_memdel((void *)&pwd);
}

static void	go_previous(t_env *e)
{
	char	**av1;
	char	**av2;
	char	*oldpwd;
	char	*home;
	char	*to_free;

	oldpwd = get_env("OLDPWD", e);
	to_free = oldpwd;
	home = get_env("HOME", e);
	if (ft_strstr(oldpwd, home))
	{
		oldpwd += ft_strlen(home) - 1;
		oldpwd[0] = '~';
	}
	oldpwd += ft_strnstr(oldpwd, "/private/", 9) ? 8 : 0;
	ft_putendl(oldpwd);
	if (!(av1 = set_av("OLDPWD", "PWD", e, 0)))
		return ;
	if (!(av2 = set_av("PWD", "OLDPWD", e, 1)))
		return ;
	launch_builtin(av1, e);
	ft_memdel((void *)&home);
	ft_memdel((void *)&to_free);
	ft_freestab(av1);
	ft_freestab(av2);
}

static void	go_to(char *path, t_env *e)
{
	char	**av;
	char	*pwd;
	char	*tmp;
	char	free_it;

	free_it = '\0';
	pwd = get_env("PWD", e);
	if (path[0] != '/' && path[0] != '~')
	{
		tmp = ft_strjoin(pwd, "/");
		path = ft_strjoin(tmp, path);
		ft_memdel((void *)&tmp);
		free_it = 'f';
	}
	if (!(av = set_av("OLDPWD", pwd, e, 0)))
		return ;
	ft_memdel((void *)&pwd);
	launch_builtin(av, e);
	ft_freestab(av);
	if (!(av = set_av("PWD", path, e, 1)))
		return ;
	ft_freestab(av);
	free_it ? ft_memdel((void *)&path) : (void)0;
}

void		ft_cd(char **av, t_env *e)
{
	int			ac;
	char		buf[PATH_SIZE];
	char		*pwd;
	char		*home;

	ac = 0;
	while (av[ac])
		ac++;
	ac > 2 ? ft_putendl("cd: Too many arguments.") : (void)0;
	if (ac > 2)
		return ;
	ac == 1 ? go_home(e) : (void)0;
	(ac > 1 && !ft_strcmp(av[1], "-")) ? go_previous(e) : (void)0;
	(ac > 1 && ft_strcmp(av[1], "-")) ? go_to(av[1], e) : (void)0;
	pwd = ft_strdup(getcwd(buf, PATH_SIZE));
	home = get_env("HOME", e);
	if (!(av = set_av("PWD", (ft_strncmp(pwd, "/Volumes/Data", 13) ||\
		ft_strlen(pwd) < ft_strlen(home)) ? pwd : pwd + 13, e, 1)))
		return ;
	launch_builtin(av, e);
	ft_memdel((void *)&pwd);
	ft_memdel((void *)&home);
	ft_freestab(av);
}
