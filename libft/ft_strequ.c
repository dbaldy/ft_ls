/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strqu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:55:13 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:19:49 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && ((s1[i]) || (s2[i])))
		i++;
	if (s1[i] != s2[i])
		return (0);
	else
		return (1);
}
