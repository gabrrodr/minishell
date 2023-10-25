/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:16:07 by mcarneir          #+#    #+#             */
/*   Updated: 2023/05/02 15:51:03 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_dec(int n)
{
	int	len;

	len = f_size(n);
	if (n == -2147483648)
	{
		ft_printchar('-');
		ft_printchar('2');
		n = 147483648;
	}
	if (n < 0)
	{
		ft_printchar ('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_dec(n / 10);
		ft_putnbr_dec(n % 10);
	}
	if (n < 10)
	{
		ft_printchar(n + '0');
	}
	return (len);
}
