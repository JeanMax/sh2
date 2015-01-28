/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/28 16:52:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** errors handling
** type: c = command not found, e = no such file, b = bus error, s = segfault,
**		 f = floating-point excepion, a = too many arg, p = $PATH not found
**		 e = execve error, c = cmd not found, o = open, F = fork fail,
**		 P = pipe fail
*/

#include "header.h"

void		error(char *type, char *msg)
{
	if (type[0] == 'c')
		ft_putstr_fd("sh2: command not found: ", 2);
	else if (type[0] == 'e')
		ft_putstr_fd("sh2: no such file or directory: ", 2);
	else if (type[0] == 'o')
		ft_putstr_fd("sh2: can't make file: ", 2);
	if (type[0] == 'c' || type[0] == 'e' || type[0] == 'o')
		ft_putendl_fd(msg, 2);
	else if (type[0] == 'b')
		ft_putendl_fd("Bus error. Try Again...", 2);
	else if (type[0] == 'P')
		ft_putendl_fd("Pipe failed. Try Again...", 2);
	else if (type[0] == 'F')
		ft_putendl_fd("Fork failed. Try Again...", 2);
	else if (type[0] == 's')
		ft_putendl_fd("Segmentation fault. Try Again...", 2);
	else if (type[0] == 'f')
		ft_putendl_fd("Floating-point exception. Try Again...", 2);
	else if (type[0] == 'a')
		ft_putendl_fd("Too many arguments.", 2);
	else if (type[0] == 'p')
		ft_putendl_fd("$PATH missing from env.", 2);
	exit((type[0] == 'c' || type[0] == 'e') ? 1 : -1);
}
