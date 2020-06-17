/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path_edge.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 16:03:35 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/18 19:06:24 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static t_queue	*queue_end_loop(t_queue *q, t_queue *queue_end)
{
	q->current->visited = 1;
	while (queue_end->next)
		queue_end = queue_end->next;
	queue_end->next = add_edges_to_queue(q, q->current, 0);
	return (queue_end);
}

t_queue			*find_path_edge(t_room *start, t_room *end,
t_lem_in *lem_in)
{
	t_queue *q;
	t_queue *queue_end;

	if (start->edges == NULL)
		return (NULL);
	q = init_queue(start);
	queue_end = q;
	while (q)
	{
		if (q->current == end)
		{
			unvisit_queue(q);
			track_path(q, 0, lem_in);
			start->visited = 0;
			save_returned_queue(q, lem_in->ret_queues);
			return (q);
		}
		queue_end = queue_end_loop(q, queue_end);
		q = q->next;
	}
	free_queue(queue_end);
	return (NULL);
}
