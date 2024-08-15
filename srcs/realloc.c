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

void	*get_new_ptr(size_t size, t_block *block, t_chunk *chunk, void *ptr)
{
	void	*new_ptr;
	size_t	allocation_cost;

	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)size);
	if (chunk->next == NULL && block->size_left >= allocation_cost)
	{
		chunk->size = size;
		block->size_left -= allocation_cost;

		log("Reallocated in same pointer %p\n", ptr);
		pthread_mutex_unlock(&g_malloc_mutex);
		return (ptr);
	}
	pthread_mutex_unlock(&g_malloc_mutex);

	log("--------Realloc: Needing new allocation--------\n");
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, chunk->size);
	free(ptr);
	log("--------Realloc: New pointer %p --------\n", new_ptr);
	return (new_ptr);
}

void	*_realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_chunk *chunk;

	if ((size_t)align_address((void *)size) >= 4294967290 || !ptr)
		return (NULL);

	pthread_mutex_lock(&g_malloc_mutex);
	if (!get_block_chunk(ptr, &block, &chunk) || chunk->freed)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		ft_dprintf(2, "realloc(): invalid pointer\n");
		return (NULL);
	}

	if (chunk->size == size)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (ptr);
	}

	log("Reallocating %p from chunk %p (%u bytes) to %u bytes", ptr, chunk, chunk->size, size);
	return (get_new_ptr(size, block, chunk, ptr));
}