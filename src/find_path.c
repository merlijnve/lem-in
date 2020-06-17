/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:53:20 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/18 15:47:15 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			save_returned_queue(t_queue *q, t_queue **array)
{
	static int	i = 0;

	array[i] = q;
	i++;
}

void			set_start_end_unvisited(t_room *start, t_room *end)
{
	start->visited = 0;
	end->visited = 0;
}

/*
**	LOOP_FIND_PATH_EDGES
**	Unvisits entire map
*/

void			loop_find_path_edges(t_lem_in *lem_in, t_room *start,
t_room *end)
{
	unvisit(lem_in);
	while (find_path_edge(end, start, lem_in) != NULL)
		set_start_end_unvisited(start, end);
	unvisit(lem_in);
}

static t_queue	*queue_end_loop(t_queue *q, t_queue *queue_end)
{
	q->current->visited = 1;
	while (queue_end->next)
		queue_end = queue_end->next;
	queue_end->next = add_edges_to_queue(q, q->current, 1);
	return (queue_end);
}

int				find_path(t_room *start, t_room *end, t_lem_in *lem_in)
{
	t_queue		*q;
	t_queue		*queue_end;

	create_solve_list(lem_in);
	if (start->edges == NULL)
		return (ERROR);
	q = init_queue(start);
	queue_end = q;
	while (q)
	{
		if (q->current == end && track_path(q, 1, lem_in) == OK)
		{
			loop_find_path_edges(lem_in, start, end);
			save_returned_queue(q, lem_in->ret_queues);
			return (OK);
		}
		queue_end = queue_end_loop(q, queue_end);
		q = q->next;
	}
	free_queue(queue_end);
	return (ERROR);
}
