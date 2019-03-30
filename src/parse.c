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

void	init_cords(t_piece *piece)
{
	int		i;
	int		j;
	int		ij;

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

void	hit_8_fill(t_map *map, int i, int j, int hit_curr)
{
	if (i - 1 >= 0 && i - 1 < map->h && map->hit_map[i - 1][j] == 99)
		map->hit_map[i - 1][j] = hit_curr + 1;
	if (i - 1 >= 0 && i - 1 < map->h && j + 1 >= 0 && j + 1 < map->w
	&& map->hit_map[i - 1][j + 1] == 99)
		map->hit_map[i - 1][j + 1] = hit_curr + 1;
	if (j + 1 >= 0 && j + 1 < map->w && map->hit_map[i][j + 1] == 99)
		map->hit_map[i][j + 1] = hit_curr + 1;
	if (i + 1 >= 0 && i + 1 < map->h && j + 1 >= 0 && j + 1 < map->w
	&& map->hit_map[i + 1][j + 1] == 99)
		map->hit_map[i + 1][j + 1] = hit_curr + 1;
	if (i + 1 >= 0 && i + 1 < map->h && map->hit_map[i + 1][j] == 99)
		map->hit_map[i + 1][j] = hit_curr + 1;
	if (i + 1 >= 0 && i + 1 < map->h && j - 1 >= 0 && j - 1 < map->w
	&& map->hit_map[i + 1][j - 1] == 99)
		map->hit_map[i + 1][j - 1] = hit_curr + 1;
	if (j - 1 >= 0 && j - 1 < map->h && map->hit_map[i][j - 1] == 99)
		map->hit_map[i][j - 1] = hit_curr + 1;
	if (i - 1 >= 0 && i - 1 < map->h && j - 1 >= 0 && j - 1 < map->w
	&& map->hit_map[i - 1][j - 1] == 99)
		map->hit_map[i - 1][j - 1] = hit_curr + 1;
}

void	hit_re(t_map *map)
{
	int hit_curr;
	int i;
	int j;

	i = 0;
	hit_curr = 0;
	while (hit_curr < map->h + map->w)
	{
		while (i < map->h)
		{
			j = 0;
			while (j < map->w)
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

void	hit_99(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			map->hit_map[i][j] = 99;
			if (ft_toupper(map->map[i][j]) == map->aplace)
				map->hit_map[i][j] = 0;
			else if (ft_toupper(map->map[i][j]) == map->place)
				map->hit_map[i][j] = -1;
			j++;
		}
		i++;
	}
}

void	parse_process(t_map *map, t_piece *piece)
{
	hit_99(map);
	analize_piece(piece);
	init_cords(piece);
	hit_re(map);
}
