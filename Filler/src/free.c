/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:28:15 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/26 19:28:27 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void	free_piece(t_piece *piece)
{
	int i;

	i = 0;
	while (i < piece->fig_h)
	{
		free(piece->fig[i]);
		i++;
	}
	i = 0;
	while (piece->cords[i])
	{
		free(piece->cords[i]);
		i++;
	}
}

void	hit_999(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (map->hit_map[i][j] != 0 && map->hit_map[i][j] != -1)
				map->hit_map[i][j] = 999;
			j++;
		}
		i++;
	}
}

void	free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->map_h)
	{
		free(map->map[i]);
		free(map->hit_map[i]);
		i++;
	}

}
