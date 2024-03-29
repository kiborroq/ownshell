/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:10:31 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/15 11:54:14 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int ch)
{
	if (ch == 32 || (ch > 8 && ch < 14))
		return (1);
	return (0);
}
