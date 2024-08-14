/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:09:57 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/14 16:44:23 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

t_block				*g_block = NULL;
pthread_mutex_t		g_malloc_mutex;

t_block	*get_using_block(t_size type)
{
	t_block *using_block;
	size_t	allocation_cost;

	if (type.type == LARGE)
		return (NULL);
	
	if (!g_block)
		g_block = block_lstnew(type);
	if (g_block == MAP_FAILED)
	{
		g_block = NULL;
		return (MAP_FAILED);
	}

	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)type.user_size);
	using_block = g_block;
	while (using_block)
	{
		if (using_block->type == type.type && allocation_cost <= using_block->size_left)
			break ;
		using_block = using_block->next;
	}
	return (using_block);
}

t_chunk *get_available_chunk(t_block *block, t_size type)
{
	t_chunk *chunk;

	chunk = block->chunks;
	while (chunk)
	{
		if (chunk->freed && chunk->size >= type.user_size)
		{
			chunk->freed = false;
			return (chunk);
		}
		chunk = chunk->next;
	}
	return (chunk);
}

void	*heap_allocate(t_size type)
{
	size_t	allocation_cost;
	t_block *using_block;
	t_chunk *new_chunk;

	using_block = get_using_block(type);
	if (using_block == MAP_FAILED)
		return (NULL);
	if (!using_block)
	{
		using_block = block_lstnew(type);
		if (using_block == MAP_FAILED)
			return (NULL);
		block_lstadd_back(&g_block, using_block);
	}

	allocation_cost = (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)type.user_size);
	using_block->size_left -= allocation_cost;
	
	new_chunk = get_available_chunk(using_block, type);
	if (!new_chunk)
	{
		new_chunk = chunk_lstnew(type, using_block);
		chunk_lstadd_back(&using_block->chunks, new_chunk);
	}

	return (void *)((char *)new_chunk + (size_t)align_address((void *)sizeof(t_chunk)));
}

void	*malloc(size_t size)
{
	void	*ptr;
	t_size	type;

	pthread_mutex_lock(&g_malloc_mutex);

	type = choose_type(size);
	ptr = heap_allocate(type);
	if (get_env(ENV_PRE_SCRIBBLE))
		ft_memset(ptr, 0xAA, size);

	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}
