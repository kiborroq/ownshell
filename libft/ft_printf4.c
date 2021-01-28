/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/26 12:12:25 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup_advanced(const char *s1, t_struct ***output,
int precision)
{
	char		*dst;
	char		*dst0;
	int			len;

	if (!s1)
		s1 = "(null)";
	len = (precision >= 0 ? precision : (int)ft_strlen(s1));
	if (!(dst = malloc((len + 1) * sizeof(char))))
	{
		(**output)->error = 1;
		return (NULL);
	}
	dst0 = dst;
	while (len-- && *s1)
		*dst++ = *s1++;
	*dst = 0;
	return (dst0);
}

int			convert_to_int(const char ***input, t_struct **output)
{
	char	temp[11];
	int		i;

	i = 0;
	while (ft_isdigit(***input))
	{
		temp[i++] = ***input;
		if (i == 11)
		{
			(*output)->error = 1;
			return (0);
		}
		(**input)++;
	}
	temp[i] = 0;
	(**input)--;
	return (ft_atoi(temp));
}

t_struct	create_new_struct(void)
{
	t_struct	output;

	output.vartype = 0;
	output.flag = 0;
	output.width = 0;
	output.precision = -1;
	output.output = NULL;
	output.error = 0;
	return (output);
}

char		*ft_itoa_ulong_base(unsigned long long n, int base, char vartype)
{
	char					*string;
	static char				basedict[16] = "0123456789abcdef";
	unsigned long long		n0;
	int						len;

	len = (n == 0 ? 1 : 0);
	n0 = n;
	while (n0 != 0)
	{
		len += 1;
		n0 /= base;
	}
	if (!(string = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	string[len] = 0;
	while (len >= 1)
	{
		string[len - 1] = basedict[n % base];
		n /= base;
		len--;
	}
	string = (vartype == 'X' ? ft_strupcase(string) : string);
	return (string);
}
