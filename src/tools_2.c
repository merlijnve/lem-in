/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merlijn <merlijn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 22:39:40 by merlijn       #+#    #+#                 */
/*   Updated: 2020/05/19 23:29:52 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		is_valid_line_startend(int i, t_input *lines)
{
	if ((lines->next && i <= 2 && ft_strchr(lines->line, ' ') != NULL)
	|| (ft_strcmp(lines->line, "##start") == 0 ||
	ft_strcmp(lines->line, "##end") == 0))
		return (OK);
	return (ERROR);
}
