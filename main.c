#include <fractol.h>

/* real to screen */
#define FX(x) ((int) ((x + 2)/4.0 * width))
#define FY(y) ((int) ((2 - y)/4.0 * height))

/*screen to real*/
#define GX(i) ((i)*4.0/width - 2)
#define GY(j) ((j)*4.0/height - 2)

long colors[] = {
	0x0048EF, 0x0057F0, 0x0166f0, 0x0274F0,
	0x0383F0, 0x0491F0, 0x05A0F1, 0x06AEF1,
	0x07BCF1, 0x08CAF1, 0x08D8f1, 0x09E6F2,
	0x0AF2F0, 0x0BF2E3, 0x0CF2D5, 0x0DF2C8,
	0x0EF3BB, 0x0FF3AE, 0x10F3A1, 0x11F394,
	0x12F388, 0x13F47B, 0x13F46E, 0x14F462,
	0x15F455, 0x16F449, 0x17F43D, 0x18F531,
	0x19F525, 0x1BF51A, 0x29F51B, 0x37F51C,
	0x44F61D, 0x52F61E, 0x5FF61F, 0x6CF620,
	0x79F621, 0x87F721, 0x94F722, 0xA1F723,
	0xADF724, 0xBAF725, 0xC7F826, 0xD4F827,
	0xE0F828, 0xECF829, 0xF8F82A, 0xF8EC2B,
	0xF9E02C, 0xF9D42D, 0xF9C92E, 0xF9BD2F,
	0xF9B230, 0xfAA731, 0xFA9B32, 0xFA9033,
	0xFA8534, 0xFA7A35, 0xFB6F36, 0xFB6537,
	0xFB5A38, 0xFB4F39, 0xFB453A, 0xFC3A3A
};

/*
** TODO:
** UPDATE THE COLORS
** NORM THE PROJECT
** GET TRIPPY / TURN IT IN
**
*/

int		changed = 1;
int		max_iter = 64;
int		count[64];
int		width = 600;
int		height = 600;
double	mouse_x = 0;
double	mouse_y = 0;
int		color_spin = 0;
double	zoom = 1.0;
double	x_shift = 0;
double	y_shift = 0;

void	put_pixel_to_img(t_view *view, int x, int y, int color)
{
	int i;

	if (x > 0 && y > 0 && x < width && y < height)
	{
		i = (x * (view->bits_per_pixel / 8)) + (y * view->size_line);
		view->pixels[i] = color;
		view->pixels[++i] = color >> 8;
		view->pixels[++i] = color >> 16;
	}
}

void	create_view_image(t_view *view)
{
	view->img = mlx_new_image(view->mlx, width, height);
	view->pixels = mlx_get_data_addr(view->img, &(view->bits_per_pixel),
			&(view->size_line), &(view->endian));
}

void	use_view_image(t_view *view)
{
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	mlx_destroy_image(view->mlx, view->img);
	create_view_image(view);
}

void	init_color_table(t_view *view, int num_of_colors)
{
	int				i;
	float			f;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	view->colors = (int*)malloc(sizeof(int) * num_of_colors);
	f = 0;
	i = -1;
	while (++i < num_of_colors)
	{
		r = (cos(f) + 1) * 127;
		g = (sin(f) + 1) * 127;
		b = (-cos(f) + 1) * 127;
		view->colors[i] = b << 16 | g << 8 | r;
		f += M_PI / num_of_colors;
	}
	view->num_colors = num_of_colors;
}

int		draw_mandelbrot(t_view *view, int pixel_x, int pixel_y)
{
	(void) view;
	double x_new;
	double re = ((4.0 * pixel_x / width - 2.0) / zoom) + (x_shift / width);
	double im = ((4.0 * pixel_y / height - 2.0) / zoom) + (y_shift / height);
	double	x = 0;
	double	y = 0;
	int 	i;

	i = 0;
	while (x * x + y * y <= 4 && i < max_iter)
	{
		x_new = x*x - y*y + re;
		y = 2*x*y + im;
		x = x_new;
		i++;
	}
	return (i);
}

