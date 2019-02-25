/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:41:41 by glavigno          #+#    #+#             */
/*   Updated: 2019/01/29 16:28:10 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"

# define INT_MAX 2147483647

typedef struct	s_struct{
	char		*str;
	int			**coord;
	char		**room_name;
	int			**matrix;
	int			nb_ants;
	int			nb_rooms;
	int			check_end;
	int			check_start;
	int			*test;
	int			*path;
	int			count_soluce;
	int			**soluce;
	int			start;
}				t_struct;

void			check_nb_ants(t_struct *s);

int				check_gnl(t_struct *s);
void			do_room_name_and_coord(t_struct *s);

void			edmonds_karp(t_struct *s);
void			calcul(t_struct *s);

void			traversal(t_struct *s, int i, int *i_ants, int *tab);
void			soluce_handler(t_struct *s, int i, int *i_ants, int *tab);

void			do_matrix(t_struct *s, int j);

void			free_all(t_struct *s, int opt);
void			clean_exit(t_struct *p, int opt);

#endif
