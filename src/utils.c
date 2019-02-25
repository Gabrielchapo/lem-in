/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:45:49 by glavigno          #+#    #+#             */
/*   Updated: 2019/01/24 16:56:05 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	free_all(t_struct *s, int opt)
{
	int	i;

	i = -1;
	if (opt)
	{
		while (++i < s->nb_rooms)
		{
			if (i < s->count_soluce)
				ft_memdel((void**)&s->soluce[i]);
			ft_memdel((void**)&s->matrix[i]);
			ft_memdel((void**)&s->coord[i]);
			ft_memdel((void**)&s->room_name[i]);
		}
		ft_strdel(&s->str);
		ft_memdel((void**)&s->soluce);
		ft_memdel((void**)&s->matrix);
		ft_memdel((void**)&s->coord);
		ft_memdel((void**)&s->room_name);
		ft_memdel((void**)&s);
	}
	else
		ft_memdel((void**)&s);
}

void	clean_exit(t_struct *p, int opt)
{
	free_all(p, opt);
	ft_putendl("ERROR");
	exit(0);
}
