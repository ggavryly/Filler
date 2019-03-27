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

void	needle_count(t_piece *piece, int count)
{
	int i;
	int j;

	i = 0;
	while (i < piece->fig_h)
	{
		j = 0;
		while (j < piece->fig_w)
		{
			if (piece->fig[i][j] == '*' && count == 0)
			{
				piece->start_x = j;
				piece->start_y = i;
				return;
			}
			else if (piece->fig[i][j] == '*')
			{
				count--;
			}
			j++;
		}
		i++;
	}
}

void	copy_cords(t_piece *piece, int cords[100][2])
{
	int k;

	k = 0;
	while (k < piece->count)
	{
		cords[k][0] = piece->cords[k][0];
		cords[k][1] = piece->cords[k][1];
		k++;
	}
}

void	rew_cords(t_piece *piece, int count, int cords[100][2])
{
	int k;

	k = 0;
	needle_count(piece, count);
	copy_cords(piece, cords);
	while (piece->cords[k])
	{
		cords[k][0] -= piece->start_y;
		cords[k][1] -= piece->start_x;
		k++;
	}
}

void	print_kord(int cords[100][2], t_piece *piece)
{
	int i;

	i = 0;
	while (piece->cords[i])
	{
		dprintf(2,"|%d - i|%d - j|\n", cords[i][0], cords[i][1]);
		i++;
	}
}

int 	try_put(t_map *map, t_piece *piece, int i, int j)
{
	int k;
	int tmp;
	int value[2];
	int count;
	int best_count;
	int cords[100][2];

	best_count = 0;
	value[0] = 999999;
	count = 0;
	while (count < piece->count)
	{
		rew_cords(piece, count, cords);
		k = 0;
		print_kord(cords, piece);
		value[1] = 0;
		while (piece->cords[k])
		{
			if ((i + cords[k][0] >= 0 && i + cords[k][0] < map->map_h
				 && j + cords[k][1] >= 0 && j + cords[k][1] < map->map_w))
			{
				tmp = map->hit_map[cords[k][0] + i][cords[k][1] + j];
				if (tmp != 0)
					value[1] += (tmp == -1) ? (100) : (tmp);
				else
					return (987654);
			}
			else
				return (987654);
			k++;
		}
		if (value[0] > value[1])
		{
			best_count = count;
			value[0] = value[1];
		}
		count++;
	}
	piece->best_count = best_count;
	return (value[0]);
}

int		test_ij(t_map *map, int i, int j)
{
	int count;

	count = 0;
	if (j + 1 < map->map_w && map->map[i][j + 1] == map->place)
		count++;
	if (i + 1 < map->map_h && map->map[i + 1][j] == map->place)
		count++;
	if (j - 1 >= 0 && map->map[i][j - 1] == map->place)
		count++;
	if (i - 1 >= 0 && map->map[i - 1][j] == map->place)
		count++;
	if (count == 4)
		return (0);
	return (1);
}

void	map_try_piece(t_map *map, t_piece *piece)
{
	int i;
	int j;
	int value[2];

	i = 0;
	value[1] = 0;
	value[0] = 987654;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (map->map[i][j] == ft_toupper(map->place) && test_ij(map, i, j))
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

