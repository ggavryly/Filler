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

void	print_res(t_map *map)
{
	ft_putnbr(map->best_y);
	ft_putchar(' ');
	ft_putnbr(map->best_x);
	ft_putchar('\n');
}

int		main(void)
{
	t_map	map;
	t_piece	piece;
	int		fd;

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
			ft_putstr("0 0\n");
			exit(0);
		}
		free_piece(&piece);
		print_res(&map);
	}
	return (0);
}
