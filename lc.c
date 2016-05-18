/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 17:12:27 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:26:16 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_car_list		*scan(t_car_list **debut, char *name)
{
	t_car_list			*new;
	t_car_list			*temp;

	temp = *debut;
	if ((new = (t_car_list *)malloc(sizeof(t_car_list))) == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	new->next = NULL;
	if (*debut == NULL)
	{
		new->prev = NULL;
		*debut = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	return (new);
}

void			attributs(char **str, char *path)
{
	acl_t	eph;

	if (listxattr(path, NULL, 999, XATTR_NOFOLLOW) > 0)
		*str = ft_strjoin(*str, "@");
	else if ((eph = acl_get_file(path, ACL_TYPE_EXTENDED)) != NULL)
	{
		*str = ft_strjoin(*str, "+");
		acl_free((void *)eph);
	}
}

void			list_clr(t_car_list **list)
{
	t_car_list	*a;
	t_car_list	*b;

	b = *list;
	a = b->next;
	while (a != NULL)
	{
		if (ft_strcmp(b->type, "l") == 0)
			ft_strdel(&b->link_name);
		ft_strdel(&b->name);
		ft_strdel(&b->mode);
		ft_strdel(&b->type);
		ft_strdel(&b->user);
		ft_strdel(&b->group);
		b->prev = NULL;
		b->next = NULL;
		free(b);
		b = NULL;
		b = a;
		a = a->next;
	}
	b->prev = NULL;
	b->next = NULL;
	free(b);
	b = NULL;
}

int				test_open(char *argv)
{
	struct stat *buf;

	if ((buf = (struct stat *)malloc(sizeof(struct stat))) == NULL)
		return (-1);
	lstat(argv, buf);
	if (ft_strcmp(typage(buf->st_mode), "l") == 0 && ((g_flag & OPT_L) == OPT_L)
			&& argv[ft_strlen(argv) - 1] != '/')
		return (1);
	else
		return (0);
}

void			calc_max_s(t_car_list *temp)
{
	if ((g_flag & OPT_A) == OPT_A)
	{
		while (temp != NULL && temp->name[0] == '.')
			temp = temp->next;
	}
	if (temp == NULL)
		return ;
	g_max[5] = nb_ch(temp->blocks);
	while (temp != NULL)
	{
		g_max[5] = (nb_ch(temp->blocks) > (unsigned int)g_max[5]) ?
			nb_ch(temp->blocks) : g_max[5];
		temp = temp->next;
	}
}
