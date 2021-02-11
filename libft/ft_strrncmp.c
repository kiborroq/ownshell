/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:10:31 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/05 20:14:45 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	int		diff;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!s1_len && s2_len)
		return (0 - *s2);
	if (!s2_len && s1_len)
		return (*s1 - 0);
	if (!s1_len && !s2_len)
		return (0);
	diff = 0;
	i = 0;
	while (i < n && diff == 0)
	{
		diff = s1[s1_len - i - 1] - s2[s2_len - i - 1];
		i++;
	}
	return (diff);
}
