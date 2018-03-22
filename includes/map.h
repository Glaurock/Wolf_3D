/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 10:44:06 by wnoth             #+#    #+#             */
/*   Updated: 2017/12/20 11:34:09 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <fcntl.h>

typedef struct	s_map
{
	int				w;
	int				h;
	int				fd;
	char			*line;
	char			**splited;
	char			linenb;
	int				hited_obj_x;
	int				hited_obj_y;
	int				coin;
	char			*coinc;
	int				*data;
	int				*initial_map;
	int				*reset_map;
}				t_map;

void			map_init(t_map *map, char *filename);
int				map_get(t_map *map, int x, int y);
int				map_color(int side);
void			ft_open(t_map *map, char *filename);
void			ft_get_size(t_map *map);
void			ft_get_tex(t_map *map);
void			ft_set_map(t_map *map);

#endif
