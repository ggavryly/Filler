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
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
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

int		read_map(t_map *m, int fd)
{
	int i;
	int j;

	i = 0;
	while (1)
	{
		if (m->l && ft_strstr(m->l, "Plateau"))
		{
			read_map_help(m, fd);
			while (get_next_line(fd, &m->l) > 0 && !ft_strstr(m->l, "Piece"))
			{
				j = 0;
				while (m->l[j] == ' ' || (m->l[j] >= '0' && m->l[j] <= '9'))
					j++;
				ft_strncpy(m->map[i++], m->l + j, m->w);
				ft_strdel(&m->l);
			}
			find_start(m);
			return (1);
		}
		else
			read_map_help2(m, fd);
	}
}

void	fig_w_h(t_piece *piece, t_map *map)
{
	int i;

	i = 0;
	while (map->l[i] < '0' || map->l[i] > '9')
		i++;
	piece->fig_h = ft_atoi(map->l + i);
	while (map->l[i] >= '0' && map->l[i] <= '9')
		i++;
	piece->fig_w = ft_atoi(map->l + i);
}

t_piece	*read_piece(t_map *map, int fd, t_piece *piece)
{
	size_t	i;

	i = 0;
	fig_w_h(piece, map);
	ft_strdel(&map->l);
	piece->fig = (char **)malloc(sizeof(char *) * piece->fig_h + 1);
	piece->fig[piece->fig_h] = NULL;
	while (i < piece->fig_h && get_next_line(fd, &map->l) > 0)
	{
		piece->fig[i] = (char *)malloc(sizeof(char) * piece->fig_w + 1);
		piece->fig[i] = ft_strncpy(piece->fig[i], map->l, piece->fig_w);
		i++;
		ft_strdel(&map->l);
	}
	return (piece);
}
