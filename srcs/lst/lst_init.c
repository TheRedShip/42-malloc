/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 00:23:58 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/02 00:23:58 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

extern t_block	*g_block;

t_block	*block_lstnew(t_size type)
{
	t_block				*ptr;
	
	ptr = mmap(NULL, type.size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	ptr->type = type.type;
	ptr->size_left = type.size - (size_t)align_address((void *)sizeof(t_block));
	ptr->chunks = NULL;
	ptr->next = NULL;
	return (ptr);
}

void	block_lstadd_back(t_block **lst, t_block *new)
{
	t_block	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = block_lstlast(*lst);
	last->next = new;
}

t_chunk	*chunk_lstnew(t_size type, t_block *parent)
{
	size_t		offset;
	t_chunk		*temp;
	t_chunk		*ptr;

	temp = parent->chunks;
	offset = sizeof(t_block);
	while (temp)
	{
		offset += (size_t)align_address((void *)sizeof(t_chunk)) + (size_t)align_address((void *)temp->size);
		temp = temp->next;
	}

	ptr = (t_chunk *)((void *)parent + offset);
	ptr->size = type.user_size;
	ptr->next = NULL;
	return (ptr);
}

void	chunk_lstadd_back(t_chunk **lst, t_chunk *new)
{
	t_chunk	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = chunk_lstlast(*lst);
	last->next = new;
}