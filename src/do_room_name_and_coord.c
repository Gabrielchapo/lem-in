/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_room_name_and_coord.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:22:20 by gdrai             #+#    #+#             */
/*   Updated: 2019/01/29 17:07:11 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		do_coordonnates(t_struct *s, int j, int i)
{
	if (!(s->coord[i] = (int*)malloc(sizeof(int) * 3)))
		exit(0);
	s->coord[i][0] = ft_atoi(&(s->str[++j]));
	while (s->str[j] >= 48 && s->str[j] <= 57)
		j++;
	s->coord[i][1] = ft_atoi(&(s->str[++j]));
	while (s->str[j] >= 48 && s->str[j] <= 57)
		j++;
	j++;
	s->coord[i][2] = 0;
	return (j);
}

int		do_name(t_struct *s, int j, int i)
{
	int k;

	k = 0;
	if (s->str[j] == '#' && s->str[j + 1] == '#' && s->str[j + 2] == 'e')
	{
		j += 6;
		s->check_end = i;
	}
	if (s->str[j] == '#' && s->str[j + 1] == '#' && s->str[j + 2] == 's')
	{
		j += 8;
		s->check_start = i;
	}
	if (!(s->room_name[i] = (char*)malloc(sizeof(char) * (s->nb_rooms + 1))))
		exit(0);
	while (s->str[j] != ' ')
		s->room_name[i][k++] = s->str[j++];
	s->room_name[i][k] = '\0';
	return (j);
}

void	handle_start_end(t_struct *s)
{
	char	*c;
	int		*tmp;

	if (s->check_start != 0)
	{
		if (s->check_end == 0)
			s->check_end = s->check_start;
		c = s->room_name[0];
		tmp = s->coord[0];
		s->room_name[0] = s->room_name[s->check_start];
		s->coord[0] = s->coord[s->check_start];
		s->room_name[s->check_start] = c;
		s->coord[s->check_start] = tmp;
		s->check_start = 0;
	}
	if (s->check_end != s->nb_rooms - 1)
	{
		c = s->room_name[s->check_end];
		tmp = s->coord[s->check_end];
		s->room_name[s->check_end] = s->room_name[s->nb_rooms - 1];
		s->coord[s->check_end] = s->coord[s->nb_rooms - 1];
		s->room_name[s->nb_rooms - 1] = c;
		s->coord[s->nb_rooms - 1] = tmp;
		s->check_end = s->nb_rooms - 1;
	}
}

void	check_identical_coord(t_struct *s)
{
	int i;
	int j;

	i = 0;
	while (i < s->nb_rooms)
	{
		j = 0;
		while (j < s->nb_rooms)
		{
			if (ft_strcmp(s->room_name[j], s->room_name[i]) == 0 && i != j)
				clean_exit(s, 1);
			if (s->coord[i][0] == s->coord[j][0] &&
				s->coord[i][1] == s->coord[j][1] && i != j)
				clean_exit(s, 1);
			j++;
		}
		i++;
	}
}

void	do_room_name_and_coord(t_struct *s)
{
	int i;
	int j;

	if (!(s->room_name = (char**)malloc(sizeof(char*) * (s->nb_rooms + 1))))
		exit(0);
	if (!(s->coord = (int**)malloc(sizeof(int*) * (s->nb_rooms + 1))))
		exit(0);
	i = 0;
	j = 0;
	while (i < s->nb_rooms)
	{
		j = do_name(s, j, i);
		j = do_coordonnates(s, j, i);
		i++;
	}
	s->room_name[i] = NULL;
	handle_start_end(s);
	do_matrix(s, j);
	check_identical_coord(s);
}
