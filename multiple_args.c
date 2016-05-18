/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 14:58:24 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 14:59:32 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_reclass(char **argv, int argc, int flag, int compt)
{
	int		j;
	DIR		*dip;
	char	**tab;
	int		k;

	j = place(argv, argc);
	k = 0;
	if ((tab = (char**)malloc(sizeof(char*) * (argc - j + 1))) == NULL)
		exit(1);
	while (j < argc)
	{
		if (((dip = opendir(argv[j])) != NULL) && test_open(argv[j]) == 0)
		{
			tab[k] = argv[j];
			k++;
		}
		if (dip != NULL)
			(void)closedir(dip);
		j++;
	}
	tab[k] = NULL;
	if (tab[0] != NULL && k > 1)
		class_elem(tab, flag);
	ft_args(tab, flag, compt);
}

void			class_args(int argc, char **argv, int i)
{
	int			re;

	re = 1;
	while (re > 0)
	{
		re = 0;
		while (i < argc - 1)
		{
			if (ft_strcmp(argv[i], argv[i + 1]) > 0)
			{
				ft_swap(&argv[i], &argv[i + 1]);
				re = 1;
			}
			if (ft_strcmp(argv[i], "") == 0)
			{
				ft_putstrfd("ls: fts_open: No such file or directory\n");
				exit(1);
			}
			i++;
		}
	}
}

int				test_link(char *str)
{
	struct stat *buf;

	if ((buf = (struct stat*)malloc(sizeof(struct stat))) == NULL ||
			lstat(str, buf) == -1)
		return (0);
	else
		return (1);
}

int				analyse_error(char *argv)
{
	if (errno == 13)
	{
		perror("ft_ls");
		return (0);
	}
	else if (errno == 2 && test_link(argv) == 0)
	{
		if (ft_strcmp(argv, "") == 0)
		{
			ft_putstrfd("ls: fts_open: No such file or directory\n");
			exit(1);
		}
		else
			ft_putstrfd(ft_strjoin("ls: ", argv));
		ft_putstrfd(": No such file or directory\n");
		g_nb_dir++;
		return (0);
	}
	else
		return (1);
}

void			multiple_args(int argc, char **argv, int i, int flag)
{
	t_car_list	*debut;
	t_car_list	*temp;
	DIR			*dip;
	int			compt[2];

	debut = NULL;
	compt[0] = 0;
	class_args(argc, argv, i);
	while (i < argc)
	{
		if (((dip = opendir(argv[i])) == NULL) || (test_open(argv[i]) == 1))
			if ((compt[1] = analyse_error(argv[i])) == 1)
			{
				compt[0]++;
				temp = scan(&debut, argv[i]);
				ft_inspect_file(&temp, argv[i]);
			}
		if (dip != NULL)
			closedir(dip);
		i++;
	}
	if (debut != NULL)
		ft_print_list(debut, flag);
	if (compt[0] != argc)
		ft_reclass(argv, argc, flag, compt[0]);
}
