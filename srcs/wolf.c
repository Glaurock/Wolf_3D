/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:34:15 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/22 11:38:21 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void		init_env(t_env *env, char *filename)
{
	env->width = WIDTH;
	env->height = HEIGHT;
	if (!(env->mlx_ptr = mlx_init()))
		ft_exit(1);
	if (!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->width,
		env->height, "Wolf3D")))
		ft_exit(1);
	if (!(env->img = mlx_new_image(env->mlx_ptr, env->width, env->height)))
		ft_exit(1);
	env->tmp = mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->edn);
	load_text(env, env->textures);
	map_init(&(env->map), filename);
	init_sprites(&(env->sprites), env->nb_sprite);
	cam_init(&(env->cam), 66, 0);
	env->inputs.can_fire = 1;
	timer_init(&(env->timer));
	env->is_alive = 1;
	ft_show_commands();
}

/*
** malloc de la struct, creation du la window et de l'image puis appel
** aux init cam et map
** si on fail le malloc ou que !action on free lenv
*/

t_env			*ft_use_env(int action, char *filename)
{
	static t_env		*env;

	if (action == 1)
	{
		env = (t_env*)ft_memalloc(sizeof(t_env));
		if (env != 0)
			init_env(env, filename);
		else
			action = 0;
	}
	if (action == 0 && env != 0)
		ft_memdel((void**)&(env));
	return (env);
}

/*
** Expose_hook btw le drag le drag and drop de la fenetre
** la fonction draw est appele avec le bon timer pour 60fps
** tous les 10ieme de secondes, on update le game pour les mouvements
*/

int				expose_hook(void *param)
{
	t_env		*env;

	env = ft_use_env(-1, 0);
	param = 0;
	if (env && env->is_alive == 1)
	{
		get_next_time(&(env->timer));
		if (env->timer.delta >= 1)
		{
			input_action(env);
			draw_all(env);
		}
		if (env->timer.timer >= CLOCKS_PER_SEC / 10)
			update_game(env);
	}
	return (0);
}

/*
** on lance l'image , et on lance les hook.
*/

int				main(int argc, char **argv)
{
	t_env		*env;

	env = 0;
	if (argc == 2 && argv[1])
	{
		env = ft_use_env(1, argv[1]);
		if (env != 0 && env->mlx_ptr != 0)
		{
			mlx_hook(WIN, KeyPress, KeyPressMask, key_hook_press, 0);
			mlx_hook(WIN, KeyRelease, KeyReleaseMask, key_hook_release, 0);
			mlx_hook(WIN, 17, 0, exit_hook, 0);
			mlx_expose_hook(WIN, expose_hook, 0);
			mlx_loop_hook(MLX, expose_hook, 0);
			system("afplay sounds/bg_music.mp3 &");
			mlx_loop(MLX);
		}
	}
	ft_putstr("Usage : wolf3d <map>\n");
	ft_use_env(0, 0);
	return (0);
}
