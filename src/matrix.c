/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:30:54 by gdrai             #+#    #+#             */
/*   Updated: 2019/01/29 16:11:12 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_sstrcmp(char *s1, char *s2, int j)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[j])
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		i++;
		j++;
	}
	if (s2[j] != '\n' && s2[j] != '-')
		return (1);
	return (0);
}

void	init_matrix(t_struct *s)
{
	int i;
	int k;

	i = 0;
	if (!(s->matrix = (int**)malloc(sizeof(int*) * (s->nb_rooms))))
		exit(0);
	while (i < s->nb_rooms)
	{
		k = 0;
		if (!(s->matrix[i] = (int*)malloc(sizeof(int) * (s->nb_rooms))))
			exit(0);
		while (k < s->nb_rooms)
			s->matrix[i][k++] = 0;
		i++;
	}
}

void	do_matrix(t_struct *s, int j)
{
	int i;
	int k;

	init_matrix(s);
	while (s->str[j])
	{
		i = 0;
		k = 0;
		while (i < s->nb_rooms && ft_sstrcmp(s->room_name[i], s->str, j)
			!= 0 && i < s->nb_rooms)
			i++;
		while (s->str[j] != '-')
			j++;
		j++;
		while (k < s->nb_rooms && ft_sstrcmp(s->room_name[k], s->str, j) != 0)
			k++;
		if (k == s->nb_rooms || i == s->nb_rooms)
			return ;
		while (s->str[j] != '\n')
			j++;
		s->matrix[k][i] = 1;
		s->matrix[i][k] = 1;
		j++;
	}
}
