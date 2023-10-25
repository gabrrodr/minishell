/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:34:51 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/05/03 14:46:54 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pointer(size_t ptr)
{
	int	len;

	if (ptr == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	len = 0;
	ft_putstr("0x");
	len = ft_dohex(ptr, 'x');
	return (len + 2);
}
