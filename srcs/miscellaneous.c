/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:10:18 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 11:22:13 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "update.h"
#include <inputs.h>
#include <textures.h>

void	update_game(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->nb_sprite)
	{
		move_sprite(&(env->map), &(env->sprites[i]));
		if (env->sprites[i].timer_dead > 0)
			dying_animation(env, &(env->sprites[i]));
	}
	env->timer.ticks = 0;
	env->timer.timer = 0;
}

/*
** exit propre lorsque ESC appuye // DEVRA AUSSI GERER LES FREES !
*/

int		exit_hook(void *param)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	param = 0;
	destroy_text(env, env->textures);
	mlx_destroy_image(env->mlx_ptr, env->img);
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	ft_memdel((void **)&env->sprites);
	ft_memdel((void **)&env->sprites_order);
	ft_memdel((void **)&env->sprites_distance);
	if (env->map.data)
		ft_memdel((void **)&env->map.data);
	if (env->map.initial_map)
		ft_memdel((void **)&env->map.initial_map);
	if (env->map.reset_map)
		ft_memdel((void **)&env->map.reset_map);
	ft_use_env(0, 0);
	system("killall afplay");
	exit(EXIT_SUCCESS);
}

/*
** detruit toutes les textures a la fin du jeu
*/

void	destroy_text(t_env *env, t_text *textures)
{
	mlx_destroy_image(env->mlx_ptr, textures[WALL].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[3].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[4].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[WALL_BRICK].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[DIAMOND].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[GROUND].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[SECRET_PATH].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[CHEST].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[MONSTER].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[MONSTER_B].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[MONSTER_D].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[BARREL].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[POMP].text_ptr);
	mlx_destroy_image(env->mlx_ptr, textures[GAMEOVER].text_ptr);
}

void	free_splited(char **splited)
{
	int i;

	i = 0;
	if (!splited)
		return ;
	while (splited[i])
	{
		ft_memdel((void **)&splited[i]);
		i++;
	}
	ft_memdel((void **)&splited);
}

void	line_size(char **splited, int action)
{
	int i;

	i = 0;
	while (splited[i])
		i++;
	if (action == 0 && i != 3)
		ft_exit(2);
	else if (action == 1 && i != 2)
		ft_exit(2);
}
