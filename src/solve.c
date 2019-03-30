/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:33:21 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/25 16:33:23 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

int		solve_a(t_map *map, t_piece *piece)
{
	int i;
	int j;
	int nice;

	nice = 0;
	init_staff(piece, map);
	i = map->h - 1;
	while (i >= 0)
	{
		j = map->w - 1;
		while (j >= 0)
		{
			if (try_piece(map, piece, i, j))
				count_value(map, piece, &nice);
			j--;
		}
		i--;
	}
	return (nice);
}

int		solve_b(t_map *map, t_piece *piece)
{
	int i;
	int j;
	int nice;

	nice = 0;
	init_staff(piece, map);
	i = map->h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < map->w)
		{
			if (try_piece(map, piece, i, j))
				count_value(map, piece, &nice);
			j++;
		}
		i--;
	}
	return (nice);
}

int		solve_c(t_map *map, t_piece *piece)
{
	int i;
	int j;
	int nice;

	nice = 0;
	i = 0;
	init_staff(piece, map);
	while (i < map->h)
	{
		j = map->w - 1;
		while (j >= 0)
		{
			if (try_piece(map, piece, i, j))
				count_value(map, piece, &nice);
			j--;
		}
		i++;
	}
	return (nice);
}

int		solve_d(t_map *map, t_piece *piece)
{
	int i;
	int j;
	int nice;

	i = 0;
	nice = 0;
	init_staff(piece, map);
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (try_piece(map, piece, i, j))
				count_value(map, piece, &nice);
			j++;
		}
		i++;
	}
	return (nice);
}

int		fight(t_map *map, t_piece *piece)
{
	if (map->me_po[0] < (map->h / 2))
	{
		if (map->me_po[1] < map->w / 2)
			return (solve_a(map, piece));
		else if (map->me_po[1] >= map->w / 2)
			return (solve_b(map, piece));
	}
	else if (map->me_po[0] >= map->h / 2)
	{
		if (map->me_po[1] < map->w / 2)
			return (solve_c(map, piece));
		else if (map->me_po[1] >= map->w / 2)
			return (solve_d(map, piece));
	}
	return (0);
}
