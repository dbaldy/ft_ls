/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 11:41:34 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:26:00 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			calcul_sa(t_car_list *temp, int flag)
{
	if ((flag & OPT_A) == OPT_A)
		return (calcul_a(temp));
	while (temp != NULL && temp->name[0] == '.')
		temp = temp->next;
	if (temp == NULL)
		return ;
	g_max[0] = nb_ch(temp->links);
	g_max[1] = ft_strlen(temp->mode);
	g_max[2] = ft_strlen(temp->user);
	g_max[3] = ft_strlen(temp->group);
	g_max[4] = nb_ch(temp->size);
	while (temp != NULL)
	{
		if (temp->name[0] != '.')
			fill_max(temp);
		temp = temp->next;
	}
}

void			calcul_a(t_car_list *temp)
{
	if (temp == NULL)
		return ;
	g_max[0] = nb_ch(temp->links);
	g_max[1] = ft_strlen(temp->mode);
	g_max[2] = ft_strlen(temp->user);
	g_max[3] = ft_strlen(temp->group);
	g_max[4] = nb_ch(temp->size);
	while (temp != NULL)
	{
		fill_max(temp);
		temp = temp->next;
	}
}

void			check_flags(char *str)
{
	int	j;

	j = 1;
	while (str[j])
	{
		if ((g_flag & OPT_L) == OPT_L && str[j] == '1')
			g_flag = g_flag - OPT_L;
		if ((g_flag & OPT_L) != OPT_L && (str[j] == 'l' || str[j] == 'g'
					|| str[j] == 'o'))
			g_flag = g_flag + OPT_L;
		if ((g_flag & OPT_A) != OPT_A)
			g_flag = (str[j] == 'a') ? g_flag + OPT_A : g_flag;
		if ((g_flag & OPT_R) != OPT_R)
			g_flag = (str[j] == 'R') ? g_flag + OPT_R : g_flag;
		if ((g_flag & OPT_MINR) != OPT_MINR)
			g_flag = (str[j] == 'r') ? g_flag + OPT_MINR : g_flag;
		if ((g_flag & OPT_T) != OPT_T)
			g_flag = (str[j] == 't') ? g_flag + OPT_T : g_flag;
		j++;
	}
}

int				analyse(char **argv, int *i, int argc)
{
	while (*i < argc && argv[*i][0] == '-' && argv[*i][1] != '\0'
			&& (ft_strcmp(argv[*i], "--") != 0))
	{
		g_c = wrong_flags(argv[*i]);
		check_flags(argv[*i]);
		check_add_flags(argv[*i]);
		if (g_c != 0)
			return (0);
		(*i)++;
	}
	if ((*i) < argc && (ft_strcmp(argv[*i], "--") == 0))
		(*i)++;
	if (*i != argc)
		g_flag += MTPL_AG;
	else
		g_flag += POINT;
	return (g_flag);
}

void			ft_class(t_car_list **debut)
{
	t_car_list	*a;
	t_car_list	*b;

	a = *debut;
	b = a->next;
	while (b != NULL)
	{
		if (ft_strcmp(b->name, a->name) < 0)
			revert(&a, &b, debut);
		else
		{
			b = b->next;
			a = a->next;
		}
	}
}
