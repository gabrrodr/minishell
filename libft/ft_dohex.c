/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:01:54 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/05/02 14:00:03 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	do_len(size_t n)
{
	int	len;

	len = 1;
	while (n > 15)
	{
		n /= 16;
		len ++;
	}
	return (len);
}

int	ft_dohex(size_t n, char c)
{
	int	len;

	len = do_len(n);
	if (n > 15)
	{
		ft_dohex(n / 16, c);
		ft_dohex(n % 16, c);
	}
	else
	{
		if (c == 'x')
		{
			ft_putchar(BASE_LOWER[n]);
		}
		else
			ft_putchar(BASE_UPPER[n]);
	}
	return (len);
}
