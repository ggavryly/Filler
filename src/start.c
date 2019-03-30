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
	while (get_next_line(fd, &map->l) > 0)
	{
		if (ft_strstr(map->l, "p1") || ft_strstr(map->l, "p2"))
		{
			if (ft_strstr(map->l, "ggavryly") && ft_strstr(map->l, "p1"))
			{
				map->place = 'O';
				map->aplace = 'X';
			}
			else
			{
				map->place = 'X';
				map->aplace = 'O';
			}
			ft_strdel(&map->l);
			break ;
		}
		ft_strdel(&map->l);
	}
}

void	map_stat(t_map *map, int fd)
{
	int		i;

	i = 0;
	while (get_next_line(fd, &map->l) > 0)
	{
		if (ft_strstr(map->l, "Plateau"))
		{
			while (map->l[i] < '0' || map->l[i] > '9')
				i++;
			if (map->l[i] >= '0' && map->l[i] <= '9')
				map->h = ft_atoi(map->l + i);
			while (map->l[i] >= '0' && map->l[i] <= '9')
				i++;
			i++;
			if (map->l[i] >= '0' && map->l[i] <= '9')
				map->w = ft_atoi(map->l + i);
			break ;
		}
		ft_strdel(&map->l);
	}
}

void	map_init(t_map *map)
{
	int i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * map->h + 1);
	map->map[map->h] = NULL;
	while (i < map->h)
	{
		map->map[i] = (char *)malloc(sizeof(char) * map->w + 1);
		ft_memset(map->map[i], 46, (size_t)map->w + 1);
		map->map[i][map->w] = '\0';
		i++;
	}
}

void	hit_map_init(t_map *map)
{
	int	i;

	i = 0;
	map->hit_map = (int **)malloc(sizeof(int *) * map->h + 1);
	map->hit_map[map->h] = NULL;
	while (i < map->h)
	{
		map->hit_map[i] = (int *)malloc(sizeof(int) * map->w);
		i++;
	}
}
