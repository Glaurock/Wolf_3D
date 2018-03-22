/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 10:02:44 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 12:17:28 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	check_y_zero(t_map *map)
{
	int i;

	i = 0;
	while (i < map->h)
	{
		if (map_get(map, 0, i) != 2)
			ft_exit(7);
		if (map_get(map, map->w - 1, i) != 2)
			ft_exit(8);
		i++;
	}
	i = 0;
	while (i < map->w)
	{
		if (map_get(map, i, map->h - 1) != 2)
			ft_exit(9);
		i++;
	}
}

void	check_x(t_map *map)
{
	int max;
	int i;

	i = 0;
	max = 0;
	map->linenb++;
	map->splited = ft_strsplit(map->line, ' ');
	checkforletter(map);
	while (map->splited[i])
	{
		if (ft_atoi(map->splited[i]) < 0)
			ft_exit_line(5, map->linenb);
		verif_number(ft_atoi(map->splited[i]));
		max++;
		i++;
	}
	if (max != map->w)
		ft_exit_line(4, map->linenb);
	free_splited(map->splited);
}

void	ft_getspawn(t_map *map)
{
	int		i;
	int		j;
	int		spawned;
	t_env	*env;

	spawned = 0;
	env = ft_use_env(-1, 0);
	i = -1;
	j = -1;
	while (++j < map->w && !spawned)
	{
		i = -1;
		while (++i < map->h)
		{
			if (j > 0 && map_get(map, j, i) == 0)
			{
				env->cam.pos_x = j + 0.5;
				env->cam.pos_y = i + 0.5;
				spawned = 1;
				break ;
			}
		}
	}
	if (!spawned)
		ft_exit(6);
}
