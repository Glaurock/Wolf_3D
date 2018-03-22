/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:32:31 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/02 08:35:55 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** ici on fait les deplacement en appelant une autre fonction pour le keyrepeat
** ici faut juste prendre en compte qu'on ce deplace ou qu'on rotate de notre
** variable SPEED_MOVE, ou SPEED_ROT
** Pour strafer on fait une douille astral, c'est a dire qu'on fait regarder
** un court instant vers la direction du straf, puis on avance, puis on regarde
** dans le sens inverse ce qui donne l'impression plutot reussi de straf
*/

void			input_action(t_env *env)
{
	if (env->inputs.left == 1)
		cam_left(&(env->cam), SPEED_ROT);
	if (env->inputs.right == 1)
		cam_right(&(env->cam), SPEED_ROT);
	if (env->inputs.up == 1)
		cam_forward(&(env->cam), &(env->map), SPEED_MOVE);
	if (env->inputs.down == 1)
		cam_backward(&(env->cam), &(env->map), SPEED_MOVE);
	if (env->inputs.sleft == 1)
	{
		cam_left(&(env->cam), 1.57);
		cam_forward(&(env->cam), &(env->map), 0.10);
		cam_left(&(env->cam), -1.57);
	}
	if (env->inputs.sright == 1)
	{
		cam_right(&(env->cam), 1.57);
		cam_forward(&(env->cam), &(env->map), 0.10);
		cam_right(&(env->cam), -1.57);
	}
	if (env->inputs.fire == 1)
		check_kills(env);
}

/*
** ici on change juste le FOV (Field Of View = Champ de vision)
** en gros plus c'est haut plus on vois les choses plates.
*/

static void		key_hook_press_cam(t_env *env, int keycode)
{
	if (keycode == FOVUP)
		cam_init(&(env->cam), 1, 1);
	if (keycode == FOVDOWN)
		cam_init(&(env->cam), -1, 1);
}

static void		reset_escape(int keycode, t_env *env)
{
	if (keycode == 53)
		exit_hook(env);
	if (keycode == ENTER)
	{
		system("killall afplay");
		system("afplay sounds/bg_music.mp3 &");
		reset(env);
	}
}

/*
** ici on gere juste le keypress en repeat
*/

int				key_hook_press(int keycode)
{
	t_env		*env;

	env = ft_use_env(-1, 0);
	reset_escape(keycode, env);
	if (keycode == PAUSE)
		ft_pause();
	if (env && env->is_alive)
	{
		if (keycode == FORWARD)
			env->inputs.up = 1;
		if (keycode == BACKWARD)
			env->inputs.down = 1;
		if (keycode == LEFT)
			env->inputs.left = 1;
		if (keycode == RIGHT)
			env->inputs.right = 1;
		if (keycode == STRAFL)
			env->inputs.sleft = 1;
		if (keycode == STRAFR)
			env->inputs.sright = 1;
		if (keycode == FIRE)
			env->inputs.fire = 1;
		key_hook_press_cam(env, keycode);
	}
	return (0);
}

/*
** et ici on gere juste quand on release pour arreter la boucle sur les actions
*/

int				key_hook_release(int keycode, void *param)
{
	t_env		*env;

	env = ft_use_env(-1, 0);
	param = 0;
	if (env && env->is_alive)
	{
		if (keycode == FORWARD)
			env->inputs.up = 0;
		if (keycode == BACKWARD)
			env->inputs.down = 0;
		if (keycode == LEFT)
			env->inputs.left = 0;
		if (keycode == RIGHT)
			env->inputs.right = 0;
		if (keycode == STRAFL)
			env->inputs.sleft = 0;
		if (keycode == STRAFR)
			env->inputs.sright = 0;
		if (keycode == FIRE)
		{
			env->inputs.fire = 0;
			env->inputs.can_fire = 1;
		}
	}
	return (0);
}
