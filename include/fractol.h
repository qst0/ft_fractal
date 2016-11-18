/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 03:27:52 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 04:29:43 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <ft_keys.h>

typedef struct	s_fractal
{
	long double x;
	long double y;
	long double re;
	long double im;
}				t_fractal;

typedef struct	s_view
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pixels;
	int			*colors;
	int			num_colors;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			max_iter;
	int			count[64];
	int			width;
	int			height;
	double		mouse_x;
	double		mouse_y;
	int			color_spin;
	int			zoom;
	double		x_shift;
	double		y_shift;
	int			changed:1;
	int			trippy:1;
	int			fuzz:1;
	char		mode;
	t_fractal	*fractal;
	t_keys		*pressed;
}				t_view;

int				key_release_hook(int keycode, t_view *view);
int				key_press_hook(int keycode, t_view *view);
int				expose_hook(t_view *view);
int				exit_hook(t_view *view);
int				loop_hook(t_view *v);

int				julia_iter_point(t_view *v);
int				julia_cubed_iter_point(t_view *v);
int				fill_carpet(t_view *view, int x, int y);
void			map_fractal(t_view *v);
void			begin_loop(void);
t_view			*create_view(void *mlx);
void			set_hooks(t_view *view);
void			init_view(t_view *v);
void			redraw(t_view *view);
void			show_fractal(t_view *v, int fractal(t_view*));

void			toggle_pressed(int keycode, t_view *view, int toggle);

void			put_pixel_to_img(t_view *view, int x, int y, int color);
void			create_view_image(t_view *view);
void			use_view_image(t_view *view);
void			hardset_color_table(t_view *view);
void			trip_color_table(t_view *view);
void			init_color_table(t_view *view, int num_of_colors);

int				motion_hook(int x, int y, t_view *v);
int				mouse_press_hook(int button, int x, int y, t_view *v);
int				mouse_release_hook(int button, int x, int y, t_view *v);

#endif
