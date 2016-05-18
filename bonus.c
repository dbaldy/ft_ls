/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 16:33:08 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:25:44 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		wrong_flags(char *str)
{
	int			j;

	j = 1;
	if (str[j] == '-' && str[j + 1] != '\0')
		return (str[j]);
	while (str[j])
	{
		if (str[j] != 'l' && str[j] != '1' && str[j] != 'a' && str[j] != 'R'
				&& str[j] != 'r' && str[j] != 't' && str[j] != 'U' &&
				str[j] != 'g' && str[j] != 'A' && str[j] != 'o' &&
				str[j] != 'S' && str[j] != 's')
			return (str[j]);
		j++;
	}
	return (0);
}

void		check_add_flags(char *str)
{
	int		j;

	j = 1;
	while (str[j])
	{
		if ((g_flag & OPT_U) != OPT_U && str[j] == 'U')
			g_flag = g_flag + OPT_U;
		if ((g_flag & OPT_G) != OPT_G && str[j] == 'g')
			g_flag = g_flag + OPT_G;
		if ((g_flag & OPT_MAJA) != OPT_MAJA && str[j] == 'A')
			g_flag = g_flag + OPT_MAJA;
		if ((g_flag & OPT_O) != OPT_O && str[j] == 'o')
			g_flag = g_flag + OPT_O;
		if ((g_flag & OPT_S) != OPT_S && str[j] == 'S')
			g_flag = g_flag + OPT_S;
		if ((g_flag & OPT_MINS) != OPT_MINS && str[j] == 's')
			g_flag = g_flag + OPT_MINS;
		j++;
	}
}

void		print_opt_g(t_car_list *temp)
{
	ft_putstr(" ");
	if ((g_flag & OPT_G) != OPT_G)
	{
		ft_putstr(temp->user);
		ft_putstr(ft_strjoin("  ", strspace(ft_strlen(temp->user), g_max[2])));
	}
}

void		ft_s(t_car_list **debut)
{
	t_car_list	*a;
	t_car_list	*b;

	a = *debut;
	b = a->next;
	while (b != NULL)
	{
		if (b->size > a->size)
			revert_s(&a, &b, debut);
		else
		{
			b = b->next;
			a = a->next;
		}
	}
}

void		print_mins(t_car_list *temp)
{
	if ((g_flag & OPT_MINS) == OPT_MINS && (g_flag & OPT_A) != OPT_A &&
				temp->name[0] != '.')
	{
		ft_putstr(space(nb_ch(temp->blocks), g_max[5]));
		ft_putnbr(temp->blocks);
		ft_putstr(" ");
	}
	else if ((g_flag & OPT_MINS) == OPT_MINS && (g_flag & OPT_MAJA) == OPT_MAJA
		&& ft_strcmp(temp->name, ".") != 0 && ft_strcmp(temp->name, "..") != 0)
	{
		ft_putstr(space(nb_ch(temp->blocks), g_max[5]));
		ft_putnbr(temp->blocks);
		ft_putstr(" ");
	}
	else if ((g_flag & OPT_MINS) == OPT_MINS && (g_flag & OPT_A) == OPT_A)
	{
		ft_putstr(space(nb_ch(temp->blocks), g_max[5]));
		ft_putnbr(temp->blocks);
		ft_putstr(" ");
	}
}
