/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:41:13 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/21 11:57:36 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include <wolf.h>
# include <ray.h>

# define TEXT_WIDTH 64
# define TEXT_HEIGHT 64

# define EMPTY 0
# define WALL 2
# define GMONNIER 3
# define WNOTH 4
# define WALL_BRICK 5
# define DIAMOND 6
# define GROUND 7
# define POMP 8
# define SECRET_PATH 9
# define SPRITES_TEXT 20
# define CHEST 21
# define MONSTER 22
# define MONSTER_B 23
# define MONSTER_D 29
# define BARREL 24
# define GAMEOVER 19

# define NB_TEXTURES 30

typedef struct	s_text
{
	void		*text_ptr;
	int			*data;
	int			w;
	int			h;
	int			bpp;
	int			sl;
	int			edn;
}				t_text;

#endif
