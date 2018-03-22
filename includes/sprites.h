/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:10:37 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/21 10:28:08 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "map.h"

# define SPRITE_SPEED 0.08
# define HIT_BOX 0.5

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	int				del;
	int				text_index;
	double			real_x;
	double			real_y;
	double			transform_x;
	double			transform_y;
	int				tex_x;
	int				tex_y;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	int				width;
	int				height;
	int				screen_x;
	double			real_dist;
	int				timer_dead;
	int				type;
}					t_sprite;

void				init_sprites(t_sprite **sprites, int nb);
void				del_sprite(t_map *map, int pos);
void				sort_sprites(int *order, double *dist, int nb);

#endif
