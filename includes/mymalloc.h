/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:10:41 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/01 18:09:36 by ycontre          ###   ########.fr       */
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
#define SMALL_SIZE (size_t)(PAGE_SIZE * 32) // 131072
#define LARGE_SIZE (size_t)(2147483647)

#define ALIGNED_BLOCK (size_t)(alignAdress((void *)(sizeof(t_block))))
#define ALIGNED_CHUNK (size_t)(alignAdress((void *)(sizeof(t_chunk))))

#define TINY_AUTHORISED_SIZE (size_t)(alignAdress((void *)(((TINY_SIZE - ALIGNED_BLOCK - ALIGNED_CHUNK * 100) / 100) - ALIGNMENT)))
#define SMALL_AUTHORISED_SIZE (size_t)(alignAdress((void *)(((SMALL_SIZE - ALIGNED_BLOCK - ALIGNED_CHUNK * 100) / 100) - ALIGNMENT)))

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
}	t_size;

typedef struct s_chunk //12 bytes
{
	int				size;
	struct s_chunk	*next;
}		t_chunk;

typedef struct s_block //24 bytes
{
	t_block_size		type;
	int					size_left;
	t_chunk				*chunks;
	struct s_block		*next;
}		t_block;



#endif
