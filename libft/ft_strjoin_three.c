/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:19:23 by aronin            #+#    #+#             */
/*   Updated: 2020/09/17 17:28:48 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*str_cons;
	char	*str_cons0;

	if (!s1 || !s2 ||
	!(str_cons0 = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1)))
		return (NULL);
	str_cons = str_cons0;
	while (*s1)
		*str_cons++ = *s1++;
	while (*s2)
		*str_cons++ = *s2++;
	while (*s3)
		*str_cons++ = *s3++;
	*str_cons = 0;
	return (str_cons0);
}
