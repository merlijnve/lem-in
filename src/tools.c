/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboer <jboer@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 16:56:00 by jboer         #+#    #+#                 */
/*   Updated: 2020/05/19 23:28:00 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_hashtable		*get_room_from_table(t_lem_in *lem_in, char *name)
{
	int			key;
	t_hashtable	*room;
	char		*temp_name;

	temp_name = ft_strdup(name);
	key = get_hash_key(temp_name, lem_in->n_rooms);
	room = lem_in->hash_table[key];
	if (room == NULL)
	{
		free(temp_name);
		return (NULL);
	}
	while (room->next && ft_strcmp(room->room_name, temp_name))
		room = room->next;
	free(temp_name);
	return (room);
}

int				print_input(t_input *input)
{
	while (input && input->line)
	{
		ft_putstr(input->line);
		ft_putstr("\n");
		input = input->next;
	}
	ft_putstr("\n");
	return (OK);
}

int				is_number(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (i == 0 && string[i] == '-')
		{
			if (string[i + 1] == '\0')
				return (ERROR);
		}
		else if (string[i] < '0' || string[i] > '9')
			return (ERROR);
		i++;
	}
	return (OK);
}

int				check_dup_rooms(t_input *names)
{
	t_input *ptr1;
	t_input *ptr2;

	ptr1 = names;
	ptr2 = names;
	while (ptr1)
	{
		while (ptr2)
		{
			if (ptr1 != ptr2 && ft_strcmp(ptr1->line, ptr2->line) == 0)
				return (ERROR);
			ptr2 = ptr2->next;
		}
		ptr2 = names;
		ptr1 = ptr1->next;
	}
	return (OK);
}

/*
**	SPLIT_ROOM_NAME
**	splits line from the t_input struct lines and sets it
**	in a new t_input for the specific room
*/

int				split_room_name(t_input *lines, t_input *rooms)
{
	char		**split;
	int			i;

	i = 0;
	split = ft_strsplit(lines->line, ' ');
	while (split[i] != NULL)
		i++;
	if (i != 3)
		return (ERROR);
	if (is_number(split[1]) == ERROR || is_number(split[2]) == ERROR)
		return (ERROR);
	rooms->line = ft_strdup(split[0]);
	ft_arrdel(split);
	if (rooms->line == NULL)
		return (ERROR);
	return (OK);
}
