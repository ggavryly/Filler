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

void	scip_to_map(t_map *map, int fd)
{
	while (1)
	{
		if (ft_strstr(map->line, "   "))
			return;
		else
			get_next_line(fd, &map->line);
	}
}

int		read_map(t_map *map, int fd)
{
	int i;

	i = 0;
	while (ft_strstr(map->line, "Plateau") || get_next_line(fd, &map->line) > 0)
	{
		if (ft_strstr(map->line, "Plateau"))
		{
			scip_to_map(map, fd);
			while (get_next_line(fd, &map->line) > 0 && !ft_strstr(map->line, "Piece"))
			{
				while (*map->line == ' ' || (*map->line >= '0' && *map->line <= '9'))
					map->line++;
				ft_strncpy(map->map[i], map->line, map->map_w);
				i++;
			}
			return (1);
		}
	}
	return (0);
}

t_piece 	*read_piece(t_map *map, int fd, t_piece *piece)
{
	int		flag;
	size_t 	i;

	flag = 0;
	i = 0;
	while (!ft_strstr(map->line, "<got") && get_next_line(fd, &map->line) > 0)
	{
		if (!flag)
		{
			piece->fig_w = ft_strlen(map->line);
			flag = 1;
		}
		if (!ft_strstr(map->line, "<got"))
		{
			piece->fig[i] = ft_strsub(map->line, 0, map->map_w);
			i++;
		}
	}
	piece->fig_h = i;
	return (piece);
}
