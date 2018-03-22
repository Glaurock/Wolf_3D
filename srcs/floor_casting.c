/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:28:08 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/02 11:34:48 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	get_floor_coord(t_ray *ray)
{
	if (ray->side <= 1 && ray->dir_x > 0)
	{
		ray->floor_x_wall = ray->map_x;
		ray->floor_y_wall = ray->map_y + ray->wall_x;
	}
	else if (ray->side <= 1 && ray->dir_x < 0)
	{
		ray->floor_x_wall = ray->map_x + 1.0;
		ray->floor_y_wall = ray->map_y + ray->wall_x;
	}
	else if (ray->side > 1 && ray->dir_y > 0)
	{
		ray->floor_x_wall = ray->map_x + ray->wall_x;
		ray->floor_y_wall = ray->map_y;
	}
	else
	{
		ray->floor_x_wall = ray->map_x + ray->wall_x;
		ray->floor_y_wall = ray->map_y + 1.0;
	}
}

static void	get_text_coord(t_env *env, t_ray *ray, int y)
{
	double	dist_player;
	double	current_dist;
	double	weight;
	double	current_floor_x;
	double	current_floor_y;

	dist_player = 0.0;
	current_dist = env->height / (2.0 * y - env->height);
	weight = (current_dist - dist_player) / (ray->wall_dist - dist_player);
	current_floor_x = weight * ray->floor_x_wall + (1.0 - weight) * ray->pos_x;
	current_floor_y = (weight * ray->floor_y_wall + (1.0 - weight)
		* ray->pos_y);
	ray->floor_text_x = (int)(current_floor_x * TEXT_WIDTH) % TEXT_WIDTH;
	ray->floor_text_y = (int)(current_floor_y * TEXT_HEIGHT) % TEXT_HEIGHT;
}

void		floor_casting(t_env *env, t_ray *ray, int pos)
{
	int		y;

	get_floor_coord(ray);
	if (ray->end < 0)
		ray->end = env->height;
	y = ray->end - 1;
	while (++y <= env->height)
	{
		get_text_coord(env, ray, y);
		if (ray->floor_text_y >= 0 && ray->floor_text_y < TEXT_HEIGHT &&
		ray->floor_text_x >= 0 && ray->floor_text_x < TEXT_WIDTH)
		{
			img_put_px(env, (env->textures[env->floor].data[TEXT_WIDTH *
			ray->floor_text_y + ray->floor_text_x] >> 1) & 0x7F7F7F, pos, y);
			img_put_px(env, env->textures[env->roof].data[TEXT_WIDTH *
			ray->floor_text_y + ray->floor_text_x], pos, env->height - y - 1);
		}
	}
}
