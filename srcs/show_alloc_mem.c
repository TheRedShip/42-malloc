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

size_t	get_chunks_bytes(char *buf, bool reset)
{
	static t_block	*block = NULL;
	static t_chunk	*chunk = NULL;
	static size_t	offset = 0;
	char			*addr = NULL;
	size_t			i = 0;

	if (!g_block)
		return (0);
	if (reset)
	{
		block = g_block;
		chunk = block->chunks;
		offset = 0;
		return (0);
	}
	while (block)
	{
		while (chunk)
		{
			addr = (char *)chunk + (size_t)align_address((void *)sizeof(t_chunk));
			while (offset < chunk->size)
			{
				if (i == 16)
					return (i);
				buf[i] = addr[offset];
				offset++;
				i++;
			}
			offset = 0;
			chunk = chunk->next;
		}
		block = block->next;
		if (block)
			chunk = block->chunks;
	}
	return (i);
}

void	print_header_line(size_t bytes)
{
	size_t	num;
	size_t	size;

	num = 16;
	size = 0;
	while (num <= bytes && ++size > 0)
		num *= 16;
	while (7 - size++ != 0)
		write(1, "0", 1);
	ft_printf("%X  ", bytes);
}

void	show_alloc_mem_ex()
{
	char	buf[16];
	size_t	bytes;
	size_t	ret;

	bytes = 0;
	get_chunks_bytes(NULL, true);
	while ((ret = get_chunks_bytes(buf, false)))
	{
		print_header_line(bytes);

		for (size_t i = 0; i < ret; i++)
		{
			if (i == 8)
				write(1, " ", 1);
			print_address(buf[i], 0);
			write(1, " ", 1);
		}
		for (size_t i = ret; i < 16; i++)
		{
			if (i == 8)
				write(1, " ", 1);
			write(1, "   ", 3);
		}

		write(1, "|", 1);
		for (size_t i = 0; i < ret; i++)
		{
			if (ft_is_printable(buf[i]))
				ft_putchar_fd(1, buf[i]);
			else
				write(1, ".", 1);
		}
		write(1, "|\n", 2);

		bytes += ret;
	}
	if (bytes)
	{
		print_header_line(bytes);
		write(1, "\n", 1);
	}
}