void	put_fractal(t_view *view, int fractal(t_view*, long double, long double, long double, long double),
	   	double x, double y, int w, int h)
{
	int		pixel_y = -1;
	int		pixel_x;
	int		temp_w;
	int		temp_h;
	int		i;
	temp_w = width;
	temp_h = height;
	width = w;
	height = h;
	while (++pixel_y < h)
	{
		pixel_x = -1;
		while (++pixel_x < w)
		{
			i = fractal(view, pixel_x, pixel_y,
							(((4.0 * x / width - 2.0) / zoom) + (x_shift)) / 48,
							(((4.0 * y / height - 2.0) / zoom) + (y_shift)) / 48);
			if (i < max_iter)
			{
				mlx_pixel_put(view->mlx, view->win, x + pixel_x, y + pixel_y,
						colors[(i + color_spin) % 64]);
				//put_pixel_to_img(view, x, y, colors[(i + color_spin) % 64]);
			}
			else
			{
				mlx_pixel_put(view->mlx, view->win, x + pixel_x, y + pixel_y, 0x0);
			}
		}
	}
	width = temp_w;
	height = temp_h;
}

void	show_fractal(t_view *view, int fractal(t_view*, int, int))
{
	int		pixel_y = -1;
	int		pixel_x;
	int		iter_count;

	while (++pixel_y < height)
	{
		pixel_x = -1;
		while (++pixel_x < width)
		{
			iter_count = fractal(view, pixel_x, pixel_y); 
			if (iter_count < max_iter)
			{
				mlx_pixel_put(view->mlx, view->win, pixel_x, pixel_y,
						colors[(iter_count + color_spin) % 64]);
				put_pixel_to_img(view, pixel_x, pixel_y, colors[(iter_count + color_spin) % 64]);
			}
			else
			{
				put_pixel_to_img(view, pixel_x, pixel_y, 0x000000);
				//mlx_pixel_put(view->mlx, view->win, pixel_x, pixel_y, 0x0);
			}
		}
	}
}

int		julia_iter_point_c(t_view *view, long double x, long double y,
			long double re, long double im)
{
	(void) view;
	int	i;
	long double temp;

	x = ((4.0 * x / width - 2.0) / zoom) + (x_shift / width);
	y = ((4.0 * y / height - 2.0) / zoom) + (y_shift / height);
	i = 0;
	while (x * x + y * y < 4.0 && i < max_iter)
	{
		temp = x * x - y * y + re;
		y = 2 * x * y + im;
		x = temp;
		i++;
	}
	return (i);
}

int		julia_iter_point(t_view *view, int pixel_x, int pixel_y)
{
	return (julia_iter_point_c(view, pixel_x, pixel_y, GX(mouse_x), GY(mouse_y)));
}

int		julia_cubed_iter_point(t_view *view, int pixel_x, int pixel_y)
{
	(void) view;
	int	i;
	long double re;
	long double im;
	long double x;
	long double y;
	long double temp;

	re = GX(mouse_x);
	im = GY(mouse_y);
	x = ((4.0 * pixel_x / width - 2.0) / zoom) + (x_shift / width);
	y = ((4.0 * pixel_y / height - 2.0) / zoom) + (y_shift / height);
	i = 0;
	while (x * x + y * y < 4.0 && i < max_iter)
	{
		temp = x * x * x - y * y * x - (2 * x * y * y) + re;
		y = 2 * x * x * y - y * y * y + im;
		x = temp;
		i++;
	}
	return (i);
}

int		is_filled(int x, int y)
{
	while (x > 0 || y > 0)
	{
		if (x % 3 == 1 && y % 3 == 1)
			return (0);
		x /= 3;
		y /= 3;
	}
	return (1);
}

void	fill_carpet(t_view *view, int x, int y)
{
	if (is_filled(x, y))
		mlx_pixel_put(view->mlx, view->win, x, y, 0xFF00FF);
	else
		mlx_pixel_put(view->mlx, view->win, x, y, 0xAAAAFF);
}

