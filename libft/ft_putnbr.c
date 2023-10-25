/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:11:35 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/05/02 14:01:42 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

int	ft_putnbr(unsigned int n)
{
	unsigned int	len;

	len = length(n);
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + 48);
	return (len);
}
