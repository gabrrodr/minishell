/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:27:42 by mcarneir          #+#    #+#             */
/*   Updated: 2023/08/18 14:41:19 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while ((s1[a] && s2[a]) && (s1[a] == s2[a]) && (a < n - 1))
		a++;
	if (a == n)
		return (0);
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
