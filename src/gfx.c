/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 06:28:00 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 21:43:20 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	redraw(t_view *view)
{
	view->changed = 0;
	if (view->mode == '1')
		view->fractal_func = mandelbrot;
	else if (view->mode == '2')
		view->fractal_func = julia_mouse;
	else
		view->fractal_func = julia_cubed_mouse;
	thread_fractal(view);
	use_view_image(view);
}

void	init_view(t_view *v)
{
	v->changed = 1;
	v->max_iter = 64;
	v->width = 1200;
	v->height = 1200;
	v->mouse_x = 0;
	v->mouse_y = 0;
	v->color_spin = 0;
	v->zoom = 1.0;
	v->x_shift = 0;
	v->y_shift = 0;
	v->trippy = 0;
	v->fuzz = 0;
}

void	set_hooks(t_view *view)
{
	mlx_do_key_autorepeatoff(view->mlx);
	mlx_hook(view->win, 2, 0, key_press_hook, view);
	mlx_hook(view->win, 3, 0, key_release_hook, view);
	mlx_hook(view->win, 4, 0, mouse_press_hook, view);
	mlx_hook(view->win, 5, 0, mouse_release_hook, view);
	mlx_hook(view->win, 6, 0, motion_hook, view);
	mlx_hook(view->win, 12, 0, expose_hook, view);
	mlx_hook(view->win, 17, 0, exit_hook, view);
}

t_view	*create_view(void *mlx)
{
	t_view	*v;

	v = (t_view*)malloc(sizeof(t_view));
	v->pressed = (t_keys*)malloc(sizeof(t_keys));
	v->fractal = (t_fractal*)malloc(sizeof(t_fractal));
	init_view(v);
	v->pressed->space = 0;
	v->pressed->w = 0;
	v->pressed->a = 0;
	v->pressed->s = 0;
	v->pressed->d = 0;
	v->pressed->i = 0;
	v->pressed->k = 0;
	v->pressed->q = 0;
	init_color_table(v, 64);
	v->mlx = mlx;
	return (v);
}
