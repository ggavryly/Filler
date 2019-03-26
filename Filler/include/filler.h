/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:18:40 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/22 18:18:41 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
#include "../libft/include/libft.h"
#include <stdio.h>

typedef struct	s_map
{
	char 		place;
	char		aplace;
	size_t		map_h;
	size_t		map_w;
	char		*line;
	char		**map;
	int			**hit_map;
	int			last_ax;
	int			last_ay;
}				t_map;

typedef	struct	s_piece
{
	char		**fig;
	int			**cords;
	int			start_x;
	int			start_y;
	size_t		curr_x;
	size_t		curr_y;
	int			best_x;
	int			best_y;
	size_t		fig_h;
	size_t		fig_w;
}				t_piece;
void		print_kords(t_piece *piece);
void		map_try_piece(t_map *map, t_piece *piece);
void		print_hit(t_map *map);
void		parse_process(t_map *map, t_piece *piece);
void		player_start(t_map *map, int fd);
t_piece 	*read_piece(t_map *map, int fd, t_piece *piece);
void		map_stat(t_map *map, int fd);
void		map_init(t_map *map);
void		hit_map_init(t_map *map);
int			read_map(t_map *map, int fd);

#endif
