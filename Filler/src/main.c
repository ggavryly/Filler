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
		printf("|%d - i|%d - j|\n", piece->cords[i][0], piece->cords[i][1]);
		i++;
	}
}

void	print_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->map_h)
		printf("%s\n", map->map[i++]);
}

void	print_hit(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			printf("%d ", map->hit_map[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}

}

void	print_piece(t_piece *piece)
{
	int i;

	i = 0;
	while (i < piece->fig_h)
		printf("%s\n", piece->fig[i++]);
}

int		main(void)
{
	t_map	map;
	t_piece	piece;
	int 	i = 0;
	int		fd;

	fd = open("../test.txt", O_RDONLY);
//	fd = 0;
	piece.fig = (char **)malloc(sizeof(char **));
	player_start(&map, fd);
	map_stat(&map, fd);
	map_init(&map);
	hit_map_init(&map);
	while (read_map(&map, fd) && read_piece(&map, fd, &piece))
	{
		parse_process(&map, &piece);
		map_try_piece(&map, &piece);
		print_kords(&piece);
		printf("%d %d\n", piece.best_y - piece.start_y, piece.best_x - piece.start_x);
	}
}
