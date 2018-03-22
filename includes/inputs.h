/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:26:12 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 08:36:07 by wnoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# define FORWARD 13
# define BACKWARD 1
# define LEFT 0
# define RIGHT 2
# define STRAFL 12
# define STRAFR 14
# define PAUSE 35

# define FOVUP 69
# define FOVDOWN 78

# define FIRE 49
# define ENTER 36

typedef struct	s_inputs
{
	int			left;
	int			right;
	int			up;
	int			down;
	int			sleft;
	int			sright;
	int			fire;
	int			can_fire;
}				t_inputs;

int				key_hook_press(int keycode);
int				key_hook_release(int keycode, void *param);
int				exit_hook(void *param);

#endif
