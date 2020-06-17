/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare_solves.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 14:25:54 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/25 17:32:45 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**	FIND_SHORTEST_PATH
**	finds shortest path by length and ants inside
*/

static t_paths	*find_shortest_path(t_paths *paths)
{
	t_paths	*p;
	t_paths *res;

	p = paths;
	res = p;
	while (p)
	{
		if (p->l_path + p->n_ants_in < res->l_path + res->n_ants_in)
			res = p;
		p = p->next;
	}
	return (res);
}

/*
**	FIND_LONGEST_PATH
**	finds longest path by path length only
*/

static t_paths	*find_longest_path(t_paths *paths)
{
	t_paths	*p;
	t_paths *res;

	p = paths;
	res = p;
	while (p)
	{
		if (p->l_path > res->l_path)
			res = p;
		p = p->next;
	}
	return (res);
}

/*
**	CALC_LINES_NEEDED
**	Calculates needed lines by adding all ants to paths,
**	then returns the amounts of ants added into the shortest path
*/

int				calc_steps(t_paths *paths, int n_ants)
{
	int		i;
	t_paths	*p;

	i = 0;
	while (i < n_ants)
	{
		find_shortest_path(paths)->n_ants_in++;
		i++;
	}
	p = find_longest_path(paths);
	return (p->l_path + p->n_ants_in - 1);
}
