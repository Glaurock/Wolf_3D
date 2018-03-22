/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:12:05 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/02 12:17:45 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		malloc_tabs(t_env *env, int nb)
{
	env->sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * nb);
	env->sprites_order = (int*)ft_memalloc(sizeof(int) * nb);
	env->sprites_distance = (double*)ft_memalloc(sizeof(double) * nb);
}

void			init_sprites(t_sprite **sprites, int nb)
{
	t_env	*env;
	int		i;
	int		index;

	env = ft_use_env(-1, 0);
	malloc_tabs(env, nb);
	i = -1;
	index = 0;
	while (++i < env->map.w * env->map.h)
	{
		if (env->map.data[i] >= SPRITES_TEXT)
		{
			(*sprites)[index].x = i % env->map.w + 0.5;
			(*sprites)[index].y = i / env->map.w + 0.5;
			(*sprites)[index].del = 0;
			(*sprites)[index].text_index = env->map.data[i];
			(*sprites)[index].dir_x = -SPRITE_SPEED;
			(*sprites)[index].type = env->map.data[i];
			if (env->map.data[i] == MONSTER_B)
				(*sprites)[index].type = MONSTER;
			(*sprites)[index].timer_dead = 0;
			env->map.data[i] = 0;
			index++;
		}
	}
}

/*
** on parcours le sprite en x et en y calculer avant
** on recupere le bon pixel dans la texture et on put pixel
*/

static void		sprite_draw(t_env *env, t_sprite *sprite)
{
	int x;
	int y;
	int d;
	int color;

	x = sprite->draw_start_x - 1;
	while (++x < sprite->draw_end_x)
	{
		sprite->tex_x = (int)(256 * (x - (-sprite->width
		/ 2 + sprite->screen_x)) * TEXT_WIDTH / sprite->width) / 256;
		if (sprite->transform_y > 0 && x > 0 && x < WIDTH
		&& sprite->transform_y < env->z_buffer[x])
		{
			y = sprite->draw_start_y - 1;
			while (++y < sprite->draw_end_y)
			{
				d = y * 256 - HEIGHT * 128 + sprite->height * 128;
				sprite->tex_y = ((d * TEXT_HEIGHT) / sprite->height) / 256;
				color = ENVTEX[sprite->text_index].data
				[sprite->tex_y * TEXT_WIDTH + sprite->tex_x];
				if (color != 0xFF00)
					img_put_px(env, color, x, y);
			}
		}
	}
}

static void		sprite_calc(t_cam *cam, t_sprite *s)
{
	double inv_det;

	s->real_x = s->x - cam->pos_x;
	s->real_y = s->y - cam->pos_y;
	inv_det = 1.0 / (cam->delta_x * cam->dir_y - cam->dir_x * cam->delta_y);
	s->transform_x = inv_det * (cam->dir_y * s->real_x
	- cam->dir_x * s->real_y);
	s->transform_y = inv_det * (-cam->delta_y * s->real_x +
	cam->delta_x * s->real_y);
	s->screen_x = (int)((WIDTH / 2) * (1 + s->transform_x / s->transform_y));
	s->height = abs((int)(HEIGHT / s->transform_y));
	s->draw_start_y = -s->height / 2 + HEIGHT / 2;
	s->draw_start_y = s->draw_start_y < 0 ? 0 : s->draw_start_y;
	s->draw_end_y = s->height / 2 + HEIGHT / 2;
	s->draw_end_y = s->draw_end_y >= HEIGHT ? HEIGHT - 1 : s->draw_end_y;
	s->width = abs((int)(HEIGHT / s->transform_y));
	s->draw_start_x = -s->width / 2 + s->screen_x;
	s->draw_start_x = s->draw_start_x < 0 ? 0 : s->draw_start_x;
	s->draw_end_x = s->width / 2 + s->screen_x;
	s->draw_end_x = s->draw_end_x >= WIDTH ? WIDTH - 1 : s->draw_end_x;
}

/*
** Fonction d'affichage des sprites
** Sort en fonction de leur distance, imprime les plus loin d'abord
** Gere aussi la collision avec le joueur pour le gameover
*/

void			sprite_casting(t_env *env, t_cam *cam)
{
	int i;

	i = -1;
	while (++i < env->nb_sprite)
	{
		env->sprites_order[i] = i;
		env->sprites_distance[i] = ((cam->pos_x - env->sprites[i].x) *
		(cam->pos_x - env->sprites[i].x) +
		(cam->pos_y - env->sprites[i].y) * (cam->pos_y - env->sprites[i].y));
		collide_player_sprite(env, i);
	}
	sort_sprites(env->sprites_order, env->sprites_distance, env->nb_sprite);
	i = -1;
	while (++i < env->nb_sprite)
	{
		if (env->sprites[env->sprites_order[i]].del == 0
		&& env->sprites[env->sprites_order[i]].text_index != 0)
		{
			sprite_calc(cam, &(env->sprites[env->sprites_order[i]]));
			sprite_draw(env, &(env->sprites[env->sprites_order[i]]));
		}
	}
}
