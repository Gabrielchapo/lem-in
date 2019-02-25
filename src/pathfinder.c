/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrai <gdrai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:49:53 by glavigno          #+#    #+#             */
/*   Updated: 2019/01/29 14:01:34 by gdrai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		pathfinder(t_struct *s, int *queue)
{
	int u;
	int v;

	queue[s->nb_rooms] = 1;
	queue[0] = 0;
	while (queue[s->nb_rooms] != 0)
	{
		u = queue[queue[s->nb_rooms] - 1];
		queue[s->nb_rooms]--;
		v = -1;
		while (++v < s->nb_rooms)
		{
			if (s->matrix[u][v] == 1 && s->path[v] == -1)
			{
				s->path[v] = u;
				if (v == s->nb_rooms - 1)
					return (1);
				queue[s->nb_rooms]++;
				queue[queue[s->nb_rooms] - 1] = v;
			}
		}
	}
	return (0);
}

void	read_path(t_struct *s, int j)
{
	int u;
	int k;

	s->soluce[j][s->nb_rooms] = 1;
	u = s->nb_rooms - 1;
	s->soluce[j][0] = s->nb_rooms - 1;
	k = 1;
	while (u != 0)
	{
		s->soluce[j][s->nb_rooms]++;
		s->soluce[j][k++] = s->path[u];
		s->matrix[s->path[u]][u] = 0;
		u = s->path[u];
	}
}

void	create_soluce(t_struct *s)
{
	int i;

	i = -1;
	s->count_soluce = 0;
	while (++i < s->nb_rooms)
	{
		if (s->matrix[s->nb_rooms - 1][i] == 1)
			s->count_soluce++;
	}
	if (!(s->soluce = (int**)malloc(sizeof(int*) * s->count_soluce)))
		exit(0);
	i = -1;
	while (++i < s->count_soluce)
	{
		if (!(s->soluce[i] = (int*)malloc(sizeof(int) * (s->nb_rooms + 1))))
			exit(0);
	}
}

void	edmonds_karp(t_struct *s)
{
	int i;
	int j;
	int *queue;

	if (!(s->path = (int*)malloc(sizeof(int) * s->nb_rooms)))
		exit(0);
	if (!(queue = (int*)malloc(sizeof(int) * (s->nb_rooms + 1))))
		exit(0);
	create_soluce(s);
	s->check_start = 0;
	j = 0;
	while (1)
	{
		i = -1;
		while (++i < s->nb_rooms)
			s->path[i] = -1;
		if (!pathfinder(s, queue))
			break ;
		s->check_start = 1;
		read_path(s, j++);
	}
	ft_memdel((void**)&s->path);
	ft_memdel((void**)&queue);
	if (s->check_start != 1)
		clean_exit(s, 1);
}
