/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 00:29:33 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/02 00:29:33 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

t_block	*block_lstlast(t_block *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_chunk	*chunk_lstlast(t_chunk *lst)
{
	int i = 0; // TODO: remove
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}