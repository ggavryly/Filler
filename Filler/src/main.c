/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:05 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/22 18:20:06 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void	print_kords(t_piece *piece)
{
	int i;

	i = 0;
	while (piece->cords[i])
	{
		dprintf(2,"|%d - i|%d - j|\n", piece->cords[i][0], piece->cords[i][1]);
		i++;
	}
}

void	print_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->map_h)
		dprintf(2,"%s\n", map->map[i++]);
}

void	print_piece(t_piece *piece)
{
	int i;

	i = 0;
	while (i < piece->fig_h)
		dprintf(2 ,"%s\n", piece->fig[i++]);
}

void    print_hit(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->map_h)
    {
        j = 0;
        while (j < map->map_w)
        {
           dprintf(2,"%d ", map->hit_map[i][j]);
           j++;
        }
        dprintf(2, "\n");
        i++;
    }
    ft_putchar('\n');
}

int		main(void)
{
	t_map	map;
	t_piece	piece;
	int		fd;

//	fd = open("../test.txt", O_RDONLY);
	fd = 0;
	player_start(&map, fd);
	map_stat(&map, fd);
	map_init(&map);
	hit_map_init(&map);
	while (read_map(&map, fd) && read_piece(&map, fd, &piece))
	{
		parse_process(&map, &piece);
		if (!fight(&map, &piece))
		{
			dprintf(1, "0 0\n");
			exit(0);
		}
		free_piece(&piece);
		dprintf(1, "%d %d\n", map.best_y, map.best_x);
	}
    return (0);
}
