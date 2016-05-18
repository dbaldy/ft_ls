/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:54:54 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:59:56 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_nolong_s(t_car_list *temp)
{
	while (temp != NULL)
	{
		if ((g_flag & OPT_A) != OPT_A && temp->name[0] != '.')
		{
			print_mins(temp);
			ft_putendl(temp->name);
		}
		else if ((g_flag & OPT_MAJA) == OPT_MAJA &&
				ft_strcmp(temp->name, ".") != 0 &&
				ft_strcmp(temp->name, "..") != 0)
		{
			print_mins(temp);
			ft_putendl(temp->name);
		}
		else if ((g_flag & OPT_A) == OPT_A)
		{
			print_mins(temp);
			ft_putendl(temp->name);
		}
		temp = temp->next;
	}
}

void		ft_print_nolong(t_car_list *temp)
{
	if ((g_flag & OPT_MINS) == OPT_MINS)
		ft_print_nolong_s(temp);
	else
	{
		while (temp != NULL)
		{
			if ((g_flag & OPT_A) != OPT_A && temp->name[0] != '.')
				ft_putendl(temp->name);
			else if ((g_flag & OPT_MAJA) == OPT_MAJA &&
					ft_strcmp(temp->name, ".") != 0 &&
					ft_strcmp(temp->name, "..") != 0)
				ft_putendl(temp->name);
			else if ((g_flag & OPT_A) == OPT_A)
				ft_putendl(temp->name);
			temp = temp->next;
		}
	}
}

int			test_hidden(t_car_list *temp)
{
	t_car_list *buf;

	buf = temp;
	while (buf != NULL)
	{
		if (buf->name[0] != '.')
			return (1);
		buf = buf->next;
	}
	return (0);
}

int			test_2(t_car_list *temp)
{
	t_car_list *buf;

	buf = temp;
	while (buf != NULL)
	{
		if (ft_strcmp(buf->name, ".") != 0 && ft_strcmp(buf->name, "..") != 0)
			return (1);
		buf = buf->next;
	}
	return (0);
}
