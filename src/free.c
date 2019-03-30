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
	free(piece->fig[i]);
	free(piece->fig);
	i = 0;
	while (piece->cords[i])
	{
		free(piece->cords[i]);
		i++;
	}
	free(piece->cords[i]);
	free(piece->cords);
}

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
				if (count++ == 0)
				{
					piece->start_y = i;
					piece->start_x = j;
				}
			}
			j++;
		}
		i++;
	}
	piece->cords = (int **)malloc(sizeof(int *) * count + 1);
	piece->cords[count] = NULL;
}

void	read_map_help(t_map *map, int fd)
{
	ft_strdel(&map->l);
	get_next_line(fd, &map->l);
	ft_strdel(&map->l);
}

void	read_map_help2(t_map *map, int fd)
{
	ft_strdel(&map->l);
	get_next_line(fd, &map->l);
}

void	init_staff(t_piece *piece, t_map *map)
{
	piece->value = 987654;
	piece->best_x = 0;
	piece->best_y = 0;
	map->best_y = 0;
	map->best_x = 0;
}
