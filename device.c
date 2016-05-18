/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 11:33:10 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:59:53 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			device(t_car_list *temp)
{
	g_dev[0] = -1;
	g_dev[1] = -1;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->type, "c") == 0 || ft_strcmp(temp->type, "b") == 0)
		{
			g_dev[0] = (g_dev[0] > (int)nb_ch(major(temp->device))) ? g_dev[0] :
				nb_ch(major(temp->device));
			g_dev[1] = (g_dev[1] > (int)nb_ch(minor(temp->device))) ? g_dev[1] :
				nb_ch(minor(temp->device));
		}
		temp = temp->next;
	}
}

void			putdevice1(t_car_list *temp)
{
	if (g_dev[0] == -1)
	{
		ft_putstr(ft_strjoin(strspace(ft_strlen(temp->group), g_max[3] + 2),
			space(nb_ch(temp->size), g_max[4])));
		ft_putnbr(temp->size);
	}
	else if (ft_strcmp(temp->type, "c") == 0 || ft_strcmp(temp->type, "b") == 0)
	{
		ft_putstr(ft_strjoin(strspace(ft_strlen(temp->group), g_max[3] + 3),
			space(nb_ch(major(temp->device)), g_dev[0])));
		ft_putnbr(major(temp->device));
		ft_putstr(ft_strjoin(", ",
			space(nb_ch(minor(temp->device)), g_dev[1])));
		ft_putnbr(minor(temp->device));
	}
	else
	{
		ft_putstr(ft_strjoin(strspace(ft_strlen(temp->group),
						g_max[3] + 2 + g_max[4]),
			space(nb_ch(temp->size), g_max[4])));
		if (g_max[4] == 1)
			ft_putstr("      ");
		ft_putnbr(temp->size);
	}
}

void			putdevice2(t_car_list *temp)
{
	if (g_dev[0] == -1)
	{
		ft_putstr(ft_strjoin("  ", space(nb_ch(temp->size), g_max[4])));
		ft_putnbr(temp->size);
	}
	else if (ft_strcmp(temp->type, "c") == 0 || ft_strcmp(temp->type, "b") == 0)
	{
		ft_putstr(ft_strjoin("  ",
					space(nb_ch(major(temp->device)), g_dev[0])));
		ft_putnbr(major(temp->device));
		ft_putstr(ft_strjoin(", ",
			space(nb_ch(minor(temp->device)), g_dev[1])));
		ft_putnbr(minor(temp->device));
	}
	else
	{
		ft_putstr(ft_strjoin("  ",
			strspace(0, g_dev[0] + g_dev[1])));
		ft_putnbr(temp->size);
	}
}

void			complete_link(t_car_list **debut, char *path, struct stat *buf)
{
	int			size;

	if (ft_strcmp((*debut)->type, "l") == 0)
	{
		size = (buf->st_size > 0) ? buf->st_size : 999;
		if (((*debut)->link_name = (char*)malloc(sizeof(char) * (size + 1)))
				== NULL)
			exit(1);
		readlink(path, (*debut)->link_name, size);
		(*debut)->link_name[size] = '\0';
	}
}

void			print_time_long(t_car_list *temp)
{
	char	*str;

	if (temp->date > time(NULL) - 15778800 && temp->date <
			time(NULL) + 15778800)
		ft_putstr(ft_strsub(ctime(&temp->date), 3, 13));
	else if (temp->date < time(NULL) + 15778800)
	{
		str = ft_strdup(convert_time(ctime(&temp->date)));
		if (str[3] == ' ' && str[4] == ' ' && str[6] != ' ')
			ft_strcpy(&str[4], &str[5]);
		ft_putstr(ft_strjoin(" ", str));
		free(str);
	}
	else
		ft_putstr(ft_strjoin(" ", convert_time(ctime(&temp->date))));
}
