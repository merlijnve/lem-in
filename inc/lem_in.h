/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem_in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-eng <mvan-eng@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 15:49:37 by mvan-eng      #+#    #+#                 */
/*   Updated: 2020/05/22 14:34:14 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include "../ft_printf/libft/libft.h"
# include "../ft_printf/includes/ft_printf.h"
# include <stdio.h>

# define OK 0
# define ERROR -1

/*
**	T_INPUT
**	Save lines
*/

typedef	struct			s_input
{
	char				*line;
	struct s_input		*next;
}						t_input;

/*
**	T_EDGE
**	Save edges for every room
*/

typedef struct			s_edge
{
	struct s_room		*room;
	int					open;
	int					visited;
	struct s_edge		*next;
}						t_edge;

/*
**	T_ROOM
**	save rooms
**	link to edges
*/

typedef struct			s_room
{
	char				*name;
	t_edge				*edges;
	int					visited;
	struct s_room		*next;
}						t_room;

/*
**	T_QUEUE
*/

typedef struct			s_queue
{
	struct s_queue		*prev;
	int					ant;
	t_room				*current;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_paths
{
	struct s_queue		*queue;
	int					l_path;
	int					n_ants_in;
	int					first_ant_n;
	struct s_paths		*next;
}						t_paths;

typedef struct			s_solve
{
	struct s_paths		*paths;
	struct s_solve		*next;
}						t_solve;

typedef struct			s_hashtable
{
	char				*room_name;
	struct s_room		*room_in;
	struct s_room		*room_out;
	struct s_hashtable	*next;
}						t_hashtable;

typedef struct			s_lem_in
{
	t_hashtable			**hash_table;
	t_room				*start_room;
	t_room				*end_room;
	t_solve				*solves;
	t_input				*lines;
	t_queue				**ret_queues;
	int					steps;
	int					n_ants;
	int					n_rooms;
}						t_lem_in;

int						get_input(t_lem_in *lem_in);
t_hashtable				**create_hashtable(t_input *room_names, int *n_rooms);
t_input					*alloc_list(t_input *list);
void					free_lines(t_input **list);
void					free_structs(t_lem_in *lem_in);
void					free_hashtable(t_hashtable **hashtable, int n_rooms);
void					print_hashtable(t_hashtable **hashtable, int n_rooms);
int						get_edges(t_input *lines, t_lem_in *lem_in);
int						get_hash_key(char *room_name, int n_rooms);
int						find_path(t_room *start, t_room *end,
t_lem_in *lem_in);
t_hashtable				*get_room_from_table(t_lem_in *lem_in, char *name);
t_queue					*allocate_queue(t_queue *queue_elem);
t_queue					*alloc_queue(t_queue *queue_elem);
void					edit_edge_direction(t_room *room_a, t_room *room_b);
t_queue					*add_edges_to_queue(t_queue *q, t_room *current,
int dir);
int						create_solve_list(t_lem_in *lem_in);
int						list_queue(t_lem_in *lem_in, t_queue *queue);
t_solve					*compare_solves(t_lem_in *lem_in, int n_ants,
t_paths *paths);
int						calc_steps(t_paths *paths, int n_ants);
t_queue					*find_path_edge(t_room *start, t_room *end,
t_lem_in *lem_in);
void					unvisit_queue(t_queue *queue);
int						track_path(t_queue *queue, int temp, t_lem_in *lem_in);
t_queue					*init_queue(t_room *start);
void					unvisit(t_lem_in *lem_in);
void					unvisit_queue(t_queue *queue);
int						print_input(t_input *input);
int						print_moves(t_input *lines, t_paths *paths, int steps);
void					free_queue(t_queue *q);
void					free_solves(t_solve *solves);
void					free_room(t_room *room);
void					save_returned_queue(t_queue *q, t_queue **array);
int						split_room_name(t_input *lines, t_input *rooms);
int						check_dup_rooms(t_input *names);
void					print_error(int errno);
int						is_valid_line_startend(int i, t_input *lines);

#endif
