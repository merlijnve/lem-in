/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_result.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboer <jboer@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 14:02:58 by jboer         #+#    #+#                 */
/*   Updated: 2020/05/19 13:09:15 by joris         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		set_first_ant_number(t_paths *paths)
{
	int	i;

	i = 1;
	while (paths)
	{
		paths->first_ant_n = i;
		i++;
		paths = paths->next;
	}
}

static int		add_instruction(t_queue *queue, int i)
{
	while (queue->prev)
		queue = queue->prev;
	while (queue->next)
	{
		if (queue->prev == NULL)
		{
			if (queue->ant > 0)
				queue->ant = 0;
		}
		if (queue->ant)
		{
			if (i == 1)
				ft_putstr(" ");
			i = 1;
			queue->prev->prev->ant = queue->ant;
			queue->ant = 0;
			ft_putstr("L");
			ft_putnbr(queue->prev->prev->ant);
			ft_putstr("-");
			ft_putstr(queue->prev->prev->current->name);
		}
		queue = queue->next;
	}
	return (i);
}

static int		add_start_ants(t_paths *paths, int n_paths, int i)
{
	if (i == 1 && paths->n_ants_in > 0)
		ft_putstr(" ");
	if (paths->n_ants_in > 0)
	{
		i = 2;
		paths->queue->prev->ant = paths->first_ant_n;
		ft_putstr("L");
		ft_putnbr(paths->queue->prev->ant);
		ft_putstr("-");
		ft_putstr(paths->queue->prev->current->name);
		if (paths->next != NULL)
			ft_putstr(" ");
		paths->first_ant_n = paths->first_ant_n + n_paths;
		paths->n_ants_in--;
	}
	return (i);
}

static int		path_count(t_paths *paths)
{
	int	i;

	i = 0;
	while (paths)
	{
		i++;
		paths = paths->next;
	}
	return (i);
}

int				print_moves(t_input *lines, t_paths *paths, int steps)
{
	t_paths	*first;
	int		n_paths;
	int		i;

	i = 0;
	first = paths;
	set_first_ant_number(paths);
	n_paths = path_count(paths);
	print_input(lines);
	while (steps > 0)
	{
		while (paths)
		{
			i = add_instruction(paths->queue, i);
			i = add_start_ants(paths, n_paths, i);
			paths = paths->next;
		}
		ft_putstr("\n");
		paths = first;
		steps--;
		i = 0;
	}
	return (OK);
}
