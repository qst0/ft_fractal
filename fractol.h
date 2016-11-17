/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 03:27:52 by myoung            #+#    #+#             */
/*   Updated: 2016/11/17 06:16:13 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 1200

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_SEMI 41
# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_SPACE 49

typedef struct	s_keys
{
	int			space:1;
	int			semi:1;
	int			i:1;
	int			j:1;
	int			k:1;
	int			l:1;
	int			m:1;
	int			n:1;
	int			o:1;
	int			p:1;
	int			x:1;
	int			y:1;
	int			z:1;
	int			q:1;
	int			w:1;
	int			e:1;
	int			a:1;
	int			s:1;
	int			d:1;
	int			left:1;
	int			up:1;
	int			right:1;
	int			down:1;
	int			plus:1;
	int			minus:1;
}				t_keys;

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
	t_keys		*pressed;
}				t_view;

int				key_release_hook(int keycode, t_view *view);
int				key_press_hook(int keycode, t_view *view);
int				expose_hook(t_view *view);
int				exit_hook(t_view *view);
int				loop_hook(t_view *v);

int				julia_iter_point(t_view *v, int pixel_x, int pixel_y);
int				julia_cubed_iter_point(t_view *v, int pixel_x, int pixel_y);
int				fill_carpet(t_view *view, int x, int y);
void			map_fractal(t_view *v);
void			begin_loop(void);
t_view			*create_view(void *mlx);
void			set_hooks(t_view *view);
void			init_view(t_view *v);
void			redraw(t_view *view);
void			show_fractal(t_view *v, int fractal(t_view*, int, int));

void			put_pixel_to_img(t_view *view, int x, int y, int color);
void			create_view_image(t_view *view);
void			use_view_image(t_view *view);
void			init_color_table(t_view *view, int num_of_colors);

int				motion_hook(int x, int y, t_view *v);
int				mouse_press_hook(int button, int x, int y, t_view *v);
int				mouse_release_hook(int button, int x, int y, t_view *v);
void			toggle_pressed(int keycode, t_view *view, int toggle);

#endif
