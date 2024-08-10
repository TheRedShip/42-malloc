/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:50:14 by rgramati          #+#    #+#             */
/*   Updated: 2024/08/10 15:48:11 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void					*ptr;
	long long unsigned		len;

	ptr = NULL;
	len = nmemb * size;
	if ((long long)nmemb == 0 || (long long)size == 0)
		return (malloc(1));
	if ((long long)nmemb < 0 || (long long)size < 0 || len > __SIZE_MAX__)
		return (ptr);
	ptr = malloc(len);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, len);
	return (ptr);
}
