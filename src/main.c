/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:44:45 by glavigno          #+#    #+#             */
/*   Updated: 2019/01/30 13:49:19 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	check_nb_ants(t_struct *s)
{
	char		*line;
	long long	test;
	int			i;

	if (get_next_line(0, &line) < 1)
		exit(0);
	i = 0;
	while (line[i] > 47 && line[i] < 58)
		i++;
	if (line[0] < 48 || line[0] > 57 || line[i] != '\0')
		clean_exit(s, 0);
	test = ft_atoll(line);
	if (test < 1 || test > INT_MAX || test / 10000000000 > 0)
		clean_exit(s, 0);
	s->nb_ants = ft_atoi(line);
	ft_strdel(&line);
	s->check_end = 0;
	s->check_start = 0;
	s->nb_rooms = 0;
}

void	sort_path(t_struct *s)
{
	int i;
	int tmp;
	int *tmp_ptr;

	tmp = s->count_soluce;
	while (tmp)
	{
		i = -1;
		while (++i < tmp - 1)
		{
			if (s->soluce[i][s->nb_rooms] > s->soluce[i + 1][s->nb_rooms])
			{
				tmp_ptr = s->soluce[i];
				s->soluce[i] = s->soluce[i + 1];
				s->soluce[i + 1] = tmp_ptr;
			}
		}
		tmp--;
	}
}

int		main(void)
{
	t_struct	*s;

	if (!(s = (t_struct*)malloc(sizeof(t_struct))))
		exit(0);
	check_gnl(s);
	do_room_name_and_coord(s);
	ft_putendl(s->str);
	edmonds_karp(s);
	sort_path(s);
	calcul(s);
	free_all(s, 1);
	exit(0);
}
