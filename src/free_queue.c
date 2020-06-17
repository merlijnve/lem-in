/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_queue.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: merlijn <merlijn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 17:53:23 by merlijn       #+#    #+#                 */
/*   Updated: 2020/05/02 16:07:08 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	free_edges(t_edge *edges)
{
	t_edge *temp;

	while (edges)
	{
		temp = edges;
		edges = edges->next;
		ft_memdel((void **)&temp);
	}
}

void	free_room(t_room *room)
{
	ft_strdel(&room->name);
	free_edges(room->edges);
}

void	free_queue(t_queue *q)
{
	t_queue *q_prev;
	t_queue	*q_orig;

	q_orig = q;
	while (q->prev)
		q = q->prev;
	while (q)
	{
		q_prev = q;
		q = q->next;
		ft_memdel((void **)&q);
	}
	free(q_orig);
}
