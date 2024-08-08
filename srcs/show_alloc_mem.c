/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:54:59 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/04 16:54:59 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

extern t_block	*g_block;

void	show_block(t_block *block)
{
	char	*base_address;

	base_address = (char *)block + (size_t)align_address((void *)sizeof(t_block));
	if (block->type == 0)
		ft_printf("TINY : 0x%X\n", base_address);
	else if (block->type == 1)
		ft_printf("SMALL : 0x%X\n", base_address);
	else
		ft_printf("LARGE : 0x%X\n", base_address);
}

void	show_chunks(t_chunk *chunks, size_t *total)
{
	char	*base_address;
	char	*end_address;
	t_chunk *chunk;

	chunk = chunks;
	while (chunk)
	{
		if (chunk->freed)
		{
			chunk = chunk->next;
			continue ;
		}

		base_address = (char *)chunk + (size_t)align_address((void *)sizeof(t_chunk));
		end_address = base_address + chunk->size;
		*total += chunk->size;
		
		ft_printf("   0x%X - 0x%X : %u bytes\n", base_address, end_address, chunk->size);

		chunk = chunk->next;
	}
}

void	show_alloc_mem()
{
	t_block	*temp;
	size_t	total;

	total = 0;
	temp = g_block;
	while (temp)
	{
		if (!is_all_freed(temp))
		{
			show_block(temp);
			show_chunks(temp->chunks, &total);
		}
		temp = temp->next;
	}
	ft_printf("Total : %u bytes\n", total);
}