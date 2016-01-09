/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 17:53:04 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:03:39 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*allocate(size_t size) {
	void	*ptr;

	ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

size_t		*init_array(size_t size) {
	size_t	*array;
	int		i;

	array = (size_t*)allocate(sizeof(size_t) * size);
	if (array) {
		i = 0;
		while (i < size)
			array[i++] = 0;
	}
	return (array);
}

void	init_malloc() {
	static int	initialized = 0;

	if (!initialized) {
		initialized = 1;
		g_memory.tiny_addrs = allocate(TINY_M * getpagesize());
		g_memory.small_addrs = allocate(SMALL_M * getpagesize());
		g_memory.tiny_array = init_array(TINY_M * getpagesize());
		g_memory.small_array = init_array(SMALL_M * getpagesize());
		g_memory.large = NULL;
	}
}

void	*ft_malloc(size_t size) {
	void	*ptr;

	init_malloc();
	if (size <= TINY_M)
		ptr = getTinyOrSmall(TINY, size);
	else if (size <= SMALL_M)
		ptr = getTinyOrSmall(SMALL, size);
	else
		ptr = getLarge(size);
	return (ptr);
}
