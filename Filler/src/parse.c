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

	i = 0;
	while (i < piece->fig_h)
	{
		j = 0;
		while (j < piece->fig_w)
		{
			if (piece->fig[i][j] == '*')
			{
				piece->start_x = j;
				piece->start_y = i;
				return;
			}
			j++;
		}
		i++;
	}
}

void	count_cords(t_piece *piece)
{
	size_t i;
	size_t j;
	size_t count;

	i = 0;
	count = 0;
	while (i < piece->fig_h)
	{
		j = 0;
		while (j < piece->fig_w)
		{
			if (piece->fig[i][j] == '*')
				count++;
			j++;
		}
		i++;
	}
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
	count_cords(piece);
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
	size_t	flag;

	i = 0;
	flag = 1;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (flag && map->map[i][j] == map->aplace)
			{
				map->last_ax = j;
				map->last_ay = i;
				flag = 0;
			}
			if (map->map[i][j] == map->aplace)
				map->hit_map[i][j] = -2;
			else if (map->map[i][j] == map->place)
				map->hit_map[i][j] = -1;
			j++;
		}
		printf("%s\n", map->map[i]);
		i++;
	}
}

void	hit_8_fill(t_map *map, int i, int j, int hit_curr)
{
	if (i - 1 >= 0 && i - 1 < map->map_h && map->hit_map[i - 1][j] == 0)
		map->hit_map[i - 1][j] = hit_curr + 1;
	if(i - 1 >= 0 && i - 1 < map->map_h && j + 1 >= 0 && j + 1 < map->map_w
		&& map->hit_map[i - 1][j + 1] == 0)
		map->hit_map[i - 1][j + 1] = hit_curr + 1;
	if (j + 1 >= 0 && j + 1 < map->map_w && map->hit_map[i][j + 1] == 0)
		map->hit_map[i][j + 1] = hit_curr + 1;
	if(i + 1 >= 0 && i + 1 < map->map_h && j + 1 >= 0 && j + 1 < map->map_w
			&& map->hit_map[i + 1][j + 1] == 0)
		map->hit_map[i + 1][j + 1] = hit_curr + 1;
	if (i + 1 >= 0 && i + 1 < map->map_h && map->hit_map[i + 1][j] == 0)
		map->hit_map[i + 1][j] = hit_curr + 1;
	if(i + 1 >= 0 && i + 1 < map->map_h && j - 1 >= 0 && j - 1 < map->map_w
			&& map->hit_map[i + 1][j - 1] == 0)
		map->hit_map[i + 1][j - 1] = hit_curr + 1;
	if (j - 1 >= 0 && j - 1 < map->map_h && map->hit_map[i][j - 1] == 0)
		map->hit_map[i][j - 1] = hit_curr + 1;
	if(i - 1 >= 0 && i - 1 < map->map_h && j - 1 >= 0 && j - 1 < map->map_w
			&& map->hit_map[i - 1][j - 1] == 0)
		map->hit_map[i - 1][j - 1] = hit_curr + 1;
}

void	hit_re(t_map *map)
{
	int hit_curr;
	int i;
	int j;

	i = 0;
	hit_curr = 1;
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

void	hit_re_first(t_map *map)
{
	int hit_curr;
	int i;
	int j;

	i = 0;
	hit_curr = 0;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (map->map[i][j] == map->aplace)
				hit_8_fill(map, i, j, hit_curr);
			j++;
		}
		i++;
	}
}

void	parse_process(t_map *map, t_piece *piece)
{
	analize_piece(piece);
	init_cords(piece);
	hit_fill_xo(map);
	hit_re_first(map);
	hit_re(map);
}