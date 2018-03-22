/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 10:47:22 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 12:17:34 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

/*
** ici on define une map et on remplis notre struct map avec cette derniere
** FF = bloc plein, 00 bloc vide, 02 un mur, 01 un bloc vide bloquant le joueur
*/

void		ft_exit(int error)
{
	ft_use_env(0, 0);
	if (error == 1)
		ft_putendl("😡 Error : Can't malloc map.");
	else if (error == 2)
		ft_putendl("😡 Error : Can't open file.");
	else if (error == 3)
		ft_putendl("😡 Error : Incorrect map size.");
	else if (error == 4)
		ft_putendl("😡 Error : Can't open folder AND/OR empty files.");
	else if (error == 5)
		ft_putendl("😡 Error : Can't close the file.");
	else if (error == 6)
		ft_putendl("😡 Error : Impossible to spawn player.");
	else if (error == 7)
		ft_putendl("😡 Error : Wrong map border on Y for x = 0.");
	else if (error == 8)
		ft_putendl("😡 Error : Wrong map border on Y for x = max.");
	else if (error == 9)
		ft_putendl("😡 Error : Wrong map border on X for y = max.");
	else if (error == 10)
		ft_putendl("😡 Error : Unkwown texture ID.");
	else if (error == 11)
		ft_putendl("😡 Error : Invalid number of sprites.");
	exit(-1);
}

void		map_init(t_map *map, char *filename)
{
	ft_open(map, filename);
	ft_check_for_error(map);
	if ((close(map->fd) < 0))
		ft_exit(5);
	ft_open(map, filename);
	ft_get_size(map);
	ft_get_tex(map);
	if (!(map->data = (int *)malloc(sizeof(int) * (map->w * map->h))))
		ft_exit(1);
	if (!(map->initial_map = (int *)malloc(sizeof(int) * (map->w * map->h))))
		ft_exit(1);
	if (!(map->reset_map = (int *)malloc(sizeof(int) * (map->w * map->h))))
		ft_exit(1);
	ft_set_map(map);
	check_y_zero(map);
	ft_getspawn(map);
	map->coin = 0;
	map->initial_map = (int*)ft_memcpy(map->initial_map,
		map->data, (map->w * map->h) * sizeof(int));
	map->reset_map = (int*)ft_memcpy(map->reset_map, map->data,
		(map->w * map->h) * sizeof(int));
}

/*
** On parcour le tableau pour renvoyer ca valeur
*/

int			map_get(t_map *map, int x, int y)
{
	int		pos;

	if (map != 0 && x < map->w)
	{
		pos = x + (y * map->w);
		if (pos >= 0 && pos < (map->w * map->h))
		{
			return (map->data[pos]);
		}
	}
	return (0);
}
