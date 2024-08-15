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

extern t_block			*g_block;
extern pthread_mutex_t	g_malloc_mutex;

void	free_all() __attribute__((destructor));

void	free_all()
{
	t_block	*block;
	t_block	*next;

	block = g_block;
	while (block)
	{
		next = block->next;
		munmap(block, block->size);
		block = next;
	}

	g_block = NULL;
}

void	free_block(t_block *block)
{
	t_block	*prev;
	t_block	*next;

	log("Freeing block %p of size %u bytes", block, block->size);

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

bool	is_valid_block(t_block *block)
{
	t_block	*using_block;
	t_block	*tmp;

	if (block->type == LARGE)
		return (true);

	tmp = g_block;
	while (tmp)
	{
		if (tmp->type == block->type)
			using_block = tmp;
		tmp = tmp->next;
	}
	if (using_block != block)
		return (true);
	return (false);
}

void	merge_chunk(t_chunk *chunk, t_chunk *next_chunk)
{
	log("Freed defragmentation of %p and %p", chunk, next_chunk);

	chunk->next = next_chunk->next;
	if (next_chunk->next)
		next_chunk->next->prev = chunk;

	chunk->size += next_chunk->size + (size_t)align_address((void *)sizeof(t_chunk));
}

void	free(void	*ptr)
{
	size_t	allocation_cost;
	t_block	*block = NULL;
	t_chunk *chunk = NULL;

	if (!ptr)
		return ;

	pthread_mutex_lock(&g_malloc_mutex);
	log("Trying to free %p", ptr);

	if (!get_block_chunk(ptr, &block, &chunk) || chunk->freed)
	{
		ft_dprintf(2, "free(): invalid pointer\n");
		pthread_mutex_unlock(&g_malloc_mutex);
		return ;
	}

	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)chunk->size);
	block->size_left += allocation_cost;
	chunk->freed = true;
	
	if (get_env(ENV_SCRIBBLE))
	{
		ft_memset(ptr, 0x55, chunk->size);
		log("EnvScribble Detected setting %p to 0x55", ptr);
	}
	if (chunk->prev && chunk->prev->freed)
	{
		merge_chunk(chunk->prev, chunk);
		chunk = chunk->prev;
	}
	if (chunk->next && chunk->next->freed)
		merge_chunk(chunk, chunk->next);

	if (is_all_freed(block) && is_valid_block(block))
		free_block(block);
	else
		log("Chunk %p from ptr %p is set to free\n", chunk, ptr);
	pthread_mutex_unlock(&g_malloc_mutex);
}
