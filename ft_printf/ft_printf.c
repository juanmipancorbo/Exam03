/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:37:32 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/08 23:36:13 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	put_string(char *string, int *length)
{
	if (!string)
		string = "(null)";
	while (*string)
		*length += write(1, string++, 1);
}

void	put_digit(long long int number, int base, int *length)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number >= base)
		put_digit((number / base), base, length);
	*length += write(1, &hex[number % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int		length;
	va_list	ptr;

	length = 0;
	va_start(ptr, format);
	while (*format)
	{
		if ((*format == '%') && ((*(format + 1) == 's')
				|| (*(format + 1) == 'd')
				|| (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				put_string(va_arg(ptr, char *), &length);
			else if (*format == 'd')
				put_digit((long long int)va_arg(ptr, int), 10, &length);
			else if (*format == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16,
					&length);
		}
		else
			length += write(1, format, 1);
		format++;
	}
	return (va_end(ptr), length);
}
