/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 05:57:42 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 00:28:53 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

/*screen to real*/
#define GX(i) ((i)*4.0/v->width - 2)
#define GY(j) ((j)*4.0/v->height - 2)

int		draw_mandelbrot(t_view *v, int pixel_x, int pixel_y)
{
	double x_new;
	double re = ((4.0 * pixel_x / v->width - 2.0) / v->zoom) + (v->x_shift / v->width);
	double im = ((4.0 * pixel_y / v->height - 2.0) / v->zoom) + (v->y_shift / v->height);
	double	x = 0;
	double	y = 0;
	int 	i;

	i = 0;
	while (x * x + y * y <= 4 && i < v->max_iter)
	{
		x_new = x*x - y*y + re;
		y = 2*x*y + im;
		x = x_new;
		i++;
	}
	return (i);
}

void	put_fractal(t_view *v, int fractal(t_view*, long double, long double, long double, long double),
	   	double x, double y, int w, int h)
{
	int		pixel_y = -1;
	int		pixel_x;
	int		i;
	int		temp_w;
	int		temp_h;
	int		temp_zoom;
	int		temp_x_shift;
	int		temp_y_shift;
	temp_zoom = v->zoom;
	temp_w = v->width;
	temp_h = v->height;
	temp_x_shift = v->x_shift;
	temp_y_shift = v->y_shift;
	while (++pixel_y < h)
	{
		pixel_x = -1;
		while (++pixel_x < w)
		{
			v->width = w;
			v->height = h;
			v->x_shift = 0;
			v->zoom = 1;
			i = fractal(v, pixel_x, pixel_y,
							(((4.0 * x / v->width - 2.0) / 2 * v->zoom) + (temp_x_shift)) / 24,
							(((4.0 * y / v->height - 2.0) / 2 * v->zoom) + (temp_y_shift)) / 24);
			v->zoom = temp_zoom;
			v->width = temp_w;
			v->height = temp_h;
			v->x_shift = temp_x_shift;
			if (i < v->max_iter)
				put_pixel_to_img(v, pixel_x + x, pixel_y + y, v->colors[(i + v->color_spin) % 64]);
		}
	}
}

void	show_fractal(t_view *v, int fractal(t_view*, int, int))
{
	int		pixel_y = -1;
	int		pixel_x;
	int		i;

	i = 0;	
	while (i < 64)
		v->count[i++] = 0;

	while (++pixel_y < v->height)
	{
		pixel_x = -1;
		while (++pixel_x < v->width)
		{
			i = fractal(v, pixel_x, pixel_y); 
			if (i < v->max_iter)
			{
				if(v->trippy)
					v->count[i]++;
				put_pixel_to_img(v, pixel_x, pixel_y, v->colors[
						((v->trippy ? v->count[i] : i  )
						   	+ v->color_spin) % 64]);
			}
		}
	}
}

int		julia_iter_point_c(t_view *v, long double x, long double y,
			long double re, long double im)
{
	int	i;
	long double temp;

	x = ((4.0 * x / v->width - 2.0) / v->zoom) + (v->x_shift / v->width);
	y = ((4.0 * y / v->height - 2.0) / v->zoom) + (v->y_shift / v->height);
	i = 0;
	while (x * x + y * y < 4.0 && i < v->max_iter)
	{
		temp = x * x - y * y + re;
		y = 2 * x * y + im;
		x = temp;
		i++;
	}
	return (i);
}

int		julia_iter_point(t_view *v, int pixel_x, int pixel_y)
{
	return (julia_iter_point_c(v, pixel_x, pixel_y, GX(v->mouse_x), GY(v->mouse_y)));
}

int		julia_cubed_iter_point(t_view *v, int pixel_x, int pixel_y)
{
	int	i;
	long double re;
	long double im;
	long double x;
	long double y;
	long double temp;

	re = GX(v->mouse_x);
	im = GY(v->mouse_y);
	x = ((4.0 * pixel_x / v->width - 2.0) / v->zoom) + (v->x_shift / v->width);
	y = ((4.0 * pixel_y / v->height - 2.0) / v->zoom) + (v->y_shift / v->height);
	i = 0;
	while (x * x + y * y < 4.0 && i < v->max_iter)
	{
		temp = x * x * x - y * y * x - (2 * x * y * y) + re;
		y = 2 * x * x * y - y * y * y + im;
		x = temp;
		i++;
	}
	return (i);
}

void	map_fractal(t_view *v)
{
	int i;
	int j;
	int res;
	
	res = 20 / v->zoom;
	i = -1;
	while(++i < res)
	{
	j = -1;
		while(++j < res)
		{
			put_fractal(v, julia_iter_point_c, j * v->width / res, i * v->height / res,
				   	v->width / res, v->height / res);
		}
	}
}

void	redraw(t_view *view)
{	
	view->changed = 0;
//	map_fractal(view);
//	show_fractal(view, julia_cubed_iter_point);
//	show_fractal(view, draw_mandelbrot);
	show_fractal(view, julia_iter_point);	
	use_view_image(view);
}

#define KEY(key) v->pressed->key

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
	KEY(space) = 0;
	KEY(w) = 0;
	KEY(a) = 0;
	KEY(s) = 0;
	KEY(d) = 0;
	KEY(i) = 0;
	KEY(k) = 0;
	KEY(q) = 0;
	init_color_table(v, 64);
	v->mlx = mlx;
	return (v);
}

int		main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	void	*mlx;
	t_view	*view;

	mlx = mlx_init();
	view = create_view(mlx);
	create_view_image(view);
	view->win = mlx_new_window(mlx, view->width, view->height,
		   	"~   F  R  A  C  T  A  L    F  I  N  D  E  R   ~" );
	set_hooks(view);
	mlx_loop_hook(mlx, loop_hook, view);
	mlx_loop(mlx);
}
