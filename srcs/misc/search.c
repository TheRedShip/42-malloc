/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 02:32:41 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/07 02:32:41 by TheRed           ###   ########.fr       */
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