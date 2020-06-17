/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_manipulation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 16:17:18 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/18 12:26:57 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**	TRACK_PATH
**	Reverse traverses path to set visited
**	Edits edge direction if temp == 1
**	sets amount of rooms in path if temp == 0
*/

int				track_path(t_queue *queue, int temp, t_lem_in *lem_in)
{
	int			count;

	count = 0;
	if (temp == 0 && list_queue(lem_in, queue) != OK)
		return (ERROR);
	while (queue->prev != NULL)
	{
		if (temp == 1)
			edit_edge_direction(queue->current, queue->prev->current);
		if (ft_strcmp(queue->current->name, queue->prev->current->name) != 0)
			count++;
		queue->current->visited = 1;
		queue = queue->prev;
	}
	if (temp == 0)
		lem_in->solves->paths->l_path = count;
	return (OK);
}

void			unvisit_queue(t_queue *queue)
{
	while (queue->prev != NULL)
		queue = queue->prev;
	while (queue)
	{
		queue->current->visited = 0;
		queue = queue->next;
	}
}

void			unvisit_edges(t_hashtable *table)
{
	t_edge	*edges;

	if (table->room_in)
	{
		edges = table->room_in->edges;
		while (edges)
			edges = edges->next;
		table->room_in->visited = 0;
	}
	if (table->room_out)
	{
		edges = table->room_out->edges;
		while (edges)
			edges = edges->next;
		table->room_out->visited = 0;
	}
}

void			unvisit(t_lem_in *lem_in)
{
	t_hashtable	*table;
	int			index;

	index = 0;
	while (index < lem_in->n_rooms)
	{
		table = lem_in->hash_table[index];
		while (table)
		{
			if (table->room_in && table->room_out)
			{
				table->room_in->visited = 0;
				table->room_out->visited = 0;
			}
			unvisit_edges(table);
			table = table->next;
		}
		index++;
	}
	get_room_from_table(lem_in, lem_in->start_room->name)->room_in->visited = 1;
	get_room_from_table(lem_in, lem_in->end_room->name)->room_out->visited = 1;
}

t_queue			*init_queue(t_room *start)
{
	t_queue *q;

	q = (t_queue *)ft_memalloc(sizeof(t_queue));
	q->current = start;
	q->prev = NULL;
	return (q);
}
