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

	chunk->freed = true;
	if (is_all_freed(block))
		free_block(block);
}