/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_tools.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 14:05:56 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/02 15:36:17 by joris         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**	FREE_HASHTABLE && FREE_HASHTABLE_INDEX
**	frees an array of lists
*/

void	free_hashtable_index(t_hashtable *elem)
{
	if (elem == NULL)
		return ;
	free_hashtable_index((elem)->next);
	free_room((elem)->room_in);
	free_room((elem)->room_out);
	free((elem)->room_name);
	ft_memdel((void**)&elem);
}

void	free_hashtable(t_hashtable **hashtable, int n_rooms)
{
	int i;

	i = 0;
	while (i + 1 < n_rooms)
	{
		if (hashtable[i] != NULL)
		{
			ft_putstr("kech\n");
			free_hashtable_index(hashtable[i]);
			i++;
			ft_putnbr(i);
			ft_putstr("\n");
		}
	}
}

/*
**	FREE_LINES
**	recursive implementation of a list freeing function
*/

void	free_lines(t_input **list)
{
	if (*list == NULL)
		return ;
	free_lines(&(*list)->next);
	ft_strdel(&(*list)->line);
	free(*list);
	*list = NULL;
}

/*
**	ALLOC_LIST
**	function to allocate list or allocate list->next
**	returns list->next
*/

t_input	*alloc_list(t_input *list)
{
	if (list == NULL)
	{
		list = (t_input *)ft_memalloc(sizeof(t_input));
		if (list == NULL)
			return (NULL);
		ft_bzero(list, sizeof(t_input));
		list->next = NULL;
		return (list);
	}
	else
	{
		list->next = (t_input *)ft_memalloc(sizeof(t_input));
		if (list == NULL)
			return (NULL);
		list = list->next;
		ft_bzero(list, sizeof(t_input));
		list->next = NULL;
		return (list);
	}
}

/*
**	ALLOC_QUEUE
**	Allocates a new queue_elem for a new or existing queue list
*/

t_queue	*alloc_queue(t_queue *queue_elem)
{
	if (queue_elem == NULL)
		queue_elem = (t_queue *)ft_memalloc(sizeof(t_queue));
	else
	{
		queue_elem->next = (t_queue *)ft_memalloc(sizeof(t_queue));
		queue_elem = queue_elem->next;
	}
	return (queue_elem);
}
