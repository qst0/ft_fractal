/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 05:52:23 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 21:57:50 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		motion_hook(int x, int y, t_view *view)
{
	if (!view->pressed->space)
	{
		view->mouse_x = x;
		view->mouse_y = y;
		view->changed = 1;
	}
	return (0);
}

int		mouse_press_hook(int button, int x, int y, t_view *v)
{
	if (button == 1)
		v->max_iter += 4;
	else if (button == 2)
		v->max_iter -= 8;
	if (button == 5)
	{
		x -= v->width / 2;
		y -= v->height / 2;
		v->zoom = (v->zoom + 1) * 1.1;
		v->x_shift += x / v->zoom / 1.5;
		v->y_shift += y / v->zoom / 1.5;
	}
	else if (button == 4)
	{
		if (v->zoom > 2)
			v->zoom = (v->zoom - 1) / 1.1;
		if (v->zoom < 4)
			v->zoom = 1;
	}
	v->changed = 1;
	return (0);
}

int		mouse_release_hook(int button, int x, int y, t_view *view)
{
	(void)view;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}
