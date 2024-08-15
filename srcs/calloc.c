/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:33:15 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/15 18:26:01 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

extern pthread_mutex_t	g_malloc_mutex;

void	*calloc(size_t count, size_t size)
{
	return (ft_calloc(count, size));
}