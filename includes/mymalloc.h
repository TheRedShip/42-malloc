/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:10:41 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/04 16:30:54 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_H__
# define __MALLOC_H__

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "libft.h"

#define PAGE_SIZE	sysconf(_SC_PAGESIZE)
#define ALIGNMENT	16

#define TINY_SIZE (size_t)(PAGE_SIZE * 4) // 16384
#define SMALL_SIZE (size_t)(PAGE_SIZE * 128) // 131072
#define LARGE_SIZE (size_t)(2147483647)

#define ALIGNED_BLOCK (size_t)(align_adress((void *)(sizeof(t_block))))
#define ALIGNED_CHUNK (size_t)(align_adress((void *)(sizeof(t_chunk))))

#define TINY_AUTHORISED_SIZE (size_t)(align_adress((void *)(((TINY_SIZE - ALIGNED_BLOCK - ALIGNED_CHUNK * 100) / 100) - ALIGNMENT)))
#define SMALL_AUTHORISED_SIZE (size_t)(align_adress((void *)(((SMALL_SIZE - ALIGNED_BLOCK - ALIGNED_CHUNK * 100) / 100) - ALIGNMENT)))

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

typedef struct s_chunk //12 bytes // 16 bytes
{
	size_t			size;
	struct s_chunk	*next;
}		t_chunk;

typedef struct s_block //24 bytes // 32 bytes
{
	t_block_size		type;
	size_t				size_left;
	t_chunk				*chunks;
	struct s_block		*next;
}		t_block;


void	*malloc(size_t size);
void	*align_adress(void *ptr);

t_block	*block_lstnew(t_size type);
void	block_lstadd_back(t_block **lst, t_block *new);
t_chunk	*chunk_lstnew(t_size type, t_block *parent);
void	chunk_lstadd_back(t_chunk **lst, t_chunk *new);

t_block	*block_lstlast(t_block *lst);
t_chunk	*chunk_lstlast(t_chunk *lst);


#endif
