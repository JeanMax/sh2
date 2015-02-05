/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/05 17:58:43 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

/*
** define
*/
# define HEADER_H
# define PATH_SIZE 128
# define DEBUG { ft_putstr_clr(__func__, "r"); ft_putstr_clr(" (", "r"); ft_putstr_clr(__FILE__, "red"); ft_putstr_clr(") - line: ", "r"); ft_putnbr_clr(__LINE__, "r"); ft_putendl(""); } //debug

/*
** include
*/
# include "libft/inc/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

/*
** struct def
*/
typedef struct s_env	t_env;
struct	s_env
{
	t_lst	*first_l;
	char	**env;
	char	**path;
	char	**builtin;
};

/*
** prototypes
*/
int		is_builtin(char **cmd, t_env *e);
char	**spaces_error(char **cmd, char *c);
void	simple_right(char **cmd, t_env *e);
void	simple_left(char **cmd, t_env *e);
void	simple_pipe(char **cmd, t_env *e);
void	doble_left(char **cmd, t_env *e);
void	doble_right(char **cmd, t_env *e);
void	redirect(char **cmd, t_env *e, int i);
void	semicolon(char *line, t_env *e);
void	init(int ac, char **ae, t_env *e);
void	prompt(t_env *e);
void	error(char *type, char *msg);
void	call_execve(char **cmd, t_env *e);
void	fork_it(char **cmd, t_env *e);
void	get_path(t_env *e);
void	get_builtin(t_env *e);
char	*get_env(char *var, t_env *e);
char	**cpy_env(char **ae, char *val);
void	launch_cmd(char **cmd, t_env *e);
void	launch_builtin(char **av, t_env *e);
void	prompt_loop(char **av, t_env *e);
void	ft_exit(int ac, char **av);
void	ft_env(char **av, t_env *e);
void	ft_cd(char **av, t_env *e);
void	ft_setenv(char **ac, t_env *e);
void	ft_unsetenv(char **ac, t_env *e);

#endif
