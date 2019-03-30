/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:28:15 by ggavryly          #+#    #+#             */
/*   Updated: 2019/03/26 19:28:27 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"


void	free_piece(t_piece *piece)
{
	int i;

	i = 0;
	while (i < piece->fig_h)
	{
		free(piece->fig[i]);
		i++;
	}
	free(piece->fig[i]);
	free(piece->fig);
	i = 0;
	while (piece->cords[i])
	{
		free(piece->cords[i]);
		i++;
	}
	free(piece->cords[i]);
	free(piece->cords);
}
