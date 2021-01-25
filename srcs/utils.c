/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 02:00:37 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_strjoin_wrap(char *s1, char *s2)
{
	char	*new;

	if (s1 == 0 && s2 == 0)
		new = 0;
	if (s1 == 0)
		new = s2;
	else if (s2 == 0)
		new = s1;
	else
	{
		new = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return (new);
}
