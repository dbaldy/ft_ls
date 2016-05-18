/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 16:55:26 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 10:52:03 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_type_list g_typ_car[] =
{
	{0, "?"},
	{1, "p"},
	{2, "c"},
	{4, "d"},
	{6, "b"},
	{8, "-"},
	{10, "l"},
	{12, "s"},
	{14, "w"}
};

t_type_list g_typ_mod[] =
{
	{0, "---"},
	{1, "--x"},
	{2, "-w-"},
	{3, "-wx"},
	{4, "r--"},
	{5, "r-x"},
	{6, "rw-"},
	{7, "rwx"}
};

char			*typage(int type)
{
	char	*str;

	str = NULL;
	str = ((type & S_IFIFO) == S_IFIFO) ? ft_strdup(g_typ_car[1].c) : str;
	str = ((type & S_IFCHR) == S_IFCHR) ? ft_strdup(g_typ_car[2].c) : str;
	str = ((type & S_IFDIR) == S_IFDIR) ? ft_strdup(g_typ_car[3].c) : str;
	str = ((type & S_IFBLK) == S_IFBLK) ? ft_strdup(g_typ_car[4].c) : str;
	str = ((type & S_IFREG) == S_IFREG) ? ft_strdup(g_typ_car[5].c) : str;
	str = ((type & S_IFLNK) == S_IFLNK) ? ft_strdup(g_typ_car[6].c) : str;
	str = ((type & S_IFSOCK) == S_IFSOCK) ? ft_strdup(g_typ_car[7].c) : str;
	str = ((type & S_IFWHT) == S_IFWHT) ? ft_strdup(g_typ_car[8].c) : str;
	if (str == NULL)
		str = ft_strdup(g_typ_car[0].c);
	return (str);
}

t_car_list		*ft_list_dir(char *argv)
{
	DIR				*dip;
	struct dirent	*dp;
	t_car_list		*debut;
	t_car_list		*temp;

	debut = NULL;
	if ((dip = opendir(argv)) == NULL)
	{
		perror("ft_ls");
		return (NULL);
	}
	while ((dp = readdir(dip)) != NULL)
	{
		temp = scan(&debut, dp->d_name);
		ft_inspect_file(&temp, ft_strjoin(ft_strjoin(argv, "/"), dp->d_name));
	}
	closedir(dip);
	return (debut);
}

char			*ft_mode(unsigned int st, char *path)
{
	char	*str;

	str = ft_strjoin(g_typ_mod[(S_IRWXU & st) / 64].c,
			g_typ_mod[(S_IRWXG & st) / 8].c);
	str = ft_strjoin(str, g_typ_mod[(S_IRWXO & st)].c);
	if ((S_ISVTX & st) != 0 && (st & S_IRWXO) != 0)
		str[8] = 't';
	else if ((S_ISVTX & st) != 0)
		str[8] = 'T';
	if ((S_ISGID & st) != 0 && (st & S_IRWXG) != 0)
		str[5] = 's';
	else if ((S_ISGID & st) != 0)
		str[5] = 'S';
	if ((S_ISUID & st) != 0 && (st & S_IRWXU) != 0)
		str[2] = 's';
	else if ((S_ISUID & st) != 0)
		str[2] = 'S';
	attributs(&str, path);
	return (str);
}

char			*check_mode(char *str, unsigned int mode)
{
	if ((S_ISVTX & mode) != 0 && (mode & S_IRWXO) != 0)
		str[9] = 't';
	else if ((S_ISVTX & mode) != 0)
		str[9] = 'T';
	if ((S_ISGID & mode) != 0 && (mode & S_IRWXG) != 0)
		str[6] = 's';
	else if ((S_ISGID & mode) != 0)
		str[6] = 'S';
	if ((S_ISUID & mode) != 0 && (mode & S_IRWXU) != 0)
		str[3] = 's';
	else if ((S_ISUID & mode) != 0)
		str[3] = 'S';
	return (str);
}

int				ft_inspect_file(t_car_list **debut, char *path)
{
	struct stat	*buf;

	if ((buf = (struct stat *)malloc(sizeof(struct stat))) == NULL ||
			(lstat(path, buf)) == -1)
	{
		perror("ft_ls");
		return (1);
	}
	(*debut)->type = typage(buf->st_mode);
	(*debut)->mode = ft_mode(buf->st_mode, path);
	(*debut)->links = buf->st_nlink;
	(*debut)->user = ft_strdup(getpwuid(buf->st_uid)->pw_name);
	(*debut)->group = ft_strdup(getgrgid(buf->st_gid)->gr_name);
	(*debut)->size = buf->st_size;
	(*debut)->blocks = buf->st_blocks;
	(*debut)->device = buf->st_rdev;
	(*debut)->date = ((g_flag & OPT_U) == OPT_U) ?
		buf->st_birthtimespec.tv_sec : buf->st_mtimespec.tv_sec;
	complete_link(debut, path, buf);
	free(buf);
	return (0);
}
