/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:06:16 by TheRed            #+#    #+#             */
/*   Updated: 2024/08/11 17:06:16 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_fd(size_t nb, char base, int fd, bool prefix)
{
	char *str;

	str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
	if (nb / base)
		ft_itoa_fd(nb / base, base, fd, prefix);
	else if (prefix)
		ft_dprintf(fd, "0x");
	ft_dprintf(fd, &str[nb % base]);
}

void	ft_itoa_base(size_t nb, char base, char length, bool prefix)
{
	char	*str;

	str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
	if (nb / base)
		ft_itoa_base(nb / base, base, length - 1, prefix);
	else
	{
		if (prefix)
			ft_printf("0x");
		while (--length > 0)
			ft_printf("0");
	}
	ft_printf(&str[nb % base]);
}