/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2020/09/12 23:01:51 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		validate_output(t_struct *output)
{
	if (output->width < 0)
	{
		output->width *= -1;
		output->flag = '-';
	}
	if (output->vartype && !output->output)
		output->error = 1;
	if (!output->precision && output->output && output->output[0] == '0'
	&& !(output->output[1]))
		output->output[0] = 0;
	if (output->precision >= 0 && output->flag == '0')
		output->flag = 0;
	if ((output->vartype == 'd' || output->vartype == 'i')
	&& output->flag == '0')
	{
		output->precision = output->precision < 0 ? output->width
		: output->precision + output->width;
		output->precision -= output->output[0] == '-' ? 1 : 0;
		output->width = 0;
	}
	return ((output->error || !output->vartype) ? 0 : 1);
}

long	print_delimiters(char c, int len, int target)
{
	char	*delimiters;

	if (target >= len)
		return (0);
	if (!(delimiters = malloc((len - target + 1) * sizeof(char))))
		return (-2147483649);
	delimiters = ft_memset(delimiters, (int)c, len - target);
	write(1, delimiters, len - target);
	free(delimiters);
	return (len - target);
}

long	ft_putstr_advanced(char *s, char vartype, int precision, int maxlen)
{
	int		result;
	int		negative;
	int		delimiters;

	result = (vartype == 'c' && !s[0]) ? 1 : 0;
	delimiters = 0;
	vartype == 'p' ? write(1, "0x", 2) : write(1, "", 0);
	if ((negative = ((vartype == 'd' || vartype == 'i') && s[0] == '-')))
	{
		maxlen -= write(1, "-", 1);
		s++;
	}
	if (vartype != 'c' && vartype != 's')
	{
		if ((delimiters = print_delimiters('0', precision, maxlen)) <
		(negative ? 0 : -1))
			return (-2147483649);
	}
	result += ft_strlen(s);
	write(1, s, result);
	return (result + delimiters + negative + (vartype == 'p' ? 2 : 0));
}

int		max(int a, int b, int c)
{
	if (a >= b && a >= c)
		return (a);
	if (b >= a && b >= c)
		return (b);
	return (c);
}

long	print_output(t_struct *output, char vartype, int width, int precision)
{
	int		result;
	int		maxlen;

	result = 0;
	maxlen = ft_strlen(output->output) + (vartype == 'c' &&
	!output->output[0] ? 1 : 0);
	if (output->flag == '-')
		result += ft_putstr_advanced(output->output, vartype, precision,
		maxlen);
	result += print_delimiters(output->flag == '0' ? '0' : ' ', width,
	((precision && vartype != 'c' && vartype != 's') ? max(precision, maxlen, 0)
	: maxlen) + (((vartype == 'd' || vartype == 'i') && *(output->output) == '-'
	&& precision >= maxlen) ? 1 : 0) + (vartype == 'p' ? 2 : 0));
	if (output->flag != '-')
		result += ft_putstr_advanced(output->output, vartype, precision,
		maxlen);
	return (result < 0 ? -2147483649 : result);
}
