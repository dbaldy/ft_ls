/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 18:33:55 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:44:13 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_t(t_car_list **debut)
{
	t_car_list	*a;
	t_car_list	*b;

	a = *debut;
	if (a != NULL)
	{
		b = a->next;
		while (b != NULL)
		{
			if (b->date > a->date)
				revert_t(&a, &b, debut);
			else
			{
				b = b->next;
				a = a->next;
			}
		}
	}
}

void		ft_r(t_car_list **temp)
{
	t_car_list *a;
	t_car_list *b;

	a = *temp;
	if (a != NULL)
	{
		b = a->next;
		while (b != NULL)
		{
			b = a->next;
			a->next = a->prev;
			a->prev = b;
			if (b != NULL)
				a = b;
		}
	}
	if (a != NULL)
		*temp = a;
}

void		ft_print_list(t_car_list *temp, int flag)
{
	if (temp == NULL)
		return ;
	if ((g_flag & OPT_U) != OPT_U)
		ft_class(&temp);
	if ((flag & OPT_T) == OPT_T)
		ft_t(&temp);
	if ((g_flag & OPT_S) == OPT_S)
		ft_s(&temp);
	if ((flag & OPT_MINR) == OPT_MINR)
		ft_r(&temp);
	if ((g_flag & OPT_MINS) == OPT_MINS)
		calc_max_s(temp);
	if ((flag & OPT_L) != OPT_L)
		ft_print_nolong(temp);
	else if (temp != NULL)
		ft_print_long(temp, flag);
}
