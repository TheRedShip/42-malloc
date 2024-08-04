/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:40:00 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/04 17:40:00 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

extern t_block	*g_block;

t_chunk	*search_ptr(void *ptr)
{
	t_block	*block;
	t_chunk	*chunk;
	void	*chunk_ptr;

	block = g_block;
	while (block)
	{
		chunk = block->chunks;
		while (chunk)
		{
			chunk_ptr = (void *)((char *)chunk + (size_t)align_address((void *)sizeof(t_chunk)));
			if (ptr == chunk_ptr)
				return (chunk);

			chunk = chunk->next;
		}
		block = block->next;
	}
	return (NULL);
}

void	myfree(void	*ptr)
{
	t_chunk *chunk;

	chunk = search_ptr(ptr);
	munmap(chunk, (size_t)align_address((void *)sizeof(t_chunk)) + chunk->size);
}