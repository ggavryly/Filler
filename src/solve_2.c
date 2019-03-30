/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:35:38 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/29 13:35:39 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

int		test_ij(t_map *m, t_piece *piece, int i, int j)
{
	int err;
	int k[2];
	int walk_k;

	err = 0;
	walk_k = 0;
	while (piece->cords[walk_k])
	{
		k[0] = piece->cords[walk_k][0];
		k[1] = piece->cords[walk_k][1];
		if (k[0] + i < 0 || k[0] + i >= m->h)
			err++;
		if (k[1] + j < 0 || k[1] + j >= m->w)
			err++;
		walk_k++;
	}
	if (err)
		return (0);
	return (1);
}

int		try_piece(t_map *map, t_piece *piece, int i, int j)
{
	int		touch;
	int		k[2];
	int		walk_k;

	walk_k = 0;
	touch = 0;
	if (!test_ij(map, piece, i, j))
		return (0);
	while (piece->cords[walk_k])
	{
		k[0] = piece->cords[walk_k][0];
		k[1] = piece->cords[walk_k][1];
		if (ft_toupper(map->map[i + k[0]][j + k[1]]) == map->place)
			touch++;
		if (ft_toupper(map->map[i + k[0]][j + k[1]]) == map->aplace)
			return (0);
		walk_k++;
	}
	if (touch == 1)
	{
		piece->best_y = i;
		piece->best_x = j;
		return (1);
	}
	return (0);
}

void	count_value(t_map *map, t_piece *piece, int *nice)
{
	int		walk_k;
	int		k[2];
	int		value;

	walk_k = 0;
	value = 0;
	while (piece->cords[walk_k])
	{
		k[0] = piece->cords[walk_k][0];
		k[1] = piece->cords[walk_k][1];
		value += map->hit_map[piece->best_y + k[0]][piece->best_x + k[1]];
		walk_k++;
	}
	if (value < piece->value)
	{
		piece->value = value;
		map->best_x = piece->best_x;
		map->best_y = piece->best_y;
	}
	*nice = 1;
}
