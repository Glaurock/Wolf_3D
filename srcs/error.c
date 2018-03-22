/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:41:25 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 11:20:05 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>

void	ft_exit_line(int error, int linenb)
{
	ft_use_env(0, 0);
	if (error == 1)
		ft_putstr("😡 Error : No maps data. line ");
	else if (error == 2)
		ft_putstr("😡 Error : Invalid MAP_SIZE / NB_SPRITES in map file. line ");
	else if (error == 3)
		ft_putstr("😡 Error : Invalid GND or SKY texture value. line ");
	else if (error == 4)
		ft_putstr("😡 Error : Invalid number of value in map. line ");
	else if (error == 5)
		ft_putstr("😡 Error : Invalid number. line ");
	else if (error == 6)
		ft_putstr("😡 Error : Invalid number of line. line ");
	else if (error == 7)
		ft_putstr("😡 Error : Invalid border number. line ");
	ft_putnbr(linenb);
	ft_putchar('\n');
	exit(-1);
}

void	checkforletter(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (map->splited[i])
	{
		j = 0;
		while (map->splited[i][j])
		{
			if (map->splited[i][j] < '0' || map->splited[i][j] > '9')
			{
				ft_exit_line(5, map->linenb);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_for_error(t_map *map)
{
	int count;

	count = 0;
	map->linenb = 0;
	if ((get_next_line(map->fd, &(map->line))) <= 0)
		ft_exit(4);
	ft_memdel((void **)&map->line);
	map->linenb++;
	while (get_next_line(map->fd, &(map->line)) && count < 1)
	{
		map->linenb++;
		map->splited = ft_strsplit(map->line, ' ');
		line_size(map->splited, 0);
		checkforletter(map);
		map->w = ft_atoi(map->splited[0]);
		map->h = ft_atoi(map->splited[1]);
		tmp_spri_nb(ft_atoi(map->splited[2]));
		free_splited(map->splited);
		ft_memdel((void **)&map->line);
		count++;
	}
	ft_memdel((void **)&map->line);
	ft_continue_error(map);
}

void	ft_continue_error(t_map *map)
{
	if ((get_next_line(map->fd, &(map->line))) <= 0)
		ft_exit_line(1, map->linenb);
	map->linenb += 2;
	map->splited = ft_strsplit(map->line, ' ');
	line_size(map->splited, 1);
	checkforletter(map);
	if (!is_tex(ft_atoi(map->splited[0]), 0) ||
		!is_tex(ft_atoi(map->splited[1]), 0))
		ft_exit_line(3, map->linenb);
	ft_memdel((void **)&map->line);
	free_splited(map->splited);
	map->linenb++;
	if ((get_next_line(map->fd, &(map->line))) <= 0)
		ft_exit_line(1, map->linenb);
	ft_memdel((void **)&map->line);
	ft_check_for_map_size(map);
}

void	ft_check_for_map_size(t_map *map)
{
	int	count;
	int i;

	i = -1;
	count = 0;
	while (get_next_line(map->fd, &(map->line)) > 0 && count++ < map->h)
	{
		if (count == 0)
		{
			map->splited = ft_strsplit(map->line, ' ');
			while (map->splited[++i])
			{
				if (ft_atoi(MAPS[i]) < 2 || ft_atoi(map->splited[i]) >= 20)
					ft_exit_line(7, map->linenb + 1);
			}
			free_splited(map->splited);
		}
		check_x(map);
		ft_memdel((void **)&map->line);
	}
	verif_nb_spri();
	if (count != map->h)
		ft_exit_line(6, map->linenb);
	if (count == 0)
		ft_exit_line(1, map->linenb);
}
