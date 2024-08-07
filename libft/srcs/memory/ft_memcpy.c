/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:40:28 by rgramati          #+#    #+#             */
/*   Updated: 2024/08/07 02:46:49 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = src;
	d = dest;
	if (s == NULL && d == NULL)
		return (NULL);
	while (i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (dest);
}
