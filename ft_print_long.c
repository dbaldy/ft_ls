/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 14:57:54 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:59:05 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*strspace(int usersize, int max)
{
	int		i;
	int		j;
	char	*str;

	if ((str = (char*)malloc(sizeof(char) * (max - usersize + 1))) == NULL)
		exit(1);
	i = usersize;
	j = 0;
	while (i < max)
	{
		str[j] = ' ';
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

void				ft_print_l(t_car_list *temp)
{
	print_mins(temp);
	ft_putstr(temp->type);
	ft_putstr(temp->mode);
	if (ft_strlen(temp->mode) == 9)
		ft_putstr(ft_strjoin("  ", space(nb_ch(temp->links), g_max[0])));
	else
		ft_putstr(ft_strjoin(" ", space(nb_ch(temp->links), g_max[0])));
	ft_putnbr(temp->links);
	print_opt_g(temp);
	ft_putstr(temp->group);
	putdevice1(temp);
	print_time_long(temp);
	ft_putstr(" ");
	ft_putstr(temp->name);
	if (ft_strcmp(temp->type, "l") == 0)
		ft_putstr(ft_strjoin(" -> ", temp->link_name));
	ft_putstr("\n");
}

unsigned int		nb_ch(unsigned int nb)
{
	unsigned int		k;

	k = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		k++;
	}
	return (k);
}

unsigned int		combien(t_car_list *temp, int flag)
{
	unsigned int	nb;

	nb = 0;
	while (temp != NULL)
	{
		if ((flag & OPT_A) != OPT_A && temp->name[0] != '.')
			nb += temp->blocks;
		else if ((g_flag & OPT_MAJA) == OPT_MAJA &&
		ft_strcmp(temp->name, ".") != 0 && ft_strcmp(temp->name, "..") != 0)
			nb += temp->blocks;
		else if ((flag & OPT_A) == OPT_A)
			nb += temp->blocks;
		temp = temp->next;
	}
	return (nb);
}

void				ft_print_long(t_car_list *temp, int flag)
{
	calcul_sa(temp, flag);
	device(temp);
	if (((flag & MTPL_AG) != MTPL_AG && temp->next->next != NULL &&
	test_hidden(temp) != 0) || ((flag & MTPL_AG) != MTPL_AG && ((flag & OPT_A)
	== OPT_A || ((g_flag & OPT_MAJA) == OPT_MAJA && test_2(temp) != 0))) ||
		((flag & POINT) == POINT))
	{
		ft_putstr("total ");
		ft_putnbr(combien(temp, flag));
		ft_putstr("\n");
		flag -= MTPL_AG;
	}
	while (temp != NULL)
	{
		if ((flag & OPT_A) != OPT_A && temp->name[0] != '.')
			ft_print_l(temp);
		else if ((g_flag & OPT_MAJA) == OPT_MAJA &&
	ft_strcmp(temp->name, ".") != 0 && ft_strcmp(temp->name, "..") != 0)
			ft_print_l(temp);
		else if ((flag & OPT_A) == OPT_A)
			ft_print_l(temp);
		temp = temp->next;
	}
}
