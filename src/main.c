/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 05:57:42 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 04:32:05 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		mandelbrot(t_view *v)
{
	double x_new;
	double	x = 0;
	double	y = 0;
	int 	i;
	v->fractal->re = ((4.0 * v->fractal->x / v->width - 2.0) / v->zoom)
		+ (v->x_shift / v->width);
	v->fractal->im = ((4.0 * v->fractal->y / v->height - 2.0) / v->zoom)
		+ (v->y_shift / v->height);

	i = 0;
	while (x * x + y * y <= 4 && i < v->max_iter)
	{
		x_new = x*x - y*y + v->fractal->re;
		y = 2*x*y + v->fractal->im;
		x = x_new;
		i++;
	}
	return (i);
}

void	show_fractal(t_view *v, int fractal(t_view*))
{
	int		y = -1;
	int		x;
	int		i;

	i = 0;	
	while (i < 64)
		v->count[i++] = 0;
	while (++y < v->height)
	{
		x = -1;
		while (++x < v->width)
		{
			v->fractal->x = x;
			v->fractal->y = y;
			i = fractal(v); 
			if (i < v->max_iter)
			{
				if(v->trippy)
					v->count[i % 64]++;
				put_pixel_to_img(v, x, y, v->colors[
						((v->trippy ? v->count[i] : i  )
						   	+ v->color_spin) % 64]);
			}
		}
	}
}

int		julia(t_view *v)
{
	int	i;
	long double temp;
	long double x;
	long double y;

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
	v->fractal->re = v->mouse_x*4.0/v->width - 2;
	v->fractal->im = v->mouse_y*4.0/v->height - 2;
	return (julia(v));
}

int		julia_cubed(t_view *v)
{
	int	i;
	long double x;
	long double y;
	long double temp;

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
	v->fractal->re = v->mouse_x*4.0/v->width - 2;
	v->fractal->im = v->mouse_y*4.0/v->height - 2;
	return (julia_cubed(v));
}

void	put_fractal(t_view *v, int fractal(t_view*),
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
			v->fractal->x = pixel_x;
			v->fractal->y = pixel_y;
			v->fractal->re = (((4.0 * x / v->width - 2.0) / 2 * v->zoom)
					+ (temp_x_shift)) / 24;
			v->fractal->im = (((4.0 * y / v->height - 2.0) / 2 * v->zoom)
					+ (temp_y_shift)) / 24;
			i = fractal(v);
			v->zoom = temp_zoom;
			v->width = temp_w;
			v->height = temp_h;
			v->x_shift = temp_x_shift;
			if (i < v->max_iter)
				put_pixel_to_img(v, pixel_x + x, pixel_y + y,
					   	v->colors[(i + v->color_spin) % 64]);
		}
	}
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
			put_fractal(v, julia_cubed,
				   	j * v->width / res, i * v->height / res,
				   	v->width / res, v->height / res);
		}
	}
}

void	redraw(t_view *view)
{	
	view->changed = 0;
	//map_fractal(view);
	if (view->mode == '1')
		show_fractal(view, mandelbrot);
	else if (view->mode == '2')
		show_fractal(view, julia_mouse);	
	else
		show_fractal(view, julia_cubed_mouse);
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

#include <unistd.h>

void 	usage(void)
{
		write(1, "Useage: ./fract_ol #\n"
				"1: Mandelbrot\n2: Julia\n3: Julia^3\n", 55);
		exit(0);
}

int		main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	void	*mlx;
	t_view	*view;

	if (argc != 2)
		usage();
	mlx = mlx_init();
	view = create_view(mlx);
	if (argv[1][0] == '1' || argv[1][0] == '2' || argv[1][0] == '3')
		view->mode = argv[1][0];
	else
		usage();	
	create_view_image(view);
	view->win = mlx_new_window(mlx, view->width, view->height,
		   	"~   F  R  A  C  T  A  L    F  I  N  D  E  R   ~" );
	set_hooks(view);
	mlx_loop_hook(mlx, loop_hook, view);
	mlx_loop(mlx);
}
