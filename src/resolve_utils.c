/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:25:36 by glavigno          #+#    #+#             */
/*   Updated: 2019/01/29 17:08:04 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	print_soluce(int count, char *str)
{
	write(1, "L", 1);
	ft_putnbr(count);
	write(1, "-", 1);
	ft_putstr(str);
	write(1, " ", 1);
}

void	traversal(t_struct *s, int i, int *i_ants, int *tab)
{
	int	j;

	j = 0;
	while (++j < s->soluce[i][s->nb_rooms] - 1)
	{
		if (tab[s->soluce[i][j]])
		{
			(j == 1) ? s->check_start++ : 0;
			tab[s->soluce[i][j - 1]] = tab[s->soluce[i][j]];
			tab[s->soluce[i][j]] = 0;
		}
	}
	if (s->nb_ants - *i_ants > s->soluce[i][s->nb_rooms]
		- s->soluce[s->start][s->nb_rooms])
	{
		tab[s->soluce[i][s->soluce[i][s->nb_rooms] - 2]] = ++(*i_ants);
		if (s->soluce[i][1] == 0)
			s->check_start++;
	}
}

void	soluce_handler(t_struct *s, int i, int *i_ants, int *tab)
{
	int j;

	j = 0;
	while (++j < s->soluce[i][s->nb_rooms] - 1)
	{
		if (tab[s->soluce[i][j]])
		{
			(j == 1) ? s->check_start++ : 0;
			print_soluce(tab[s->soluce[i][j]],
				s->room_name[s->soluce[i][j - 1]]);
			tab[s->soluce[i][j - 1]] = tab[s->soluce[i][j]];
			tab[s->soluce[i][j]] = 0;
		}
	}
	if (s->nb_ants - *i_ants > s->soluce[i][s->nb_rooms]
		- s->soluce[s->start][s->nb_rooms])
	{
		tab[s->soluce[i][s->soluce[i][s->nb_rooms] - 2]] = ++(*i_ants);
		print_soluce(*i_ants,
			s->room_name[s->soluce[i][s->soluce[i][s->nb_rooms] - 2]]);
		(s->soluce[i][1] == 0) ? s->check_start++ : 0;
	}
}
