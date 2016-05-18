/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 21:56:22 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:25:50 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>

void	ft_putstrfd(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	ft_swap(char **s1, char **s2)
{
	char *a;

	a = *s1;
	*s1 = *s2;
	*s2 = a;
}

char	*last_chr(char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = ft_strdup(str);
	while (ptr[i])
		i++;
	while (i && ptr[i] != (const char)c)
		i--;
	if (i == 0 && ptr[i] != (const char)c)
		return (ptr);
	else
		while (ptr[i])
		{
			ptr[i] = '\0';
			i++;
		}
	return (ptr);
}

void	invert(t_car_list **a, t_car_list **b)
{
	t_car_list *bufb;
	t_car_list *bufa;

	bufb = (*b)->next;
	bufa = (*a)->prev;
	if (bufa != NULL)
		bufa->next = *b;
	(*b)->prev = bufa;
	(*b)->next = *a;
	(*a)->prev = (*b);
	(*a)->next = bufb;
	if (bufb != NULL)
		bufb->prev = *a;
}

void	fill_max(t_car_list *temp)
{
	g_max[0] = (nb_ch(temp->links) > (unsigned int)g_max[0]) ?
		nb_ch(temp->links) : g_max[0];
	g_max[1] = (ft_strlen(temp->mode) > g_max[1]) ?
		ft_strlen(temp->mode) : g_max[1];
	g_max[2] = (ft_strlen(temp->user) > g_max[2]) ?
		ft_strlen(temp->user) : g_max[2];
	g_max[3] = (ft_strlen(temp->group) > g_max[3]) ?
		ft_strlen(temp->group) : g_max[3];
	g_max[4] = (nb_ch(temp->size) > (unsigned int)g_max[4]) ?
		nb_ch(temp->size) : g_max[4];
}
