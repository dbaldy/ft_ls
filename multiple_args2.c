/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_args2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 14:58:37 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:05:00 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			temps(char **tab)
{
	int			k;
	t_car_list	*dir1;
	t_car_list	*dir2;

	k = 0;
	while (tab[k + 1] != NULL)
	{
		dir1 = ft_list_dir(tab[k]);
		dir2 = ft_list_dir(tab[k + 1]);
		while (ft_strcmp(dir1->name, ".") != 0)
			dir1 = dir1->next;
		while (ft_strcmp(dir2->name, ".") != 0)
			dir2 = dir2->next;
		if (dir1->date > dir2->date)
			ft_swap(&tab[k], &tab[k + 1]);
		list_clr(&dir1);
		list_clr(&dir2);
		k++;
	}
}

void			rev(char **tab)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	while (tab[k + 1] != NULL)
		k++;
	while (i < k)
	{
		ft_swap(&tab[i], &tab[k]);
		i++;
		k--;
	}
}

void			class_elem(char **tab, int flag)
{
	int		k;

	k = 0;
	while (tab[k + 1] != NULL)
	{
		if (ft_strcmp(tab[k], tab[k + 1]) > 0)
			ft_swap(&tab[k], &tab[k + 1]);
		k++;
	}
	if ((flag & OPT_T) == OPT_T && k > 0)
		temps(tab);
	if ((flag & OPT_MINR) == OPT_MINR && k > 0)
		rev(tab);
}

void			ft_args(char **tab, int flag, int compt)
{
	int		k;

	k = 0;
	while (tab[k] != NULL)
	{
		if (compt > 0)
		{
			ft_putstr("\n");
			ft_putstr(tab[k]);
			ft_putendl(":");
		}
		else if (k > 0)
			ft_putstr("\n");
		if ((tab[k + 1] != NULL || k > 0 ||
					(g_nb_dir > 0 && ft_strcmp(tab[k], ".") != 0)) &&
					(compt == 0))
		{
			ft_putstr(tab[k]);
			ft_putendl(":");
		}
		play(flag - MTPL_AG, tab[k]);
		k++;
	}
}

int				place(char **argv, int argc)
{
	int		i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0' &&
			ft_strcmp(argv[i], "--") != 0)
		i++;
	if (i < argc && ft_strcmp(argv[i], "--") == 0)
		i++;
	return (i);
}
