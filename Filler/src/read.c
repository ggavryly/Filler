/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 11:22:19 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/23 11:22:20 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void	find_start(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (ft_toupper(map->map[i][j]) == map->place)
			{
				map->me_po[0] = i;
				map->me_po[1] = j;
			}
			j++;
		}
		i++;
	}
}

int		read_map(t_map *map, int fd)
{
	int i;
	int j;

	i = 0;
	while (1)
	{
		if (map->line && ft_strstr(map->line, "Plateau"))
		{
			ft_strdel(&map->line);
			get_next_line(fd, &map->line);
			ft_strdel(&map->line);
			while (get_next_line(fd, &map->line) > 0 && !ft_strstr(map->line, "Piece"))
			{
				j = 0;
				while (map->line[j] == ' ' || (map->line[j] >= '0' && map->line[j] <= '9'))
					j++;
				ft_strncpy(map->map[i], map->line + j, map->map_w);
				i++;
				ft_strdel(&map->line);
			}
			find_start(map);
			return (1);
		}
		else
		{
			ft_strdel(&map->line);
			get_next_line(fd, &map->line);
		}
	}
}

void		fig_w_h(t_piece *piece, t_map *map)
{
	int i;

	i = 0;
	while (map->line[i] < '0' || map->line[i] > '9')
		i++;
	piece->fig_h = ft_atoi(map->line + i);
	while (map->line[i] >= '0' && map->line[i] <= '9')
		i++;
	piece->fig_w = ft_atoi(map->line + i);
}

t_piece 	*read_piece(t_map *map, int fd, t_piece *piece)
{
	size_t 	i;

	i = 0;
	fig_w_h(piece, map);
	ft_strdel(&map->line);
	piece->fig = (char **)malloc(sizeof(char *) * piece->fig_h + 1);
	piece->fig[piece->fig_h] = NULL;
	while (i < piece->fig_h && get_next_line(fd, &map->line) > 0)
	{
		piece->fig[i] = (char *)malloc(sizeof(char) * piece->fig_w + 1);
		piece->fig[i] = ft_strncpy(piece->fig[i], map->line, piece->fig_w);
		i++;
		ft_strdel(&map->line);
	}
	return (piece);
}
