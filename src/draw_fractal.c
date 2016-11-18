/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 06:42:00 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 06:44:49 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	show_fractal(t_view *v, int fractal(t_view*))
{
	int		y;
	int		x;
	int		i;

	i = 0;
	y = -1;
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
				if (v->trippy)
					v->count[i % 64]++;
				put_pixel_to_img(v, x, y, v->colors[
						((v->trippy ? v->count[i] : i) + v->color_spin) % 64]);
			}
		}
	}
}
