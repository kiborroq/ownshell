/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_treat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 01:55:59 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_unexpect_token_message(char c)
{
	char	*message;
	size_t	len;

	len = ft_strlen(UNEXPECTED_TOKEN);
	message = (char *)ft_calloc(len + 4, sizeof(char));
	if (message != 0)
	{
		ft_memcpy(message, UNEXPECTED_TOKEN, len);
		message[len + 0] = '\'';
		message[len + 1] = c;
		message[len + 2] = '\'';
	}
	return (message);
}
