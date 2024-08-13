/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 02:34:46 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/07 02:34:46 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

extern t_block			*g_block;
extern pthread_mutex_t	g_malloc_mutex;

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_block	*using_block;
	t_chunk *using_chunk;
	size_t	allocation_cost;

	if ((size_t)align_address((void *)size) >= 4294967290 || !ptr)
		return (NULL);

	pthread_mutex_lock(&g_malloc_mutex);
	if (!get_block_chunk(ptr, &using_block, &using_chunk) || using_chunk->freed)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		ft_printf("realloc: Invalid address\n");
		exit(1);
	}

	if (using_chunk->size == size)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (ptr);
	}

	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)size);
	if (using_chunk->next == NULL && using_block->size_left >= allocation_cost)
	{
		using_chunk->size = size;
		using_block->size_left -= allocation_cost;
		if (getenv("MyMallocPreScribble"))
			ft_memset(ptr, 0xaa, size);

		pthread_mutex_unlock(&g_malloc_mutex);
		return (ptr);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, using_chunk->size);
	free(ptr);
	return (new_ptr);
}