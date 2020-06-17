/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_solves.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merlijn <merlijn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 18:41:06 by merlijn       #+#    #+#                 */
/*   Updated: 2020/05/02 15:37:10 by joris         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		free_paths(t_paths *paths)
{
	t_paths *temp;
	int		i;

	i = 1;
	while (paths)
	{
		ft_printf("path %d\n", i);
		temp = paths;
		paths = paths->next;
		free_queue(temp->queue);
		ft_memdel((void **)&temp);
		i++;
	}
}

void		free_solves(t_solve *solves)
{
	int		i;
	t_solve	*temp;

	i = 1;
	while (solves)
	{
		ft_printf("solve %d\n", i);
		temp = solves;
		solves = solves->next;
		free_paths(temp->paths);
		ft_memdel((void **)&temp);
		i++;
	}
}
