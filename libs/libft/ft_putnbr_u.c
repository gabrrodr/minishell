/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:46:57 by mcarneir          #+#    #+#             */
/*   Updated: 2023/05/02 15:51:18 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_size_u(unsigned int n)
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
		n = n / 10;
	}
	return (i);
}

int	ft_putnbr_u(unsigned int n)
{
	unsigned int	len;

	len = f_size_u(n);
	if (n >= 10)
	{
		ft_putnbr_u(n / 10);
		ft_putnbr_u(n % 10);
	}
	if (n < 10)
	{
		ft_printchar(n + '0');
	}
	return (len);
}
