/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2020/09/12 23:01:51 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_ifvalid(const char *typedict, char c, int mode)
{
	while (*typedict)
	{
		if (*typedict == c)
			return (1);
		typedict++;
	}
	return (mode == 2 ? 0 : (c == '-' || c == '0' || c == '.' || c == '*'
	|| ft_isdigit(c)));
}

void	get_output(t_struct **output, const char ***input, va_list ***arg)
{
	char	temp[2];

	if (***input == 'c')
	{
		temp[0] = (char)va_arg(***arg, int);
		temp[1] = 0;
		(*output)->output = ft_strdup(temp);
	}
	else if (***input == 's')
		(*output)->output = ft_strdup_advanced(va_arg(***arg, char *), &output,
		(*output)->precision);
	else if (***input == 'p')
		(*output)->output = ft_itoa_ulong_base(va_arg(***arg,
		unsigned long long), 16, ***input);
	else if (***input == 'd' || ***input == 'i')
		(*output)->output = ft_itoa(va_arg(***arg, int));
	else if (***input == 'u' || ***input == 'x' || ***input == 'X')
		(*output)->output = ft_itoa_ulong_base(va_arg(***arg,
		unsigned int), ***input == 'u' ? 10 : 16, ***input);
	else if (***input == '%')
	{
		(*output)->vartype = 'c';
		(*output)->output = ft_strdup("%");
	}
}

void	read_format(t_struct *output, const char **input, va_list **arg,
const char *typedict)
{
	while (**input == '-' || **input == '0')
	{
		output->flag = (output->flag == '-' ? '-' : **input);
		(*input)++;
	}
	if (**input == '*' || ft_isdigit(**input))
	{
		output->width = (**input == '*' ? va_arg(**arg, int) :
		convert_to_int(&input, &output));
		(*input)++;
	}
	if (**input == '.' && (*input)++ && (**input == '*' || ft_isdigit(**input)
	|| check_ifvalid(typedict, **input, 2)))
	{
		if ((output->precision = check_ifvalid(typedict, **input, 2) ? 0 : -1))
			output->precision = (**input == '*' ? va_arg(**arg, int) :
			convert_to_int(&input, &output));
		*input += check_ifvalid(typedict, **input, 2) ? 0 : 1;
	}
	if (check_ifvalid(typedict, **input, 2))
	{
		output->vartype = **input;
		get_output(&output, &input, &arg);
	}
	*input += (**input ? 1 : 0);
}
