/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:49:00 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/04 16:49:00 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

void	*align_address(void *ptr)
{
	if (((size_t)ptr) & (ALIGNMENT - 1))
		ptr += ALIGNMENT - (((size_t)ptr) & (ALIGNMENT - 1));
	return (ptr);
}

t_size	choose_type(size_t size)
{
	t_size	type;
	
	type.user_size = size;
	if (size <= TINY_AUTHORIZED_SIZE) // 144
	{
		type.size = TINY_SIZE;
		type.type = TINY;
	}
	else if (size <= SMALL_AUTHORIZED_SIZE) // 5000
	{
		type.size = SMALL_SIZE;
		type.type = SMALL;
	}
	else
	{
		type.size = -1;
		type.type = LARGE;
	}
	return (type);
}

bool	is_all_freed(t_block *block)
{
	t_chunk *temp;

	temp = block->chunks;
	while (temp)
	{
		if (!temp->freed)
			return (false);
		temp = temp->next;
	}
	return (true);
}

bool	get_env(t_env env)
{
	static unsigned int	env_cache = 0;
	static bool			init = false;

	if (!init)
	{
		if (getenv("MyMallocStackLogging"))
			env_cache |= ENV_STACK_LOGGING;
		if (getenv("MyMallocFullLogging"))
			env_cache |= ENV_LOGGING;
		if (getenv("MyMallocPreScribble"))
			env_cache |= ENV_PRE_SCRIBBLE;
		if (getenv("MyMallocScribble"))
			env_cache |= ENV_SCRIBBLE;
		init = true;
	}
	return (env_cache & env);
}