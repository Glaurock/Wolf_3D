/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 10:28:03 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 11:26:36 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void			draw_gun(t_env *env, t_text texture)
{
	int x;
	int y;
	int x_start;
	int y_start;

	y = -1;
	x_start = env->width / 2 - texture.w / 2;
	y_start = env->height - texture.h;
	while (++y < texture.h)
	{
		x = -1;
		while (++x < texture.w)
		{
			if (texture.data[x + y * texture.w] != 0xFF00)
				img_put_px(env, texture.data[x + y * texture.w], x +
					x_start, y + y_start);
		}
	}
}

/*
** fonction draw (autrefois a l'interieur d'exposehook)
*/

void			draw_all(t_env *env)
{
	int	x;

	x = -1;
	env->map.coinc = ft_itoa(env->map.coin);
	while (++x < env->width)
		vertical_draw(env, x);
	sprite_casting(env, &(env->cam));
	input_action(env);
	draw_gun(env, env->textures[POMP]);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
	if (!env->is_alive)
		mlx_put_image_to_window(MLX, WIN, ENVTEX[GAMEOVER].text_ptr,
			WIDTH / 2 - ENVTEX[GAMEOVER].w /
			2, HEIGHT / 2 - ENVTEX[GAMEOVER].h / 2);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 10, 10, 0xFFFFFF, "Points:");
	mlx_string_put(MLX, WIN, 100, 10, 0xFFFFFF, env->map.coinc);
	ft_memdel((void **)&env->map.coinc);
	env->timer.delta -= 1;
	env->timer.ticks++;
}

/*
** on fou le pixel de couleur au bon endroit
** (decallage binaire pour recup le g et r)
*/

void			img_put_px(t_env *env, int color, int x, int y)
{
	if (y >= 0 && x >= 0 && y < HEIGHT && x < WIDTH)
	{
		env->tmp[y * env->sl + x * env->bpp / 8] = (color & 0xFF);
		env->tmp[y * env->sl + x * env->bpp / 8 + 1] = (color & 0xFF00) >> 8;
		env->tmp[y * env->sl + x * env->bpp / 8 + 2] = (color & 0xFF0000) >> 16;
	}
}

/*
** ici on draw une colonne a la fois , avec gestion ciel et sol
*/

void			vertical_draw(t_env *env, int x)
{
	double	cur_pos;
	int		y;

	y = 0;
	cur_pos = (double)x / (double)env->width;
	ray_init(&(env->ray), &(env->cam), cur_pos);
	ray_side_dist(&(env->ray));
	ray_dda(&(env->ray), &(env->map), 0);
	env->z_buffer[x] = env->ray.wall_dist;
	ray_display(env, &(env->ray), x, env->height);
	floor_casting(env, &(env->ray), x);
}
