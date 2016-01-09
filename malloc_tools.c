/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 18:32:58 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:29:51 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*getLarge(size_t size) {
	t_large		*large;
	t_large		*tmp;

	large = (t_large*)allocate(sizeof(t_large));
	if (!large)
		return (NULL);
	large->addr = allocate(size);
	large->size = size;
	large->next = NULL;
	if (!g_memory.large) {
		large->prev = NULL;
		g_memory.large = large;
	} else {
		tmp = g_memory.large;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = large;
		large->prev = tmp;
	}
	return (large->addr);
}

size_t	getSize(size_t index, size_t len, size_t *array) {
	size_t	space;

	space = 0;
	while (index < len) {
		if (array[index] != 0)
			break;
		space++;
		index++;
	}
	return (space);
}

void	*getAddr(size_t size, size_t len, size_t **array, void *ptr) {
	size_t		index;
	size_t		available_space;

	len *= getpagesize();
	index = 0;
	while (index < len) {
		if ((*array)[index] != 0)
			index += (*array)[index];
		else {
			available_space = getSize(index, len, *array);
			if (size <= available_space)
				break;
			index += available_space;
		}
	}
	if (index >= len)
		return (NULL);
	else {
		(*array)[index] = size;
		return ptr + index;
	}
}

void	*getTinyOrSmall(char type, size_t size) {
	void	*ptr;

	if (type == TINY)
		ptr = getAddr(size, TINY_M, &g_memory.tiny_array, g_memory.tiny_addrs);
	else
		ptr = getAddr(size, SMALL_M, &g_memory.small_array, g_memory.small_addrs);
	return (ptr);
}
