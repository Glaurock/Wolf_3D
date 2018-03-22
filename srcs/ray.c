/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:44:25 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/02 12:17:41 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

/*
** On init le rayon en fonction de la position du joueur et de la dir dans
** laquelle il regarde
*/

void			ray_init(t_ray *ray, t_cam *camera, double cur_pos)
{
	ray->pos_x = camera->pos_x;
	ray->pos_y = camera->pos_y;
	ray->dir_x = camera->dir_x + camera->delta_x * (2 * cur_pos - 1);
	ray->dir_y = camera->dir_y + camera->delta_y * (2 * cur_pos - 1);
	ray->map_x = (int)(ray->pos_x);
	ray->map_y = (int)(ray->pos_y);
	ray->delta_x = sqrt((ray->dir_y * ray->dir_y)
		/ (ray->dir_x * ray->dir_x) + 1);
	ray->delta_y = sqrt((ray->dir_x * ray->dir_x)
		/ (ray->dir_y * ray->dir_y) + 1);
}

/*
** calcul step et taille distance
*/

void			ray_side_dist(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x - ray->pos_x + 1.0) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y - ray->pos_y + 1.0) * ray->delta_y;
	}
}

void			check_hit_sprite(t_ray *ray, t_map *map, int kill_sprites)
{
	if (kill_sprites == 1 &&
	(map->initial_map[ray->map_x + ray->map_y * map->w] == MONSTER ||
	map->initial_map[ray->map_x + ray->map_y * map->w] == MONSTER_B))
		ray->hit_sprite = 1;
}

/*
** ici c'est le DDA (voir tuto)
*/

void			ray_dda(t_ray *ray, t_map *map, int kill_sprites)
{
	int		hit;

	hit = 0;
	while (hit == 0 && ray->hit_sprite == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
			if (ray->step_x == 1)
				ray->side = 1;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 2;
			if (ray->step_y == 1)
				ray->side = 3;
		}
		check_hit_sprite(ray, map, kill_sprites);
		if (map_get(map, ray->map_x, ray->map_y) > 0)
			hit = 1;
	}
}

void			ray_display(t_env *env, t_ray *ray, int pos, int height)
{
	int		line_height;
	int		start;
	int		color;

	if (ray->side <= 1)
		ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
		/ ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
		/ ray->dir_y;
	line_height = (int)(height / ray->wall_dist);
	start = -line_height / 2 + height / 2;
	ray->end = line_height / 2 + height / 2;
	start = start < 0 ? 0 : start;
	ray->end = ray->end >= height ? height : ray->end;
	get_tex_x(ray);
	while (start < ray->end)
	{
		get_tex_y(ray, start, height, line_height);
		color = get_pixel_from_texture(env, ray);
		img_put_px(env, color, pos, start);
		start++;
	}
}
