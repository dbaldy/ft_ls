/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 14:58:09 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:02:09 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*space(unsigned int size, int max)
{
	char				*str;
	unsigned int		i;

	if ((str = (char *)malloc(sizeof(char) * (max - size + 1))) == NULL)
	{
		perror("ft_ls");
		exit(1);
	}
	i = 0;
	while (i < (max - size))
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*convert_time(char *date)
{
	char	**str;
	char	*ptr;

	str = ft_strsplit(date, ' ');
	str[4][ft_strlen(str[4]) - 1] = '\0';
	ptr = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(str[1], "  "), str[2]),
				"  "), str[4]);
	return (ptr);
}

void		revert(t_car_list **a, t_car_list **b, t_car_list **debut)
{
	t_car_list *temp;

	temp = *a;
	while (ft_strcmp((*b)->name, (*a)->name) < 0)
	{
		invert(a, b);
		*debut = (ft_strcmp((*a)->name, (*debut)->name) == 0) ? *b : *debut;
		*a = ((*b)->prev != NULL) ? (*b)->prev : *b;
		*b = ((*b)->prev != NULL) ? *b : (*b)->next;
	}
	*a = temp;
	*b = (*a)->next;
}

void		revert_t(t_car_list **a, t_car_list **b, t_car_list **debut)
{
	t_car_list *temp;

	temp = *a;
	while ((*b)->date > (*a)->date)
	{
		invert(a, b);
		*debut = (((*a)->date - (*debut)->date) == 0) ? *b : *debut;
		*a = ((*b)->prev != NULL) ? (*b)->prev : *b;
		*b = ((*b)->prev != NULL) ? *b : (*b)->next;
	}
	*a = temp;
	*b = (*a)->next;
}

void		revert_s(t_car_list **a, t_car_list **b, t_car_list **debut)
{
	t_car_list *temp;

	temp = *a;
	while ((*b)->size > (*a)->size)
	{
		invert(a, b);
		*debut = (((*a)->size - (*debut)->size) == 0) ? *b : *debut;
		*a = ((*b)->prev != NULL) ? (*b)->prev : *b;
		*b = ((*b)->prev != NULL) ? *b : (*b)->next;
	}
	*a = temp;
	*b = (*a)->next;
}
