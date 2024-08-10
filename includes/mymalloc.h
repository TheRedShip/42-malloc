/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:10:41 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/10 22:49:32 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_H__
# define __MALLOC_H__

#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#define PAGE_SIZE	sysconf(_SC_PAGESIZE)
#define ALIGNMENT	16

#define TINY_SIZE (size_t)(PAGE_SIZE * 4) // 16384
#define SMALL_SIZE (size_t)(PAGE_SIZE * 256) // 524288

#define ALIGNED_BLOCK (size_t)(align_address((void *)(sizeof(t_block))))
#define ALIGNED_CHUNK (size_t)(align_address((void *)(sizeof(t_chunk))))

#define TINY_AUTHORIZED_SIZE (size_t)(align_address((void *)(((TINY_SIZE - ALIGNED_BLOCK - ALIGNED_CHUNK * 100) / 100) - ALIGNMENT)))
#define SMALL_AUTHORIZED_SIZE (size_t)(align_address((void *)(((SMALL_SIZE - ALIGNED_BLOCK - ALIGNED_CHUNK * 100) / 100) - ALIGNMENT)))

typedef enum e_env
{
	ENV_STACK_LOGGING = 1 << 0,
	ENV_PRE_SCRIBBLE = 1 << 1,
	ENV_SCRIBBLE = 1 << 2,
	ENV_LOGGING = 1 << 3
}	t_env;

typedef enum e_block_size
{
	TINY,
	SMALL,
	LARGE
}	t_block_size;

typedef struct s_size
{
	t_block_size		type;
	size_t				size;
	size_t				user_size;
}	t_size;

typedef struct s_chunk // 32 bytes
{
	size_t			size; //8
	bool			freed; //1 but 8
	struct s_chunk	*next; //8
}		t_chunk;

typedef struct s_block //44 bytes // 48 bytes
{
	t_block_size		type;
	size_t				size;
	size_t				size_left;
	t_chunk				*chunks;
	struct s_block		*next;
}		t_block;


void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);
void	show_alloc_mem();
void	free(void	*ptr);
void	free_all();

void	*align_address(void *ptr);
t_size	choose_type(size_t size);
bool	is_all_freed(t_block *block);
bool	get_env(t_env env);

bool	get_block_chunk(void *ptr, t_block **using_block, t_chunk **using_chunk);

t_block	*block_lstnew(t_size type);
void	block_lstadd_back(t_block **lst, t_block *new);
t_chunk	*chunk_lstnew(t_size type, t_block *parent);
void	chunk_lstadd_back(t_chunk **lst, t_chunk *new);

t_block	*block_lstlast(t_block *lst);
t_chunk	*chunk_lstlast(t_chunk *lst);


#endif
