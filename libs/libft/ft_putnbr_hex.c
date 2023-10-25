/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:50:16 by mcarneir          #+#    #+#             */
/*   Updated: 2023/05/02 15:51:12 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_size_hex(size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n > 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

int	ft_putnbr_hex(size_t n, int uplow)
{
	int	len;

	len = f_size_hex(n);
	if (n >= 16)
	{
		ft_putnbr_hex(n / 16, uplow);
		ft_putnbr_hex(n % 16, uplow);
	}
	if (n < 16)
	{
		if (uplow)
			write(1, &"0123456789abcdef"[n], 1);
		else
			write(1, &"0123456789ABCDEF"[n], 1);
	}
	return (len);
}
