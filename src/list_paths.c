/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_paths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboer <jboer@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 13:28:53 by jboer         #+#    #+#                 */
/*   Updated: 2020/05/02 14:19:59 by joris         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**	Creates list of paths (list of t_queue)
*/

int				list_queue(t_lem_in *lem_in, t_queue *queue)
{
	t_paths		*new;

	new = (t_paths *)ft_memalloc(sizeof(t_paths));
	if (new == NULL)
		return (ERROR);
	new->next = lem_in->solves->paths;
	lem_in->solves->paths = new;
	lem_in->solves->paths->queue = queue;
	return (OK);
}

/*
**	Creates lem_in->solves or adds an element to it
*/

int				create_solve_list(t_lem_in *lem_in)
{
	t_solve *new;

	new = (t_solve *)ft_memalloc(sizeof(t_solve));
	new->paths = NULL;
	if (lem_in->solves == NULL)
	{
		lem_in->solves = new;
		lem_in->solves->next = NULL;
		return (OK);
	}
	new->next = lem_in->solves;
	lem_in->solves = new;
	return (OK);
}

void			print_path(t_queue *path)
{
	t_queue		*p;

	p = path;
	while (p)
	{
		ft_putendl(p->current->name);
		p = p->prev;
	}
}

void			print_all_paths(t_solve *solves)
{
	t_solve		*s;

	s = solves;
	while (s)
	{
		while (s->paths)
		{
			print_path(s->paths->queue);
			s->paths = s->paths->next;
		}
		s = s->next;
	}
}
