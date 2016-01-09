/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 19:07:13 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:29:38 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		checkExists(void *ptr, void *addrs, size_t *array, size_t len) {
	size_t	index;

	len *= getpagesize();
	index = 0;
	while (index < len) {
		if (array[index] != 0) {
			if (ptr == (addrs + index))
				return (index);
			else
				index += array[index];
		} else
			index++;
	}
	return (-1);
}

void	ft_free(void *ptr) {
	int		 	index;
	t_large		*tmp;

	index = checkExists(ptr, g_memory.tiny_addrs, g_memory.tiny_array, TINY_M);
	if (index > -1) {
		g_memory.tiny_array[index] = 0;
		return;
	}
	index = checkExists(ptr, g_memory.small_addrs, g_memory.small_array, SMALL_M);
	if (index > -1) {
		g_memory.small_array[index] = 0;
		return;
	}
	tmp = g_memory.large;
	while (tmp) {
		if (ptr == tmp->addr) {
			munmap(ptr, tmp->size);
			if (tmp == g_memory.large) {
				g_memory.large = tmp->next;
				if (g_memory.large)
					g_memory.large->prev = NULL;
			} else {
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				if (tmp->prev)
					tmp->prev->next = tmp->next;
			}
			munmap(tmp, sizeof(tmp));
			return;
		}
	}
}
