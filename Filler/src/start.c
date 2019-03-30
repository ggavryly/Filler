/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:58:50 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/22 18:58:51 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void	player_start(t_map *map, int fd)
{
	while(get_next_line(fd, &map->line) > 0)
	{
		if (ft_strstr(map->line, "p1") || ft_strstr(map->line, "p2"))
		{
			if (ft_strstr(map->line, "ggavryly") && ft_strstr(map->line, "p1"))
			{
				map->place = 'O';
				map->aplace = 'X';
			}
			else
			{
				map->place = 'X';
				map->aplace = 'O';
			}
			ft_strdel(&map->line);
			break ;
		}
		ft_strdel(&map->line);
	}
}

void	map_stat(t_map *map, int fd)
{
	int		i;

	i = 0;
	while (get_next_line(fd, &map->line) > 0)
	{
		if (ft_strstr(map->line, "Plateau"))
		{
			while (map->line[i] < '0' || map->line[i] > '9')
				i++;
			if (map->line[i] >= '0' && map->line[i] <= '9')
				map->map_h = ft_atoi(map->line + i);
			while (map->line[i] >= '0' && map->line[i] <= '9')
				i++;
			i++;
			if (map->line[i] >= '0' && map->line[i] <= '9')
				map->map_w = ft_atoi(map->line + i);
			break ;
		}
		ft_strdel(&map->line);
	}
}

void	map_init(t_map *map)
{
	int i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * map->map_h + 1);
	map->map[map->map_h] = NULL;
	while (i < map->map_h)
	{
		map->map[i] = (char *)malloc(sizeof(char) * map->map_w + 1);
		ft_memset(map->map[i], 46, (size_t)map->map_w + 1);
		map->map[i][map->map_w] = '\0';
		i++;
	}
}

void	hit_map_init(t_map *map)
{
	int i;

	i = 0;
	map->hit_map = (int **)malloc(sizeof(int *) * map->map_h + 1);
	map->hit_map[map->map_h] = NULL;
	while (i < map->map_h)
	{
		map->hit_map[i] = (int *)malloc(sizeof(int) * map->map_w);
		i++;
	}
}


