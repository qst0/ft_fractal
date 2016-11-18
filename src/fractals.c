/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 06:40:10 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 06:41:48 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		mandelbrot(t_view *v)
{
	double	x_new;
	double	x;
	double	y;
	int		i;

	v->fractal->re = ((4.0 * v->fractal->x / v->width - 2.0) / v->zoom)
		+ (v->x_shift / v->width);
	v->fractal->im = ((4.0 * v->fractal->y / v->height - 2.0) / v->zoom)
		+ (v->y_shift / v->height);
	x = 0;
	y = 0;
	i = 0;
	while (x * x + y * y <= 4 && i < v->max_iter)
	{
		x_new = x * x - y * y + v->fractal->re;
		y = 2 * x * y + v->fractal->im;
		x = x_new;
		i++;
	}
	return (i);
}

int		julia(t_view *v)
{
	int			i;
	long double	temp;
	long double	x;
	long double	y;

	x = v->fractal->x;
	y = v->fractal->y;
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

int		julia_mouse(t_view *v)
{
	v->fractal->re = v->mouse_x * 4.0 / v->width - 2;
	v->fractal->im = v->mouse_y * 4.0 / v->height - 2;
	return (julia(v));
}

int		julia_cubed(t_view *v)
{
	int			i;
	long double	x;
	long double	y;
	long double	temp;

	x = v->fractal->x;
	y = v->fractal->y;
	x = ((4.0 * v->fractal->x / v->width - 2.0) / v->zoom)
		+ (v->x_shift / v->width);
	y = ((4.0 * v->fractal->y / v->height - 2.0) / v->zoom)
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

int		julia_cubed_mouse(t_view *v)
{
	v->fractal->re = v->mouse_x * 4.0 / v->width - 2;
	v->fractal->im = v->mouse_y * 4.0 / v->height - 2;
	return (julia_cubed(v));
}
