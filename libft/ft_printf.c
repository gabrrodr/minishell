/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:26:12 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/05/05 12:12:53 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print(va_list args, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (c == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		len += ft_pointer(va_arg(args, size_t));
	else if (c == 'x')
		len += ft_dohex(va_arg(args, unsigned int), c);
	else if (c == 'X')
		len += ft_dohex(va_arg(args, unsigned int), c);
	else if (c == 'i')
		len += ft_putnbr_dec(va_arg(args, unsigned int));
	else if (c == 'd')
		len += ft_putnbr_dec(va_arg(args, int));
	else if (c == 'u')
		len += ft_putnbr(va_arg(args, unsigned int));
	else if (c == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	args;
	int		len;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			len += print(args, format[i]);
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
