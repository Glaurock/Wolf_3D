/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:19:02 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/02 12:16:53 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

/*
** init des vals de base de la cam
** xy en 2 pour pas poper dans un mur
*/

void			cam_init(t_cam *cam, double fov, int onlyfov)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	if (onlyfov == 0)
	{
		ft_getspawn(&env->map);
		cam->fov = 0;
	}
	cam->fov += fov;
	if (cam->fov < 10)
		cam->fov = 10;
	if (cam->fov > 170)
		cam->fov = 170;
	cam->dir_x = 1;
	cam->dir_y = 0;
	cam->delta_x = 0;
	cam->delta_y = tan((cam->fov * 3.14 / 180.0) / 2);
}

/*
** action lorsque on appuy sur W
** on recup la position du joueur
** check des collisions puis deplacement
*/

void			cam_forward(t_cam *cam, t_map *map, double speed)
{
	int x_t_hited;
	int y_t_hited;

	map->hited_obj_x = (int)(cam->pos_x + cam->dir_x * speed * 3);
	map->hited_obj_y = (int)(cam->pos_y + cam->dir_y * speed * 3);
	x_t_hited = map->initial_map[(int)cam->pos_y * map->w + map->hited_obj_x];
	y_t_hited = map->initial_map[map->hited_obj_y * map->w + (int)cam->pos_x];
	if (check_collision(x_t_hited, y_t_hited, x_t_hited, map))
		cam->pos_x += cam->dir_x * speed;
	if (check_collision(x_t_hited, y_t_hited, y_t_hited, map))
		cam->pos_y += cam->dir_y * speed;
}

/*
** pareil ici mais dans l'autre sens lorsque appui sur S
*/

void			cam_backward(t_cam *cam, t_map *map, double speed)
{
	int x_t_hited;
	int y_t_hited;

	map->hited_obj_x = (int)(cam->pos_x - cam->dir_x * speed * 3);
	map->hited_obj_y = (int)(cam->pos_y - cam->dir_y * speed * 3);
	x_t_hited = map->initial_map[(int)cam->pos_y * map->w + map->hited_obj_x];
	y_t_hited = map->initial_map[map->hited_obj_y * map->w + (int)cam->pos_x];
	if (check_collision(x_t_hited, y_t_hited, x_t_hited, map))
		cam->pos_x -= cam->dir_x * speed;
	if (check_collision(x_t_hited, y_t_hited, y_t_hited, map))
		cam->pos_y -= cam->dir_y * speed;
}

/*
** Ici on calcul un nouvel angle de camera (rotation) losque on appui sur D
*/

void			cam_right(t_cam *cam, double speed)
{
	double dir_x;
	double delta_x;

	dir_x = cam->dir_x;
	delta_x = cam->delta_x;
	cam->dir_x = cam->dir_x * cos(speed) - cam->dir_y * sin(speed);
	cam->dir_y = dir_x * sin(speed) + cam->dir_y * cos(speed);
	cam->delta_x = cam->delta_x * cos(speed) - cam->delta_y * sin(speed);
	cam->delta_y = delta_x * sin(speed) + cam->delta_y * cos(speed);
}

/*
** Pareil mais dans l'autre sens lorsque appui sur A
*/

void			cam_left(t_cam *cam, double speed)
{
	double dir_x;
	double delta_x;

	dir_x = cam->dir_x;
	delta_x = cam->delta_x;
	cam->dir_x = cam->dir_x * cos(-speed) - cam->dir_y * sin(-speed);
	cam->dir_y = dir_x * sin(-speed) + cam->dir_y * cos(-speed);
	cam->delta_x = cam->delta_x * cos(-speed) - cam->delta_y * sin(-speed);
	cam->delta_y = delta_x * sin(-speed) + cam->delta_y * cos(-speed);
}
