/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 22:05:53 by dbaldy            #+#    #+#             */
/*   Updated: 2016/05/18 10:36:04 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		recurs(char *path, t_car_list *temp, int flag)
{
	char	*str;

	while (temp != NULL)
	{
		if (ft_strcmp(temp->type, "d") == 0 && ft_strcmp(temp->name, ".") != 0
				&& ft_strcmp(temp->name, "..") != 0 && (flag & OPT_A) == OPT_A)
		{
			str = ft_strjoin(ft_strjoin(path, "/"), temp->name);
			ft_putstr("\n");
			ft_putstr(str);
			ft_putendl(":");
			play(flag, str);
		}
		else if (ft_strcmp(temp->type, "d") == 0 && (flag & OPT_A) != OPT_A &&
				temp->name[0] != '.')
		{
			str = ft_strjoin(ft_strjoin(path, "/"), temp->name);
			ft_putstr("\n");
			ft_putstr(str);
			ft_putendl(":");
			play(flag, str);
		}
		temp = temp->next;
	}
}

int			play(int flag, char *argv)
{
	t_car_list	*debut;

	debut = ft_list_dir(argv);
	ft_print_list(debut, flag);
	if ((flag & OPT_MINR) == OPT_MINR || (flag & OPT_T) == OPT_T
			|| (g_flag & OPT_S) == OPT_S)
		while (debut != NULL && debut->prev != NULL)
			debut = debut->prev;
	if ((flag & OPT_R) == OPT_R)
		recurs(argv, debut, flag);
	if (debut != NULL)
		list_clr(&debut);
	return (0);
}

int			main(int argc, char **argv)
{
	int			i;

	i = 1;
	analyse(argv, &i, argc);
	if (g_c != 0)
	{
		ft_putstrfd("ft_ls: illegal option -- ");
		write(2, &g_c, 1);
		ft_putstrfd("\n");
		ft_putstrfd("usage: ls [-ASRUaglrst1] ");
		ft_putendl("[file ...]");
		return (0);
	}
	else if (argc == i)
		play(g_flag, ".");
	else
	{
		g_nb_dir = 0;
		multiple_args(argc, argv, i, g_flag);
	}
	return (0);
}
