/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_hashtable.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:06:16 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/19 16:45:19 by joris         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**	GET_HASH_KEY
**	hashes a room name
**	returns index
*/

int			get_hash_key(char *room_name, int n_rooms)
{
	int		key;
	int		i;

	key = 1;
	i = ft_charindex(room_name, ' ');
	if (i != -1)
		room_name[i] = '\0';
	while (*room_name)
	{
		key *= *room_name;
		room_name++;
	}
	if (key <= 0)
		key *= -1;
	return (key % n_rooms);
}

/*
**	ADD_ROOM_TO_TABLE
**	gets hash key for given room_name
**	indexes on hashtables with given key
**	adds element to hashtable
*/

int			add_room_to_table(int n_rooms, char *name, t_hashtable **hashtable)
{
	int			key;
	t_hashtable	*hashtable_elem;

	if (ft_charindex(name, 'L') == 0)
		print_error(4);
	key = get_hash_key(name, n_rooms);
	if (hashtable[key] == NULL)
	{
		hashtable[key] = (t_hashtable *)ft_memalloc(sizeof(t_hashtable));
		if (hashtable[key] == NULL)
			return (ERROR);
		hashtable_elem = hashtable[key];
	}
	else
	{
		hashtable_elem = hashtable[key];
		while (hashtable_elem->next != NULL)
			hashtable_elem = hashtable_elem->next;
		hashtable_elem->next = (t_hashtable *)ft_memalloc(sizeof(t_hashtable));
		if (hashtable_elem->next == NULL)
			return (ERROR);
		hashtable_elem = hashtable_elem->next;
	}
	hashtable_elem->room_name = ft_strdup(name);
	return (OK);
}

/*
**	COUNT_ROOMS
**	counts amount of rooms, skipping lines starting with '#'
*/

int			count_rooms(t_input *rooms)
{
	int		n_rooms;

	n_rooms = 0;
	while (rooms)
	{
		if (rooms->line[0] != '#')
			n_rooms++;
		rooms = rooms->next;
	}
	return (n_rooms);
}

/*
**	PRINT_HASHTABLE
**	for debugging
*/

void		print_hashtable(t_hashtable **hashtable, int n_rooms)
{
	int			i;
	int			n_elem;
	t_hashtable	*elem;

	n_elem = 0;
	i = 0;
	while (i < n_rooms)
	{
		if (hashtable[i] != NULL)
		{
			elem = hashtable[i];
			ft_printf("Index %i\n", i);
			ft_printf("\t%s\n", elem->room_name);
			while (elem->next != NULL)
			{
				elem = elem->next;
				ft_printf("\t%s\n", elem->room_name);
				n_elem++;
			}
			ft_printf("--------------\n");
		}
		i++;
	}
	ft_printf("Indexes in hashtable:\t%d\n", n_elem);
}

/*
**	CREATE_HASHTABLE
**	counts rooms
**	allocates n_rooms of hashtable space
**	loops through room_name
*/

t_hashtable	**create_hashtable(t_input *room_names, int *n_rooms)
{
	t_hashtable **hashtable;
	int			ret;

	ret = OK;
	*n_rooms = count_rooms(room_names);
	hashtable = (t_hashtable **)ft_memalloc(sizeof(t_hashtable *) * *n_rooms);
	if (hashtable == NULL)
		return (NULL);
	while (room_names)
	{
		if (room_names->line[0] != '#')
			ret = add_room_to_table(*n_rooms, room_names->line, hashtable);
		if (ret != OK)
			return (NULL);
		room_names = room_names->next;
	}
	return (hashtable);
}
