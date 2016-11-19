/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 06:40:10 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 21:38:14 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		mandelbrot(t_view *v, double re, double im)
{
	double	x_new;
	double	x;
	double	y;
	int		i;

	re = ((4.0 * re / v->width - 2.0) / v->zoom)
		+ (v->x_shift / v->width);
	im = ((4.0 * im / v->height - 2.0) / v->zoom)
		+ (v->y_shift / v->height);
	x = 0;
	y = 0;
	i = 0;
	while (x * x + y * y <= 4 && i < v->max_iter)
	{
		x_new = x * x - y * y + re;
		y = 2 * x * y + im;
		x = x_new;
		i++;
	}
	return (i);
}

int		julia(t_view *v, double x, double y)
{
	int			i;
	long double	temp;

	x = ((4.0 * x / v->width - 2.0) / v->zoom) + (v->x_shift / v->width);
	y = ((4.0 * y / v->height - 2.0) / v->zoom) + (v->y_shift / v->height);
	i = 0;
	while (x * x + y * y < 4.0 && i < v->max_iter)
	{
		temp = x * x - y * y + v->fractal->re;
		y = 2 * x * y + v->fractal->im;
		x = temp;
		i++;
	}
	return (i);
}

int		julia_mouse(t_view *v, double x, double y)
{
	v->fractal->re = v->mouse_x * 4.0 / v->width - 2;
	v->fractal->im = v->mouse_y * 4.0 / v->height - 2;
	return (julia(v, x, y));
}

int		julia_cubed(t_view *v, double x, double y)
{
	int			i;
	long double	temp;

	x = ((4.0 * x / v->width - 2.0) / v->zoom)
		+ (v->x_shift / v->width);
	y = ((4.0 * y / v->height - 2.0) / v->zoom)
		+ (v->y_shift / v->height);
	i = 0;
	while (x * x + y * y < 4.0 && i < v->max_iter)
	{
		temp = x * x * x - y * y * x - (2 * x * y * y) + v->fractal->re;
		y = 2 * x * x * y - y * y * y + v->fractal->im;
		x = temp;
		i++;
	}
	return (i);
}

int		julia_cubed_mouse(t_view *v, double x, double y)
{
	v->fractal->re = v->mouse_x * 4.0 / v->width - 2;
	v->fractal->im = v->mouse_y * 4.0 / v->height - 2;
	return (julia_cubed(v, x, y));
}
