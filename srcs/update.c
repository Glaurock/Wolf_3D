/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:51:45 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/02 12:17:57 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		timer_init(t_timer *timer)
{
	timer->last_time = clock();
	timer->delta = 0;
	timer->timer = 0;
	timer->ticks = 0;
}

void		get_next_time(t_timer *timer)
{
	timer->time_per_tick = CLOCKS_PER_SEC / FPS;
	timer->now = clock();
	timer->delta += (timer->now - timer->last_time) / timer->time_per_tick;
	timer->timer += timer->now - timer->last_time;
	timer->last_time = timer->now;
}

/*
** recupere la texture du dickman en fonction de la position
** du joueur en y et du sens de marche
*/

void		get_dickman_text(t_sprite *sprite)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	if (env->cam.pos_y < sprite->y)
		sprite->text_index = sprite->dir_x < 0 ? MONSTER_B : MONSTER;
	else
		sprite->text_index = sprite->dir_x < 0 ? MONSTER : MONSTER_B;
}

/*
** a chaque tick de game on deplace les dickmans, on checks les collisions
** avec les murs et on change de sens
*/

void		move_sprite(t_map *map, t_sprite *sprite)
{
	int		save_x;
	double	avoid_wall;

	if (sprite->type == MONSTER && sprite->del == 0 && sprite->timer_dead == 0)
	{
		save_x = (int)sprite->x;
		avoid_wall = sprite->dir_x > 0 ? 0.5 : -0.5;
		if (map_get(map, (int)(sprite->x + sprite->dir_x +
		avoid_wall), (int)sprite->y) > 0)
			sprite->dir_x = -sprite->dir_x;
		get_dickman_text(sprite);
		if ((sprite->x + sprite->dir_x) - save_x >= 1 ||
		(sprite->x + sprite->dir_x) - save_x <= 0)
		{
			map->initial_map[(int)sprite->y * map->w + save_x] = 0;
			map->initial_map[(int)sprite->y * map->w + (int)(sprite->x +
				sprite->dir_x)] = sprite->text_index;
		}
		sprite->x += sprite->dir_x;
	}
}

/*
** gere le clignement des dickmans
*/

void		dying_animation(t_env *env, t_sprite *sprite)
{
	sprite->timer_dead--;
	if (sprite->timer_dead % 4)
		sprite->text_index = 0;
	else
		sprite->text_index = MONSTER_D;
	if (sprite->timer_dead == 0)
	{
		sprite->del = 1;
		env->map.initial_map[(int)sprite->x + (int)sprite->y * env->map.w] = 0;
	}
}
