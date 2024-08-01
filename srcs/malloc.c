/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:09:57 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/01 18:15:26 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

t_block *block = NULL;

void *alignAdress(void *ptr)
{
	if (((size_t)ptr) % ALIGNMENT != 0)
		ptr += ALIGNMENT - (((size_t)ptr) % ALIGNMENT);
	return (ptr);
}

t_size choose_type(size_t size)
{
	t_size	type;
	
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

t_block *init_heap(size_t size, t_size type)
{
	t_block				*ptr;
	
	ptr = mmap(NULL, type.size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	ptr->type = type.type;
	ptr->size_left = type.size;
	ptr->chunks = NULL;
	ptr->next = NULL;
	
	(void) size;
	return (ptr);
}

void allocate_block(size_t size, t_size type)
{
	
}

void *malloc(size_t size)
{
	t_size	type;

	type = choose_type(size);
	if (!block)
		block = init_heap(size, type);
	else
		allocate_block(size, type);
		
	ft_printf("%p\n", block);

	(void) size;
	return (NULL);	
}
