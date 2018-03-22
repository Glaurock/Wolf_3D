/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:38:41 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 12:25:24 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <mlx.h>
# include <libft.h>
# include <time.h>
# include "inputs.h"
# include "camera.h"
# include "ray.h"
# include "textures.h"
# include "sprites.h"
# include "update.h"
# include "error.h"
# include "/System/Library/Frameworks/Tk.framework/Versions/8.4/Headers/X11/X.h"

# define ENVTEX env->textures
# define MLX env->mlx_ptr
# define WIN env->win_ptr

# define WIDTH 640
# define HEIGHT 480
# define FPS 60

typedef struct	s_env
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	int			bpp;
	int			sl;
	int			edn;
	void		*img;
	char		*tmp;
	int			roof;
	int			floor;
	t_inputs	inputs;
	t_cam		cam;
	t_ray		ray;
	t_map		map;
	t_text		textures[NB_TEXTURES];
	t_timer		timer;
	int			nb_sprite;
	int			count_sprite;
	t_sprite	*sprites;
	double		z_buffer[WIDTH];
	int			*sprites_order;
	double		*sprites_distance;
	int			is_alive;
}				t_env;

t_env			*ft_use_env(int action, char *filename);
void			input_action(t_env *env);
int				expose_hook(void *param);
void			img_put_px(t_env *env, int color, int x, int y);
void			ray_display(t_env *env, t_ray *ray, int pos, int height);
void			ft_exit(int error);

void			update_game(t_env *env);
void			move_sprite(t_map *map, t_sprite *sprite);
void			dying_animation(t_env *env, t_sprite *sprite);
void			destroy_text(t_env *env, t_text *textures);

/*
** Functions de draw
*/

void			draw_all(t_env *env);
void			vertical_draw(t_env *env, int x);

/*
** fonctions de textures
*/

void			get_tex_x(t_ray *ray);
void			get_tex_y(t_ray *ray, int y, int height, int line_height);
void			load_text(t_env *env, t_text *textures);
int				get_pixel_from_texture(t_env *env, t_ray *ray);
void			destroy_text(t_env *env, t_text *textures);

/*
** floor_casting
*/

void			floor_casting(t_env *env, t_ray *ray, int pos);

/*
** sprites
*/

void			sprite_casting(t_env *env, t_cam *cam);
void			init_sprites(t_sprite **sprites, int nb);
void			check_kills(t_env *env);
void			del_sprite(t_map *map, int pos);
void			collide_player_sprite(t_env *env, int i);

/*
** update
*/

void			update_game(t_env *env);
void			timer_init(t_timer *timer);
void			get_next_time(t_timer *timer);

void			reset(t_env *env);
void			free_splited(char **splited);
void			verif_number(int nb);
void			verif_nb_spri();
void			tmp_spri_nb(int nb);
void			ft_reset_input(void);
void			ft_pause(void);
void			ft_show_commands(void);

#endif
