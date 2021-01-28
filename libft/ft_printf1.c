/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2020/09/12 23:01:51 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_printf_coordinator(const char *input, va_list *arg, int result)
{
	static char	typedict[9] = "cspdiuxX%";
	t_struct	output;

	output = create_new_struct();
	while (*input && !output.error && result >= 0)
	{
		if (*input == '%' && *(input++) && check_ifvalid(typedict, *input, 1))
		{
			output = create_new_struct();
			read_format(&output, &input, &arg, typedict);
			result += (validate_output(&output) ? print_output(&output,
			output.vartype, output.width, output.precision) : 0);
			free(output.output);
		}
		else if (*input != '%')
		{
			while (*input && *input != '%')
			{
				result += write(1, input, 1);
				input++;
			}
		}
	}
	return ((output.error || result < 0) ? -1 : result);
}

int		ft_printf(const char *input, ...)
{
	va_list		arg;
	int			result;

	va_start(arg, input);
	result = (int)ft_printf_coordinator(input, &arg, 0);
	va_end(arg);
	return (result);
}
