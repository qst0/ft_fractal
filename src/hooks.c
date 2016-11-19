/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 06:07:28 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 21:59:07 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		key_release_hook(int keycode, t_view *view)
{
	toggle_pressed(keycode, view, 0);
	view->changed = 1;
	return (0);
}

int		key_press_hook(int keycode, t_view *view)
{
	if (keycode == KEY_Z)
		trip_color_table(view);
	if (keycode == KEY_X)
		hardset_color_table(view);
	if (keycode == KEY_SPACE)
		view->pressed->space = !view->pressed->space;
	if (keycode == KEY_E)
		view->trippy = !view->trippy;
	if (keycode == 53)
		exit(0);
	toggle_pressed(keycode, view, 1);
	view->changed = 1;
	return (0);
}

int		expose_hook(t_view *view)
{
	if (view->changed)
		redraw(view);
	return (0);
}

int		exit_hook(t_view *view)
{
	mlx_destroy_window(view->mlx, view->win);
	exit(0);
	return (0);
}

int		loop_hook(t_view *v)
{
	if (v->pressed->a || v->pressed->s || v->pressed->w ||
		v->pressed->d || v->pressed->i || v->pressed->k || v->pressed->q)
		v->changed = 1;
	if (v->pressed->a)
		v->x_shift += 10;
	else if (v->pressed->d)
		v->x_shift -= 10;
	if (v->pressed->w)
		v->y_shift += 10;
	else if (v->pressed->s)
		v->y_shift -= 10;
	if (v->pressed->i)
		v->zoom = (v->zoom + 1) * 1.1;
	else if (v->pressed->k && v->zoom > 1)
		v->zoom = (v->zoom - 1) * 1.1;
	else if (v->pressed->q)
		v->color_spin++;
	if (v->changed)
		redraw(v);
	return (0);
}