int		key_release_hook(int keycode, t_view *view)
{
	(void) keycode;
	(void) view;
	//toggle_pressed(keycode, view, 0);
	return (0);
}

int		key_press_hook(int keycode, t_view *view)
{
	(void) view;
	if (keycode == 53)
		exit(0);
	//toggle_pressed(keycode, view, 1);

	if (keycode == KEY_A)
		x_shift += 10;
	else if (keycode == KEY_D)
		x_shift -= 10;

	if (keycode == KEY_W)
		y_shift += 10;
	else if(keycode == KEY_S)
		y_shift -= 10;

	if (keycode == KEY_I)
		zoom = zoom + 1;
	else if (keycode == KEY_K && zoom > 1)
		zoom = zoom - 1;
	else if (keycode == KEY_F)
		color_spin++;
	changed = 1;
	return (0);
}

void	map_fractal(t_view *view)
{
	int i;
	int j;
	int res;
	
	res = 40;
	i = -1;
	while(++i < res)
	{
	j = -1;
		while(++j < res)
		{
			put_fractal(view, julia_iter_point_c, j * width / res, i * height / res,
				   	width / res, height / res);
		}
	}
}

void	redraw(t_view *view)
{	
	changed = 0;
//	mlx_clear_window(view->mlx, view->win);
//	map_fractal(view);
//	show_fractal(view, fill_carpet);
	show_fractal(view, draw_mandelbrot);
//	show_fractal(view, julia_iter_point);
//	show_fractal(view, draw_dopeness);
	use_view_image(view);
}

int		expose_hook(t_view *view)
{
	if(changed)
		redraw(view);
	return (0);
}

int		exit_hook(t_view *view)
{
	mlx_destroy_window(view->mlx, view->win);
	exit(0);
	return (0);
}

int		motion_hook(int x, int y, t_view *view)
{
	(void) view;
	mouse_x = x;
	mouse_y = y;
	changed = 1;
	return (0);
}

int		mouse_press_hook(int button, int x, int y, t_view *view)
{
	(void) button;
	(void) view;
	if (button == 5)
	{
		x -= width / 2;
		y -= height / 2;
		zoom++;
		x_shift += x / zoom / 1.5;
		y_shift += y / zoom / 1.5;
	}
	else if (button == 4)
	{
		if(zoom > 1)
			zoom--;
	}
	//mouse_x = x;
	//mouse_y = y;
	changed = 1;
	return (0);
}

int		mouse_release_hook(int button, int x, int y, t_view *view)
{
	(void) view;
	(void) button;
	(void) x;
	(void) y;
	return (0);
}

void	set_hooks(t_view *view)
{
	mlx_hook(view->win, 2, 0, key_press_hook, view);
	mlx_hook(view->win, 3, 0, key_release_hook, view);
	mlx_hook(view->win, 4, 0, mouse_press_hook, view);
	mlx_hook(view->win, 5, 0, mouse_release_hook, view);
	mlx_hook(view->win, 6, 0, motion_hook, view);
	mlx_hook(view->win, 12, 0, expose_hook, view);
	mlx_hook(view->win, 17, 0, exit_hook, view);
}

int		loop_hook(t_view *view)
{
	if(changed)
		redraw(view);
	return (0);
}

t_view	*create_view(void *mlx)
{
	t_view	*view;

	view = (t_view*)malloc(sizeof(t_view));
	view->mlx = mlx;
	return (view);
}

void	begin_loop(void)
{
	void	*mlx;
	t_view	*view;

	mlx = mlx_init();
	view = create_view(mlx);
	create_view_image(view);
	view->win = mlx_new_window(mlx, width, height, "FRACT_OL");
	set_hooks(view);
	mlx_loop_hook(mlx, loop_hook, view);
	mlx_loop(mlx);
}

int		main(void)
{
	begin_loop();
}
