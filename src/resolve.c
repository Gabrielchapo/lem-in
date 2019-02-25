/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:06:44 by gdrai             #+#    #+#             */
/*   Updated: 2019/01/30 13:49:36 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	resolve(t_struct *s, int good, int *tab)
{
	int	i_ants;
	int i;

	i_ants = 0;
	while (s->check_start < s->nb_ants)
	{
		i = s->start - 1;
		while (++i < good)
			soluce_handler(s, i, &i_ants, tab);
		write(1, "\n", 1);
	}
}

int		resolve1(t_struct *s, int cmp, int *tab, int tmp)
{
	int	i_ants;
	int i;
	int count;

	i_ants = 0;
	count = 0;
	while (s->check_start < s->nb_ants)
	{
		i = s->start - 1;
		while (++i < tmp)
			traversal(s, i, &i_ants, tab);
		count++;
		if (cmp != -1 && count > cmp)
			break ;
	}
	return (count);
}

int		*get_good(t_struct *s, int *tab)
{
	int i;

	i = 0;
	s->check_start = 0;
	i = 0;
	while (i < s->nb_rooms)
		tab[i++] = 0;
	return (tab);
}

void	calcul(t_struct *s)
{
	int good_count;
	int good;
	int *tab;
	int i;
	int current;

	s->start = 0;
	i = s->count_soluce;
	while (!s->soluce[s->start][s->nb_rooms])
		s->start++;
	if (!(tab = (int*)malloc(sizeof(int) * s->nb_rooms)))
		exit(0);
	good_count = resolve1(s, 1000, get_good(s, tab), i);
	while (i > 0)
	{
		current = resolve1(s, good_count, get_good(s, tab), i);
		if (current <= good_count)
		{
			good_count = current;
			good = i;
		}
		i--;
	}
	resolve(s, good, get_good(s, tab));
	free(tab);
}
