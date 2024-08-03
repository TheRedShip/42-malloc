/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:30:40 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/04 01:57:37 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/mymalloc.h"
#include <stdlib.h>

extern t_block	*g_block;

void	test_malloc(t_block *ptr)
{
	ptr->chunks = (void *)(ptr);
	ptr->size_left = 100;
	ptr->type = TINY;
	ptr->next = (void *)ptr;
}

void	test_strwrite(char *str, size_t size)
{
	ft_strlcpy(str, "Hello, World!", size);
	ft_printf("%s\n", str);
}

int main(void)
{
	for (size_t i = 0; i <= 100000; i++)
	{
		t_block *ptr = malloc(sizeof(t_block));
		test_malloc(ptr);
	}
	
	for (size_t i = 0; i <= 14; i++)
	{
		char *ptr = malloc(sizeof(char) * 100);
		test_strwrite(ptr, i);
	}

	return (0);
}