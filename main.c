/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:30:40 by ycontre           #+#    #+#             */
/*   Updated: 2024/08/02 02:03:25 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/mymalloc.h"

int main(void)
{
	void *test = malloc(144);
	test = malloc(144);
	for (int i = 0; i < 100; i++)
		test = malloc(144);
	
	ft_printf("%p\n", test);
	return (0);
}