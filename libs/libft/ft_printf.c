/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:52:36 by mcarneir          #+#    #+#             */
/*   Updated: 2023/05/02 15:51:38 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_formats(va_list args, const char type)
{
	int	print;

	print = 0;
	if (type == 'c')
		print += ft_printchar(va_arg(args, int));
	if (type == 's')
		print += ft_printstr(va_arg(args, char *));
	if (type == 'p')
		print += ft_printptr(va_arg(args, size_t));
	if (type == 'd' || type == 'i')
		print += ft_putnbr_dec(va_arg(args, int));
	if (type == 'u')
		print += ft_putnbr_u(va_arg(args, unsigned int));
	if (type == 'x')
		print += ft_putnbr_hex(va_arg(args, unsigned int), 1);
	if (type == 'X')
		print += ft_putnbr_hex(va_arg(args, unsigned int), 0);
	if (type == '%')
		print += ft_printpercent();
	return (print);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		print;

	i = 0;
	print = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print += ft_formats(args, str[i + 1]);
			i++;
		}
		else
		{
			print += ft_printchar(str[i]);
		}
		i++;
	}
	va_end(args);
	return (print);
}
