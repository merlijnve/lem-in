/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_edges.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboer <jboer@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 20:28:28 by jboer         #+#    #+#                 */
/*   Updated: 2020/05/19 23:19:38 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**	SET_EDGES
**	pointers from and to edges and rooms based on the specific map data
*/

static int		set_edges(t_room *room_a, t_room *room_b, int open)
{
	t_edge	*edge;

	edge = ft_memalloc(sizeof(t_edge));
	if (edge == NULL)
		return (ERROR);
	edge->room = room_b;
	edge->open = open;
	edge->next = room_a->edges;
	room_a->edges = edge;
	return (OK);
}

/*
**	ALLOC_ROOM
**	checks if the room already exits in struct if so nothing happends,
**	if not the specific struct are allocated
**	check_edge_alloc gets called with room
*/

static int		alloc_room(t_hashtable *room, char *line)
{
	if (room == NULL)
		return (ERROR);
	while (ft_strcmp(room->room_name, line) != 0)
	{
		if (room->next == NULL)
			return (ERROR);
		room = room->next;
	}
	if (room->room_in == NULL && room->room_out == NULL)
	{
		room->room_in = (t_room *)ft_memalloc(sizeof(t_room));
		room->room_out = (t_room *)ft_memalloc(sizeof(t_room));
		room->room_in->name = ft_strdup(line);
		room->room_out->name = ft_strdup(line);
	}
	if (room->room_in->edges == NULL)
	{
		room->room_in->edges = ft_memalloc(sizeof(t_edge));
		if (!room->room_in->edges)
			return (ERROR);
		room->room_in->edges->room = room->room_out;
		room->room_in->edges->open = 0;
	}
	return (OK);
}

/*
**	SET_EDGE_CHECK
**	checks if all edges are set correctly in SET_EDGES
*/

static int		set_edge_check(t_hashtable *ht_one, t_hashtable *ht_two)
{
	if (set_edges(ht_one->room_out, ht_one->room_in, 1) == ERROR)
		return (ERROR);
	if (set_edges(ht_two->room_out, ht_two->room_in, 1) == ERROR)
		return (ERROR);
	if (set_edges(ht_one->room_out, ht_two->room_in, 0) == ERROR)
		return (ERROR);
	if (set_edges(ht_one->room_in, ht_two->room_out, 1) == ERROR)
		return (ERROR);
	if (set_edges(ht_two->room_out, ht_one->room_in, 0) == ERROR)
		return (ERROR);
	if (set_edges(ht_two->room_in, ht_one->room_out, 1) == ERROR)
		return (ERROR);
	return (OK);
}

/*
**	MAKE_ROOM_EDGES
**	main functions for functions above
**	finds the two hashtable structs as specified in the line from map data
*/

static int		make_room_edges(char *line, t_lem_in *lem_in)
{
	int			i;
	t_hashtable *ht_one;
	t_hashtable *ht_two;

	i = ft_charindex(line, '-');
	line[i] = '\0';
	if (ft_strcmp(line, &line[i + 1]) == 0)
		return (ERROR);
	ht_one = get_room_from_table(lem_in, line);
	ht_two = get_room_from_table(lem_in, &line[i + 1]);
	if (alloc_room(ht_one, line) == ERROR)
		return (ERROR);
	if (alloc_room(ht_two, &line[i + 1]) == ERROR)
		return (ERROR);
	if (set_edge_check(ht_one, ht_two) == ERROR)
		return (ERROR);
	line[i] = '-';
	return (OK);
}

/*
**	GET_EDGES
**	goes through every line that gives edge data
**	and fills the hashtable struct with that data
*/

int				get_edges(t_input *lines, t_lem_in *lem_in)
{
	int ret;

	while (lines && lines->line &&
	(ft_strchr(lines->line, ' ') != NULL || lines->line[0] == '#'))
		lines = lines->next;
	if (lines == NULL || lines->line == NULL)
		return (ERROR);
	while (lines)
	{
		if (lines->line == NULL)
			return (OK);
		if (lines->line[0] != '#' && lines->line[0] != 'L')
			ret = make_room_edges(lines->line, lem_in);
		if (ret == ERROR)
			return (ERROR);
		lines = lines->next;
	}
	return (OK);
}
