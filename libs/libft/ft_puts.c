/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:53:41 by mcarneir          #+#    #+#             */
/*   Updated: 2023/05/02 15:51:24 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_printstr ("(null)");
		return (6);
	}
	while (str[i])
	{
		ft_printchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_printpercent(void)
{
	ft_printchar('%');
	return (1);
}

/*
int main(void)
{
	char	str[] = "Hello";
	ft_putstr(str);
	ft_putchar('\n');
}
*/