/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 17:47:04 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:21:34 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <string.h>
# include <sys/mman.h>

# define TINY 't'
# define SMALL 's'
# define LARGE 'l'

# define TINY_M 1024
# define SMALL_M 4096

typedef struct		s_large {
	void			*addr;
	size_t			size;
	struct s_large	*next;
	struct s_large	*prev;
}					t_large;

typedef struct		s_malloc {
	void			*tiny_addrs;
	void			*small_addrs;
	size_t			*tiny_array;
	size_t			*small_array;
	t_large			*large;
}					t_malloc;

t_malloc g_memory;

void	*ft_malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	ft_free(void *ptr);
void	*getTinyOrSmall(char type, size_t size);
void	*getLarge(size_t size);
void	*allocate(size_t size);

#endif
