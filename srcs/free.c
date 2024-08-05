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

bool get_block_chunk(void *ptr, t_block **using_block, t_chunk **using_chunk)
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
			{
				*using_block = block;
				*using_chunk = chunk;
				return (true); 
			}

			chunk = chunk->next;
		}
		block = block->next;
	}
	return (false);
}

void	free_block(t_block *block)
{
	t_block	*prev;
	t_block	*next;

	prev = block->prev;
	next = block->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (block == g_block)
		g_block = next;
	
	munmap(block, block->size);
}

void	free(void	*ptr)
{
	t_block	*block = NULL;
	t_chunk *chunk = NULL;

	if (!get_block_chunk(ptr, &block, &chunk))
	{
		ft_printf("Invalid free\n");
		exit(1);
	}
	if (chunk->freed)
	{
		ft_printf("Double free\n");
		exit(1);
	}

	chunk->freed = true;
	if (is_all_freed(block))
		free_block(block);
}