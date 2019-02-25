/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 10:00:18 by gdrai             #+#    #+#             */
/*   Updated: 2019/01/29 16:12:49 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		check_room(char *line, t_struct *s)
{
	int i;

	i = 0;
	if (!line[0])
		return (1);
	if (line[0] == 'L' || line[0] == ' ')
		clean_exit(s, 0);
	while (line[i] != ' ' && line[i] && line[i] != '-')
		i++;
	if (line[i++] == '-')
		return (0);
	if (line[i] < 48 || line[i] > 57)
		clean_exit(s, 0);
	while (line[i] >= 48 && line[i] <= 57)
		i++;
	if (line[i++] != ' ' || line[i] < 48 || line[i] > 57)
		clean_exit(s, 0);
	while (line[i] >= 48 && line[i] <= 57)
		i++;
	if (line[i] != '\0')
		clean_exit(s, 0);
	if (!(s->str = ft_strjoin_free(s->str, line)))
		exit(0);
	s->nb_rooms++;
	return (1);
}

void	check_start_end(char *line, t_struct *s)
{
	if (ft_strcmp(line, "##end") == 0)
	{
		s->check_end++;
		if (!(s->str = ft_strjoin_free(s->str, line)))
			exit(0);
	}
	if (ft_strcmp(line, "##start") == 0)
	{
		s->check_start++;
		if (!(s->str = ft_strjoin_free(s->str, line)))
			exit(0);
	}
}

int		check_links(char *line, t_struct *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '-')
			count++;
		if (line[i] == ' ')
			return (0);
		i++;
	}
	i = 0;
	if (line[0] == '-' || line[0] == ' ' || count != 1)
		return (0);
	while (line[i] != '-' && line[i])
		i++;
	if (line[i] != '-' || line[i + 1] == '-' ||
		line[i + 1] == '\n' || !line[i + 1])
		return (0);
	if (!(s->str = ft_strjoin_free(s->str, line)))
		exit(0);
	return (1);
}

int		no_idea(t_struct *s, char *line)
{
	if (line[0] != '#' && line[0] != '\0')
	{
		if (!check_links(line, s))
		{
			ft_strdel(&line);
			return (0);
		}
	}
	ft_strdel(&line);
	return (1);
}

int		check_gnl(t_struct *s)
{
	char *line;

	check_nb_ants(s);
	s->str = ft_strdup("\0");
	while (get_next_line(0, &line) == 1)
	{
		(line[0] == '#' && line[1] == '#') ? check_start_end(line, s) : 0;
		if (line[0] != '#' && check_room(line, s) == 0)
			break ;
		ft_strdel(&line);
	}
	if (s->check_end != 1 || s->check_start != 1)
	{
		ft_strdel(&s->str);
		clean_exit(s, 0);
	}
	(line == NULL) ? clean_exit(s, 0) : 0;
	if (!no_idea(s, line))
		return (0);
	while (get_next_line(0, &line) == 1)
	{
		if (!no_idea(s, line))
			return (0);
	}
	return (0);
}
