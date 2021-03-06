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
# include "../libft/include/libft.h"
# include <stdio.h>

typedef struct	s_map
{
	char		place;
	char		aplace;
	int			h;
	int			w;
	int			me_po[2];
	int			best_x;
	int			best_y;
	char		*l;
	char		**map;
	int			**hit_map;
}				t_map;

typedef	struct	s_piece
{
	char		**fig;
	int			**cords;
	int			value;
	int			start_x;
	int			start_y;
	int			best_x;
	int			best_y;
	int			fig_h;
	int			fig_w;
}				t_piece;

void			init_staff(t_piece *piece, t_map *map);
void			read_map_help(t_map *map, int fd);
void			read_map_help2(t_map *map, int fd);
void			analize_piece(t_piece *piece);
void			hit_map_init(t_map *map);
void			free_piece(t_piece *piece);
int				fight(t_map *map, t_piece *piece);
int				try_piece(t_map *map, t_piece *piece, int i, int j);
void			parse_process(t_map *map, t_piece *piece);
void			player_start(t_map *map, int fd);
t_piece			*read_piece(t_map *map, int fd, t_piece *piece);
void			map_stat(t_map *map, int fd);
void			map_init(t_map *map);
int				read_map(t_map *map, int fd);
void			count_value(t_map *map, t_piece *piece, int *nice);

#endif
