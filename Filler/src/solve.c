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

void	rew_cords(t_piece *piece)
{
	int i;
	int j;
	int k;
	int f;

	i = 0;
	k = 1;
	f = 0;
	while (i < piece->fig_h)
	{
		j = 0;
		while (j < piece->fig_w)
		{
			if (piece->cords[i][j] == '*' && f)
			{
				piece->cords[k][1] = j - piece->start_x;
				piece->cords[k][0] = i - piece->start_y;
				k++;
			}
			else if (piece->cords[i][j] == '*' && !f)
				f = 1;
			j++;
		}
		i++;
	}
}

int 	try_put(t_map *map, t_piece *piece, int i, int j)
{
	int k;
	int value;

	k = 1;
	value = 0;
	while (piece->cords[k])
	{
		if ((i + piece->cords[k][0] >= 0 && i + piece->cords[k][0] < map->map_h
		&& j + piece->cords[k][1] >= 0 && j + piece->cords[k][1] < map->map_w))
		{
			if (map->hit_map[piece->cords[k][0] + i][piece->cords[k][1] + j] == -2)
				return (987654);
			else
				value += map->hit_map[piece->cords[k][0] + i][piece->cords[k][1] + j];
		}
		else
			return (987654);
		k++;
	}
	return (1);
}

void	map_try_piece(t_map *map, t_piece *piece)
{
	int i;
	int j;
	int value[2];

	i = 0;
	value[0] = 987654;
	print_kords(piece);
	rew_cords(piece);
	ft_putstr("REW_CORD\n");
	print_kords(piece);
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (map->map[i][j] == map->place)
			{
				value[1] = try_put(map, piece, i, j);
				if (value[1] < value[0])
				{
					value[0] = value[1];
					piece->best_x = j;
					piece->best_y = i;
				}
			}
			j++;
		}
		i++;
	}
}

