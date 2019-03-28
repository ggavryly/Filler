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

void	print_kord(int cords[100][2], t_piece *piece, int count)
{
	int i;

	i = 0;
	dprintf(2, "%d -", count);
	while (piece->cords[i])
	{
		dprintf(2,"|%d - i|%d - j|\n", cords[i][0], cords[i][1]);
		i++;
	}
	dprintf(2, "\n");
}

int 	try_put(t_map *map, t_piece *piece, int ij[2], int cords[100][2])
{
	int k;
	int tmp[2];
	int value[2];
	int count;

	value[0] = 987654;
	count = 0;
	while (count < piece->count)
	{
		rew_cords(piece, count, cords);
		k = 0;
		print_kord(cords, piece, count);
		value[1] = 0;
		tmp[1] = 0;
		while (piece->cords[k])
		{
			if ((ij[0] + cords[k][0] >= 0 && ij[0] + cords[k][0] < map->map_h
				 && ij[1] + cords[k][1] >= 0 && ij[1] + cords[k][1] < map->map_w))
			{
				tmp[0] = map->hit_map[cords[k][0] + ij[0]][cords[k][1] + ij[1]];
				if (tmp[0] != 0 && tmp[1] != 2)
				{
					if (tmp[0] == -1)
						tmp[1]++;
					value[1] += (tmp[0] == -1) ? (100) : (tmp[0]);
				}
				else
					return (987654);
			}
			else
				return (987654);
			k++;
		}
		if (value[0] > value[1])
		{
			piece->best_count = count;
			value[0] = value[1];
		}
		count++;
	}
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

void	map_try_piece(t_map *map, t_piece *piece, int cords[100][2])
{
	int ij[2];
	int value[2];

	ij[0] = 0;
	value[1] = 0;
	value[0] = 987654;
	while (ij[0] < map->map_h)
	{
		ij[1] = 0;
		while (ij[1] < map->map_w)
		{
			if (map->map[ij[0]][ij[1]] == ft_toupper(map->place) && test_ij(map, ij[0], ij[1]))
			{
				value[1] = try_put(map, piece, ij, cords);
				if (value[1] < value[0])
				{
					value[0] = value[1];
					piece->best_xy[1] = ij[1];
					piece->best_xy[0] = ij[0];
				}
			}
			ij[1]++;
		}
		ij[0]++;
	}
}

