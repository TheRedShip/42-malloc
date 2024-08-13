/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:33:15 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/13 13:58:17 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

extern pthread_mutex_t	g_malloc_mutex;

void	*calloc(size_t count, size_t size)
{
	pthread_mutex_lock(&g_malloc_mutex);
	return (ft_calloc(count, size));
	pthread_mutex_unlock(&g_malloc_mutex);
}