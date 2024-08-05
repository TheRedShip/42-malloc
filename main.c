/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:30:40 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/05 19:47:01 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/mymalloc.h"

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

void	test_mallocs()
{
	ft_printf("starting mallocs : %d * 101 / %d\n", TINY_AUTHORISED_SIZE, TINY_SIZE);
	for (size_t i = 0; i <= 1000; i++)
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
	
	void *daccordmaisporuquoipas = malloc(TINY_AUTHORISED_SIZE);
	daccordmaisporuquoipas = malloc(SMALL_AUTHORISED_SIZE);
	(void) daccordmaisporuquoipas;
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
}

int main(void)
{
	
	// test_mallocs();
	// show_alloc_mem();
	
	munmap(NULL, 0);
	
	for (int i = 0; i < 1000; i++)
	{
		void *ptr = malloc(5);
		void *ptr2 = malloc(5);
		void *ptr3 = malloc(5);

		(void) ptr;
		(void) ptr2;
		(void) ptr3;
		
		// free(ptr);
		// free(ptr2);
		// free(ptr3);
	}

	return (0);
}
