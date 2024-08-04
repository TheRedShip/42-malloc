/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:09:57 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/04 02:03:58 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

t_block *g_block = NULL;

void	*align_adress(void *ptr)
{
	if (((size_t)ptr) % ALIGNMENT != 0)
		ptr += ALIGNMENT - (((size_t)ptr) % ALIGNMENT);
	return (ptr);
}

t_size	choose_type(size_t size)
{
	t_size	type;
	
	type.user_size = size;
	if (size <= TINY_AUTHORISED_SIZE)
	{
		type.size = TINY_SIZE;
		type.type = TINY;
	}
	else if (size <= SMALL_AUTHORISED_SIZE)
	{
		type.size = SMALL_SIZE;
		type.type = SMALL;
	}
	else
	{
		type.size = LARGE_SIZE;
		type.type = LARGE;
	}
	return (type);
}

t_block	*get_using_block(t_size type)
{
	int i = 0; // TODO: remove
	t_block *using_block;
	size_t	allocation_cost;

	if (!g_block)
		block_lstadd_back(&g_block, block_lstnew(type));
	using_block = g_block;
	while (using_block)
	{
		allocation_cost = (size_t)align_adress((void *)sizeof(t_chunk)) + type.user_size;
		if (using_block->type == type.type && allocation_cost <= using_block->size_left)
			break ;
		i++;
		using_block = using_block->next;
	}
	if (!using_block)
		ft_printf("NEW using block id: %d size left : %u\n", i, type.size - (size_t)align_adress((void *)sizeof(t_block)));
	else
		ft_printf("using block id: %d size left : %u\n", i, using_block->size_left);
	return (using_block);
}

void	*heap_allocate(t_size type)
{
	t_block *using_block;
	t_chunk *new_chunk;

	using_block = get_using_block(type);
	if (!using_block)
	{
		using_block = block_lstnew(type);
		block_lstadd_back(&g_block, using_block);
	}
	using_block->size_left -= (size_t)align_adress((void *)type.user_size) + (size_t)align_adress((void *)sizeof(t_chunk));
	
	new_chunk = chunk_lstnew(type, using_block);
	chunk_lstadd_back(&using_block->chunks, new_chunk);

	return (new_chunk + sizeof(t_chunk));
}

void	*malloc(size_t size)
{
	t_size	type;

	type = choose_type(size);
	return (heap_allocate(type));
}
