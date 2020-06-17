/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 16:10:52 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/22 14:14:39 by joris         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"
#include <fcntl.h>

/*
**	READ_LINES
**	reads standard input and returns line list
**	skips all empty lines and comments
*/

static t_input			*read_lines(void)
{
	t_input	*all;
	t_input	*head;

	all = alloc_list(NULL);
	if (all == NULL)
		return (NULL);
	head = all;
	while (get_next_line(0, &head->line) == 1)
	{
		if (*head->line == '\0')
			print_error(1);
		while (head->line && (head->line[0] == '\0' || (head->line[0] == '#' &&
		ft_strcmp(head->line, "##start") != 0 && ft_strcmp(head->line, "##end")
		!= 0)))
		{
			ft_strdel(&head->line);
			get_next_line(0, &head->line);
		}
		head = alloc_list(head);
		if (head == NULL)
			return (NULL);
	}
	if (all->line == NULL)
		return (NULL);
	return (all);
}

/*
**	COUNT_ANTS
**	returns amount of ants
*/

static int				count_ants(t_input *lines)
{
	int	n_ants;

	n_ants = 0;
	while (lines->line[0] == '#')
		lines = lines->next;
	if (ft_strlen(lines->line) >= 10)
		return (ERROR);
	while (lines->line[n_ants] != '\0')
	{
		if (!ft_isdigit(lines->line[n_ants]))
			return (ERROR);
		n_ants++;
	}
	n_ants = ft_atoi(lines->line);
	if (n_ants <= 0)
		return (ERROR);
	return (n_ants);
}

/*
**	GET_ROOMS
**	checks line for spaces (because all lines indicating new rooms have spaces)
**	OR checks for a hash, indicating a comment or start/end room
**	returns a list of rooms
*/

t_input					*get_rooms(t_input *lines)
{
	t_input *rooms;
	t_input *head;
	int		i;

	i = 0;
	rooms = NULL;
	while (lines->line != NULL &&
	(ft_strchr(lines->line, ' ') != NULL || lines->line[0] == '#'))
	{
		if (ft_strcmp(lines->line, "##start") == 0 ||
		ft_strcmp(lines->line, "##end") == 0)
			lines = lines->next;
		rooms = alloc_list(rooms);
		if (rooms == NULL)
			return (NULL);
		if (i == 0)
			head = rooms;
		if (split_room_name(lines, rooms) == ERROR)
			return (NULL);
		lines = lines->next;
		i++;
	}
	if (i == 0)
		return (NULL);
	return (head);
}

/*
**	SET_START_END
**	sets end/start room in t_lem_in
*/

static int				set_start_end(t_input *lines, t_lem_in *lem_in)
{
	int			i;

	i = 0;
	while (is_valid_line_startend(i, lines) == OK)
	{
		if (lines->line == NULL)
			return (OK);
		if (ft_strcmp(lines->line, "##start") == 0)
		{
			i++;
			lem_in->start_room =
			get_room_from_table(lem_in, lines->next->line)->room_out;
		}
		if (ft_strcmp(lines->line, "##end") == 0)
		{
			i++;
			lem_in->end_room =
			get_room_from_table(lem_in, lines->next->line)->room_in;
		}
		lines = lines->next;
	}
	if (lem_in->end_room == NULL || lem_in->start_room == NULL || i != 2 ||
	ft_strcmp(lem_in->start_room->name, lem_in->end_room->name) == 0)
		return (ERROR);
	return (OK);
}

/*
**	GET_INPUT
**	reads lines into linked list
**	parses amount of ants
**	parses rooms (including comments) into list
**	parses rooms into hashtable
*/

int						get_input(t_lem_in *lem_in)
{
	t_input	*lines;
	t_input	*room_names;

	lines = read_lines();
	if (lines == NULL)
		return (1);
	lem_in->n_ants = count_ants(lines);
	if (lem_in->n_ants == -1)
		return (2);
	room_names = get_rooms(lines->next);
	if (room_names == NULL)
		return (3);
	if (check_dup_rooms(room_names) == ERROR)
		return (9);
	lem_in->hash_table = create_hashtable(room_names, &lem_in->n_rooms);
	if (lem_in->hash_table == NULL)
		return (4);
	if (get_edges(lines->next, lem_in) == ERROR)
		return (5);
	if (set_start_end(lines->next, lem_in) == ERROR)
		return (6);
	lem_in->lines = lines;
	free_lines(&room_names);
	return (OK);
}
