/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:40:56 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/22 18:40:58 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void	analize_piece(t_piece *piece)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < piece->fig_h)
	{
		j = 0;
		while (j < piece->fig_w)
		{
			if (piece->fig[i][j] == '*')
			{
				count++;
			}
			j++;
		}
		i++;
	}
	piece->count = count;
	piece->cords = (int **)malloc(sizeof(int *) * count + 1);
	piece->cords[count] = NULL;
}

void	init_cords(t_piece *piece)
{
	int		i;
	int		j;
	int 	ij;

	i = 0;
	ij = 0;
	while (i < piece->fig_h)
	{
		j = 0;
		while (j < piece->fig_w)
		{
			if (piece->fig[i][j] == '*')
			{
				piece->cords[ij] = (int *)malloc(sizeof(int) * 2);
				piece->cords[ij][0] = i;
				piece->cords[ij++][1] = j;
			}
			j++;
		}
		i++;
	}
}

void	hit_fill_xo(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	print_map(map);
	dprintf(2, "\n ");
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (ft_toupper(map->map[i][j]) == map->aplace)
				map->hit_map[i][j] = 0;
			else if (ft_toupper(map->map[i][j]) == map->place)
				map->hit_map[i][j] = -1;
			j++;
		}
		i++;
	}
}

void	hit_8_fill(t_map *map, int i, int j, int hit_curr)
{
	if (i - 1 >= 0 && i - 1 < map->map_h && map->hit_map[i - 1][j] == 999)
		map->hit_map[i - 1][j] = hit_curr + 1;
	if(i - 1 >= 0 && i - 1 < map->map_h && j + 1 >= 0 && j + 1 < map->map_w
		&& map->hit_map[i - 1][j + 1] == 999)
		map->hit_map[i - 1][j + 1] = hit_curr + 1;
	if (j + 1 >= 0 && j + 1 < map->map_w && map->hit_map[i][j + 1] == 999)
		map->hit_map[i][j + 1] = hit_curr + 1;
	if(i + 1 >= 0 && i + 1 < map->map_h && j + 1 >= 0 && j + 1 < map->map_w
			&& map->hit_map[i + 1][j + 1] == 999)
		map->hit_map[i + 1][j + 1] = hit_curr + 1;
	if (i + 1 >= 0 && i + 1 < map->map_h && map->hit_map[i + 1][j] == 999)
		map->hit_map[i + 1][j] = hit_curr + 1;
	if(i + 1 >= 0 && i + 1 < map->map_h && j - 1 >= 0 && j - 1 < map->map_w
			&& map->hit_map[i + 1][j - 1] == 999)
		map->hit_map[i + 1][j - 1] = hit_curr + 1;
	if (j - 1 >= 0 && j - 1 < map->map_h && map->hit_map[i][j - 1] == 999)
		map->hit_map[i][j - 1] = hit_curr + 1;
	if(i - 1 >= 0 && i - 1 < map->map_h && j - 1 >= 0 && j - 1 < map->map_w
			&& map->hit_map[i - 1][j - 1] == 999)
		map->hit_map[i - 1][j - 1] = hit_curr + 1;
}

void	hit_re(t_map *map)
{
	int hit_curr;
	int i;
	int j;

	i = 0;
	hit_curr = 0;
	while (hit_curr < map->map_h)
	{
		while (i < map->map_h)
		{
			j = 0;
			while (j < map->map_w)
			{
				if (map->hit_map[i][j] == hit_curr)
					hit_8_fill(map, i, j, hit_curr);
				j++;
			}
			i++;
		}
		i = 0;
		hit_curr++;
	}
}


void	parse_process(t_map *map, t_piece *piece)
{
	hit_999(map);
	analize_piece(piece);
	init_cords(piece);
	hit_fill_xo(map);
	hit_re(map);
	print_hit(map);
	dprintf(2, "\n");
}