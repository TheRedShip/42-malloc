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

	prev = block->prev;
	next = block->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (block == g_block)
		g_block = next;
	ft_printf("CALL MUNMAP %d\n", block->size);
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

	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)chunk->size);
	block->size_left += allocation_cost;
	chunk->freed = true;

	if (chunk->prev && chunk->prev->freed)
	{
		merge_chunk(chunk->prev, chunk);
		chunk = chunk->prev;
	}
	if (chunk->next && chunk->next->freed)
		merge_chunk(chunk, chunk->next);

	if (is_all_freed(block) && is_valid_block(block))
		free_block(block);
}