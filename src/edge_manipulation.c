/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   edge_manipulation.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 19:42:20 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/11 15:19:49 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int		get_edge_direction(t_room *room_a, t_room *room_b)
{
	t_edge		*edge;

	edge = room_b->edges;
	while (edge->room != room_a)
		edge = edge->next;
	return (edge->open);
}

t_queue			*add_edges_to_queue(t_queue *q, t_room *current, int dir)
{
	t_queue		*queue_elem;
	t_queue		*head;
	t_edge		*edge_p;

	edge_p = current->edges;
	queue_elem = NULL;
	head = NULL;
	while (edge_p)
	{
		if (edge_p->room->visited == 0 &&
		((get_edge_direction(current, edge_p->room) && dir == 1) ||
		(edge_p->open == 0 && edge_p->visited == 1 && dir == 0)))
		{
			queue_elem = alloc_queue(queue_elem);
			if (head == NULL)
				head = queue_elem;
			queue_elem->current = edge_p->room;
			queue_elem->prev = q;
		}
		edge_p = edge_p->next;
	}
	dir = 0;
	return (head);
}

void			edit_edge_direction(t_room *room_a, t_room *room_b)
{
	t_edge		*edge;

	edge = room_a->edges;
	while (edge->room != room_b)
		edge = edge->next;
	edge->open = 0;
	edge->visited = 1;
	edge = room_b->edges;
	while (edge->room != room_a)
		edge = edge->next;
	edge->open = 1;
	edge->visited = 1;
}
