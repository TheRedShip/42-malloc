/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:30:40 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/10 23:05:06 by ycontre          ###   ########.fr       */
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

void *ptr[1000000];

void	test_mallocs()
{
	ft_printf("starting mallocs : %d * 101 / %d\n", TINY_AUTHORIZED_SIZE, TINY_SIZE);
	for (size_t i = 0; i <= 101; i++)
	{
		ptr[i] = malloc(TINY_AUTHORIZED_SIZE);
		if (ptr[i])
			test_malloc((void *)ptr[i]);
	}

	ft_printf("\n\n");
	ft_printf("starting mallocs : %d * 101 / %d\n", SMALL_AUTHORIZED_SIZE, SMALL_SIZE);
	for (size_t i = 102; i < 102 + 100; i++)
	{
		ptr[i] = malloc(SMALL_AUTHORIZED_SIZE);
		if (ptr[i])
			test_malloc((void *)ptr[i]);
	}
	
	void *temp;
	temp = malloc(TINY_AUTHORIZED_SIZE);
	temp = malloc(SMALL_AUTHORIZED_SIZE);

	ft_printf("\nstarting strs\n");
	for (size_t i = 0; i <= 14; i++)
	{
		char *ptr = malloc(sizeof(char) * 100);
		ft_printf("%d ptr: %p\n", i, ptr);
		if (ptr)
			test_strwrite(ptr, i);
	}

	temp = malloc(0);

	(void) temp;

	size_t test_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
	for (size_t i = 0; i < sizeof(test_sizes) / sizeof(test_sizes[0]); i++)
	{
		ft_printf("malloc(%d) : %p\n", test_sizes[i], malloc(test_sizes[i]));
	}
	ft_printf("\n\n");

	for (size_t i = 0; i <= 201; i++)
	{
		free(ptr[i]);
	}
	show_alloc_mem();
}

void	test_realloc()
{
	void *ptr;
	void *ptr2;

	ptr2 = malloc(100);
	ptr = malloc(100);
	ptr = malloc(100);
	ptr = malloc(100);
	ptr = malloc(100);

	show_alloc_mem();
	ft_printf("\n");

	ptr = realloc(ptr, 200);
	ptr2 = realloc(ptr2, 500);

	show_alloc_mem();
}

void test_free()
{
	for (int i = 0; i < 4; i ++)
	{
		void *ptr2 = malloc(100);
		test_malloc((t_block *)ptr2);
	}

	void *ptr = malloc(100);
	ft_printf("%p keep value %d\n", ptr, ((t_block *)ptr)->size_left);
	((t_block *)ptr)->size_left = 5;

	for (int i = 0; i < 4; i ++)
	{
		void *ptr2 = malloc(100);
		test_malloc((t_block *)ptr2);
	}

	show_alloc_mem();
	ft_printf("\n");

	free(ptr);
	
	show_alloc_mem();
	ft_printf("\n");
	
	ptr = malloc(100);
	ft_printf("%p still keep value %d\n", ptr, ((t_block *)ptr)->size_left);

	show_alloc_mem();

	//new test
	ft_printf("\n\n");
	free_all();

	ptr = malloc(100);
	((t_block *)ptr)->size_left = 5;
	free(ptr);

	for (int i = 0; i < 4; i ++)
	{
		void *ptr2 = malloc(100);
		test_malloc((t_block *)ptr2);
		free(ptr2);
	}

	ptr = malloc(100);
	ft_printf("%p doesn't keep value since all chunk freed %d\n", ptr, ((t_block *)ptr)->size_left);
	
	show_alloc_mem();
	free(ptr);
	show_alloc_mem();
}

void	test_page_fault()
{
	void *ptr[100];
	for (int i = 0; i < 100; i++)
	{
		ptr[i] = malloc(SMALL_AUTHORIZED_SIZE);
		test_malloc((t_block *)ptr[i]);
		free(ptr[i]);
	}
	
	show_alloc_mem();
}

void	test_defrag()
{
	void *ptr = malloc(SMALL_AUTHORIZED_SIZE);
	void *ptr2 = malloc(SMALL_AUTHORIZED_SIZE);
	void *ptr3 = malloc(SMALL_AUTHORIZED_SIZE);
	(void) ptr;
	(void) ptr2;
	(void) ptr3;
	
	free(ptr);
	free(ptr2);
	free(ptr3);
	show_alloc_mem();
}

void	test_env()
{
	//need to setup env variables : MyMallocPreScribble
	char *ptr = malloc(15);
	for (int i = 0; i < 15; i++)
		ft_printf("%X\n", ptr[i]);

	//need to setup env variables : MyMallocScribble
	free(ptr);
	for (int i = 0; i < 15; i++)
		ft_printf("%X\n", ptr[i]);
}

#define malloc(X) ch_debug_malloc(X, __FILE__, __LINE__, __FUNCTION__)

#undef malloc

ch_debug_malloc(size_t size, const char *file, int line, const char *func)
{
	void *ptr = malloc(size);
	
	
	return (ptr);
}

int main(int ac, char **av, char **env)
{
	// test_mallocs();
	// test_realloc();
	// test_free();
	// test_page_fault();
	// test_defrag();
	// test_env();
	
	ft_printf("%s\n", __FUNCTION__);
	// int i;
	// char *addr;

	// i = 0;
	// while (i < 1024)
	// {
	// 	addr = (char*)malloc(1024);
	// 	addr[0] = 42;
	// 	i++;
	// }
	// show_alloc_mem();
	return (0);
}
