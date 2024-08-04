/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:30:40 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/04 17:36:49 by TheRed           ###   ########.fr       */
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
	ft_printf("starting mallocs : %d * 101 / %d\n", TINY_AUTHORISED_SIZE, TINY_SIZE);
	for (size_t i = 0; i <= 101; i++)
	{
		t_block *ptr = malloc(TINY_AUTHORISED_SIZE);
		test_malloc(ptr);
	}

	ft_printf("\n\n");
	ft_printf("starting mallocs : %d * 101 / %d\n", SMALL_AUTHORISED_SIZE, SMALL_SIZE);
	for (size_t i = 0; i < 100; i++)
	{
		t_block *ptr = malloc(SMALL_AUTHORISED_SIZE);
		test_malloc(ptr);
	}
	
	malloc(TINY_AUTHORISED_SIZE);
	malloc(SMALL_AUTHORISED_SIZE);

	ft_printf("\nstarting strs\n");
	for (size_t i = 0; i <= 14; i++)
	{
		char *ptr = malloc(sizeof(char) * 100);
		ft_printf("%d ptr: %p\n", i, ptr);
		test_strwrite(ptr, i);
	}


	void *ptr = malloc(0);
	ft_printf("\n\nAllocation réussie pour 0 octets: %p\n\n", ptr);


	size_t test_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
	for (size_t i = 0; i < sizeof(test_sizes) / sizeof(test_sizes[0]); i++)
		ft_printf("malloc(%d) : %p\n", test_sizes[i], malloc(test_sizes[i]));
	ft_printf("\n\n");
	show_alloc_mem();

	return (0);
}
