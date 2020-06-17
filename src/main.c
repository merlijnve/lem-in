/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 15:47:06 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/06/03 14:18:59 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			var_dump(t_lem_in *lem_in, t_paths *solve)
{
	ft_putendl("____VAR_DUMP____");
	ft_putnbr(lem_in->n_ants);
	ft_putendl(" ants.");
	ft_putnbr(lem_in->n_rooms);
	ft_putendl(" rooms.");
	ft_printf("%s -> %s\n", lem_in->start_room->name, lem_in->end_room->name);
	while (solve)
	{
		ft_printf("l_path: %i\n", solve->l_path);
		solve = solve->next;
	}
}

/*
**	PRINT_ERROR
**	Custom error management - BONUS
*/

void			print_error(int errno)
{
	ft_putendl("ERROR");
	if (errno == 1)
		ft_putendl("Problem with read lines");
	if (errno == 2)
		ft_putendl("Problem with ant count - no ants or too much ants");
	if (errno == 3)
		ft_putendl("Problem with rooms");
	if (errno == 4)
		ft_putendl("Problem allocating hashtable");
	if (errno == 5)
		ft_putendl("Problem creating edges");
	if (errno == 6)
		ft_putendl("Problem setting start/end rooms (missing or too many)");
	if (errno == 8)
		ft_putendl("Found no path");
	if (errno == 9)
		ft_putendl("Duplicate rooms");
	exit(ERROR);
}

void			check_start_connects_to_end(t_lem_in *lem_in)
{
	t_room	start;
	t_room	end;
	int		i;

	i = 1;
	start = *lem_in->start_room;
	end = *lem_in->end_room;
	while (start.edges)
	{
		if (ft_strcmp(start.edges->room->name, end.name) == 0)
		{
			print_input(lem_in->lines);
			while (i <= lem_in->n_ants)
			{
				ft_printf("L%i-%s", i, lem_in->end_room->name);
				if (i == lem_in->n_ants)
					ft_putchar('\n');
				else
					ft_putchar(' ');
				i++;
			}
			exit(OK);
		}
		start.edges = start.edges->next;
	}
}

static t_solve	*find_path_loop(t_lem_in *lem_in, t_solve *solve)
{
	int			calc;

	while (find_path(lem_in->start_room, lem_in->end_room, lem_in) == OK)
	{
		calc = calc_steps(lem_in->solves->paths, lem_in->n_ants);
		if (lem_in->steps > calc)
		{
			lem_in->steps = calc;
			solve = lem_in->solves;
		}
		else
			break ;
	}
	return (solve);
}

int				main(void)
{
	t_lem_in	*lem_in;
	t_solve		*solve;
	int			input_ret;

	lem_in = (t_lem_in *)ft_memalloc(sizeof(t_lem_in));
	lem_in->steps = __INT_MAX__;
	solve = NULL;
	input_ret = get_input(lem_in);
	if (input_ret != OK)
		print_error(input_ret);
	get_room_from_table(lem_in, lem_in->start_room->name)->room_in->visited = 1;
	get_room_from_table(lem_in, lem_in->end_room->name)->room_out->visited = 1;
	check_start_connects_to_end(lem_in);
	lem_in->ret_queues = (t_queue **)ft_memalloc(sizeof(t_queue *) * 10000);
	solve = find_path_loop(lem_in, solve);
	if (solve == NULL)
		print_error(8);
	print_moves(lem_in->lines, solve->paths, lem_in->steps);
	return (OK);
}
