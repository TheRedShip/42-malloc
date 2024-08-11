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

void	print_address(unsigned nb, int depth)
{
	if (nb >= 16)
		print_address(nb / 16, depth + 1);
	else if (depth == 0)
		ft_printf("0");
	if (depth < 2)
		ft_putchar_fd(1, "0123456789ABCDEF"[nb % 16]);
}

void	show_chunk_ex(t_chunk *chunk, size_t *bytes)
{
	char	*base_address;

	for (size_t i = 0; i < (chunk->size / 16) + (chunk->size % 16 != 0) + 1; i++)
	{
		size_t	num = *bytes;
		size_t	size = 0;
		while (num >= 16)
		{
			num /= 16;
			size++;
		}
		for (size_t i = 0; i < 7 - size; i++)
			write(1, "0", 1);
		ft_printf("%X", *bytes);

		for (size_t j = 0; j < 16; j+=2)
		{
			size_t	offset = i * 16 + j;
			if (offset >= chunk->size)
				break;
			if (j % 2 == 0)
				write(1, " ", 1);

			base_address = (char *)chunk + (size_t)align_address((void *)sizeof(t_chunk));
			print_address(base_address[offset + 1], 0);
			print_address(base_address[offset], 0);
			
			*bytes += base_address[offset + 1] != 0;
			*bytes += base_address[offset] != 0;
		}
		write(1, "\n", 1);
	}
}

void	show_alloc_mem_ex()
{
	t_chunk *chunk;
	t_block *temp;
	size_t	bytes;
	size_t	total;

	bytes = 0;
	total = 0;
	temp = g_block;
	while (temp)
	{
		if (!is_all_freed(temp))
		{
			chunk = temp->chunks;
			while (chunk && !chunk->freed)
			{
				show_chunk_ex(chunk, &bytes);
				total += chunk->size;
				chunk = chunk->next;
			}
		}
		temp = temp->next;
	}
	ft_printf("Total : %u bytes\n", total);
}