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
	if (size <= TINY_AUTHORIZED_SIZE)
	{
		type.size = TINY_SIZE;
		type.type = TINY;
	}
	else if (size <= SMALL_AUTHORIZED_SIZE)
	{
		type.size = SMALL_SIZE;
		type.type = SMALL;
	}
	else
	{
		type.size = -1;
		type.type = LARGE;
	}
	log("Trying to allocate %u bytes (block %u)", size, type.size);
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
		if (getenv("MyMallocPreScribble"))
			env_cache |= ENV_PRE_SCRIBBLE;
		if (getenv("MyMallocScribble"))
			env_cache |= ENV_SCRIBBLE;
		init = true;
	}
	return (env_cache & env);
}

void log_debug(const char *file, int line, const char *function, const char *format, ...)
{
	va_list		args;
	char		buffer[4096];
	int			fd;
	int			len;

	static bool init = false;
	int			mode = init ? O_APPEND | O_WRONLY : O_WRONLY | O_CREAT | O_TRUNC;
	init = true;

	if (!get_env(ENV_STACK_LOGGING))
		return ;

	fd = open("malloc.log", mode, 0644);
	if (fd == -1)
		return;

    len = snprintf(buffer, sizeof(buffer), "%s:%d %s() ", file, line, function);

    va_start(args, format);
    len += vsnprintf(buffer + len, sizeof(buffer) - len, format, args);
    va_end(args);
    buffer[sizeof(buffer) - 1] = '\0';

	write(fd, buffer, len);
	ft_dprintf(fd, "\n");
	close(fd);
}