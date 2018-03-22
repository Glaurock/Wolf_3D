/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:22:56 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 12:22:58 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	ft_pause(void)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	env->is_alive = (env->is_alive == 0) ? 1 : 0;
	ft_reset_input();
	ft_putendl("Pause pressed !");
}

void	ft_reset_input(void)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	env->inputs.left = 0;
	env->inputs.right = 0;
	env->inputs.up = 0;
	env->inputs.down = 0;
	env->inputs.sleft = 0;
	env->inputs.sright = 0;
	env->inputs.can_fire = 1;
}

void	reset(t_env *env)
{
	env->is_alive = 1;
	env->map.initial_map = (int*)ft_memcpy(env->map.initial_map,
	env->map.reset_map, (env->map.w * env->map.h) * sizeof(int));
	env->map.data = (int*)ft_memcpy(env->map.data, env->map.reset_map,
	(env->map.w * env->map.h) * sizeof(int));
	ft_memdel((void **)&env->sprites);
	ft_memdel((void **)&env->sprites_order);
	ft_memdel((void **)&env->sprites_distance);
	init_sprites(&(env->sprites), env->nb_sprite);
	cam_init(&(env->cam), 66, 0);
	ft_reset_input();
	env->map.coin = 0;
	timer_init(&(env->timer));
	env->is_alive = 1;
}

void	ft_show_commands(void)
{
	ft_putendl("COMMANDS :");
	ft_putendl("W, A, S, D to move");
	ft_putendl("Q, E to straf");
	ft_putendl("+, - to change FOV");
	ft_putendl("P to pause the game");
	ft_putendl("SPACE to fire");
	ft_putendl("ENTER to reset");
	ft_putendl("ESC to exit");
}
