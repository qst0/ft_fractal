/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 06:05:54 by myoung            #+#    #+#             */
/*   Updated: 2016/11/17 06:06:29 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	put_pixel_to_img(t_view *view, int x, int y, int color)
{
	int i;

	if (x > 0 && y > 0 && x < view->width && y < view->height)
	{
		i = (x * (view->bits_per_pixel / 8)) + (y * view->size_line);
		view->pixels[i] = color;
		view->pixels[++i] = color >> 8;
		view->pixels[++i] = color >> 16;
	}
}

void	create_view_image(t_view *view)
{
	view->img = mlx_new_image(view->mlx, view->width, view->height);
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
