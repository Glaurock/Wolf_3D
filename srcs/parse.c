/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:36:10 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 12:17:38 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void			ft_open(t_map *map, char *filename)
{
	if (!(map->fd = open(filename, O_RDONLY)))
		ft_exit(2);
}

static void		ft_get_nb_sprites(char *nb)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	env->nb_sprite = ft_atoi(nb);
}

void			ft_get_size(t_map *map)
{
	char	**splited;
	char	*line;
	int		count;

	count = 0;
	while (get_next_line(map->fd, &line) > 0)
	{
		if (count)
		{
			splited = ft_strsplit(line, ' ');
			map->w = ft_atoi(splited[0]);
			map->h = ft_atoi(splited[1]);
			ft_get_nb_sprites(splited[2]);
			free_splited(splited);
			ft_memdel((void **)&line);
			break ;
		}
		ft_memdel((void **)&line);
		count++;
	}
}

void			ft_get_tex(t_map *map)
{
	t_env	*env;
	char	**splited;
	char	*line;
	int		count;

	count = 0;
	env = ft_use_env(-1, 0);
	while (get_next_line(map->fd, &line) > 0 && count <= 1)
	{
		if (count)
		{
			splited = ft_strsplit(line, ' ');
			env->floor = ft_atoi(splited[0]);
			env->roof = ft_atoi(splited[1]);
			free_splited(splited);
		}
		ft_memdel((void **)&line);
		count++;
	}
	ft_memdel((void **)&line);
}

void			ft_set_map(t_map *map)
{
	char	**splited;
	char	*line;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	while (get_next_line(map->fd, &line) > 0 && count < map->h)
	{
		splited = ft_strsplit(line, ' ');
		while (splited[j])
		{
			map->data[i] = ft_atoi(splited[j]);
			i++;
			j++;
		}
		j = 0;
		free_splited(splited);
		ft_memdel((void **)&line);
		count++;
	}
}
