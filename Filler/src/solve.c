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

void	init_staff(t_piece *piece, t_map *map)
{
	piece->value = 987654;
	piece->best_x = 0;
	piece->best_y = 0;
	map->best_y = 0;
	map->best_x = 0;
}

int		solve_a(t_map *map, t_piece *piece)
{
	int i;
	int j;
	int nice;

	nice = 0;
	init_staff(piece, map);
	i = map->map_h - 1;
	while (i >= 0)
	{
		j = map->map_w - 1;
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
	i = map->map_h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < map->map_w)
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
	while (i < map->map_h)
	{
		j = map->map_w - 1;
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
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
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
	if (map->me_po[0] < (map->map_h / 2))
	{
		if (map->me_po[1] < map->map_w / 2)
			return (solve_a(map, piece));
		else if (map->me_po[1] >= map->map_w / 2)
			return (solve_b(map, piece));
	}
	else if (map->me_po[0] >= map->map_h / 2)
	{
		if (map->me_po[1] < map->map_w / 2)
			return (solve_c(map, piece));
		else if (map->me_po[1] >= map->map_w / 2)
			return (solve_d(map, piece));
	}
	return (0);
}

