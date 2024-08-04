/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:09:57 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/05 01:44:43 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

t_block *g_block = NULL;

t_block	*get_using_block(t_size type)
{
	int i = 0; // TODO: remove
	t_block *using_block;
	size_t	allocation_cost;

	if (!g_block)
		g_block = block_lstnew(type); //need to check failure

	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)type.user_size);
	using_block = g_block;
	while (using_block)
	{
		if (using_block->type == type.type && allocation_cost <= using_block->size_left)
			break ;
		i++;
		using_block = using_block->next;
	}
	if (!using_block)
		ft_printf("NEW using block id: %d size left : %u\n", i, type.size - (size_t)align_address((void *)sizeof(t_block)));
	else
		ft_printf("using block id: %d size left : %u\n", i, using_block->size_left - allocation_cost);
	return (using_block);
}

void	*heap_allocate(t_size type)
{
	size_t	allocation_cost;
	t_block *using_block;
	t_chunk *new_chunk;

	using_block = get_using_block(type);
	if (!using_block)
	{
		using_block = block_lstnew(type);
		block_lstadd_back(&g_block, using_block);
	}
	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)type.user_size);
	using_block->size_left -= allocation_cost;
	
	new_chunk = chunk_lstnew(type, using_block);
	chunk_lstadd_back(&using_block->chunks, new_chunk);

	return (void *)((char *)new_chunk + (size_t)align_address((void *)sizeof(t_chunk)));
}

void	*mymalloc(size_t size)
{
	t_size	type;

	type = choose_type(size);
	return (heap_allocate(type));
}
