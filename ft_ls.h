/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 21:34:07 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/07 15:43:51 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <string.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/acl.h>
# define OPT_L 1
# define OPT_A 2
# define OPT_R 4
# define OPT_MINR 8
# define OPT_T 16
# define MTPL_AG 32
# define TYPAGE 64
# define POINT 128
# define OPT_U 256
# define OPT_G 512
# define OPT_MAJA 1024
# define OPT_O 2048
# define OPT_S 4096
# define OPT_MINS 8192
# ifndef _DARWIN_FEATURE_64_BIT_INODE
#  define _DARWIN_FEATURE_64_BIT_INODE
# endif

typedef struct		s_1_list
{
	char			*name;
	char			*type;
	char			*mode;
	unsigned int	links;
	char			*user;
	char			*group;
	unsigned int	size;
	unsigned int	blocks;
	time_t			date;
	char			*link_name;
	unsigned int	device;
	struct s_1_list	*next;
	struct s_1_list	*prev;
}					t_car_list;

typedef struct		s_2_list
{
	int				fi;
	char			*c;
}					t_type_list;

int					test_2(t_car_list *temp);
int					test_hidden(t_car_list *temp);
void				revert_s(t_car_list **a, t_car_list **b,
		t_car_list **debut);
void				ft_print_nolong(t_car_list *temp);
void				calc_max_s(t_car_list *temp);
void				print_mins(t_car_list *temp);
void				ft_s(t_car_list **debut);
void				print_opt_g(t_car_list *temp);
void				check_add_flags(char *str);
char				*ft_strcpy(char *dst, const char *src);
void				print_time_long(t_car_list *temp);
void				complete_link(t_car_list **debut, char *path,
		struct stat *buf);
char				*strspace(int usersize, int max);
void				attributs(char **str, char *path);
void				revert(t_car_list **a, t_car_list **b, t_car_list **debut);
void				fill_max(t_car_list *temp);
void				invert(t_car_list **a, t_car_list **b);
char				*space(unsigned int size, int max);
char				*convert_time(char *date);
void				ft_print_l(t_car_list *temp);
void				ft_putstrfd(char *str);
char				*last_chr(char *str, int c);
void				ft_swap(char **s1, char **s2);
unsigned int		combien(t_car_list *temp, int flag);
void				multiple_args(int argc, char **argv, int i, int flag);
int					size_list(t_car_list *temp);
void				invert(t_car_list **a, t_car_list **b);
void				ft_class(t_car_list **debut);
void				calcul_a(t_car_list *temp);
void				calcul_sa(t_car_list *temp, int flag);
unsigned int		nb_chf(unsigned int nb);
void				ft_print_long(t_car_list *temp, int flag);
char				*space(unsigned int size, int max);
unsigned int		ft_strlen(char *s);
int					play(int flag, char *argv);
void				ft_strdel(char **as);
t_car_list			*scan(t_car_list **debut, char *name);
void				list_clr(t_car_list **list);
char				*ft_strsub(const char *s, unsigned int start,
unsigned int len);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_strclr(const char *s);
char				*ft_itoa(int n);
void				ft_putnbr(int nb);
int					ft_inspect_file(t_car_list **debut, char *path);
t_car_list			*ft_list_dir(char *argv);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_putstr(char *str);
void				ft_putendl(char *str);
void				ft_print_list(t_car_list *car, int flag);
int					analyse(char **argv, int *i, int argc);
unsigned int		nb_ch(unsigned int nb);
char				**ft_strsplit(char const *str, char c);
int					analyse_error(char *argv);
int					test_link(char *str);
void				class_args(int argc, char **argv, int i);
void				ft_reclass(char **argv, int argc, int flag, int compt);
int					place(char **argv, int argc);
void				ft_args(char **tab, int flag, int compt);
void				class_elem(char **tab, int flag);
void				rev(char **tab);
void				temps(char **tab);
void				ft_t(t_car_list **debut);
void				ft_r(t_car_list **temp);
void				ft_print_list(t_car_list *temp, int flag);
int					ft_inspect_link(t_car_list **debut, char *path);
char				*typage (int type);
char				*ft_mode(unsigned int st, char *path);
int					test_open(char *argv);
void				putdevice1(t_car_list *temp);
void				putdevice2(t_car_list *temp);
void				device(t_car_list *temp);
char				wrong_flags(char *str);
void				revert_t(t_car_list **a, t_car_list **b,
		t_car_list **debut);
char				g_c;
int					g_nb_dir;
int					g_flag;
int					g_dev[2];
unsigned int		g_max[6];
#endif
