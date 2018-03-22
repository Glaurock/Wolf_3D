/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:44:54 by wnoth             #+#    #+#             */
/*   Updated: 2018/01/02 12:18:10 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int			is_tex(int nb, int action)
{
	int r;

	r = 0;
	if (nb == WALL)
		r = 1;
	else if (nb == WALL_BRICK)
		r = 1;
	else if (nb == GMONNIER)
		r = 1;
	else if (nb == WNOTH)
		r = 1;
	else if (nb == DIAMOND)
		r = 1;
	else if (nb == GROUND)
		r = 1;
	else if (nb == SECRET_PATH)
		r = 1;
	else if (nb == EMPTY && action)
		r = 1;
	return (r);
}

static int	is_spri(int nb)
{
	int r;

	r = 0;
	if (nb == CHEST)
		r = 1;
	else if (nb == MONSTER)
		r = 1;
	else if (nb == MONSTER_B)
		r = 1;
	else if (nb == BARREL)
		r = 1;
	return (r);
}

void		verif_number(int nb)
{
	int		tex;
	int		spri;
	t_env	*env;

	env = ft_use_env(-1, 0);
	tex = is_tex(nb, 1);
	spri = is_spri(nb);
	if (!env->count_sprite)
		env->count_sprite = 0;
	if (!tex && !spri)
		ft_exit(10);
	if (!tex && spri)
		env->count_sprite++;
}

void		verif_nb_spri(void)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	if (env->nb_sprite != env->count_sprite)
		ft_exit(11);
}

void		tmp_spri_nb(int nb)
{
	t_env *env;

	env = ft_use_env(-1, 0);
	env->nb_sprite = nb;
}
