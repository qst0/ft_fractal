/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 22:11:46 by myoung            #+#    #+#             */
/*   Updated: 2016/11/17 22:13:39 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

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

void	trip_color_table(t_view *view)
{
	if (view->colors)
		free(view->colors);
	view->colors = (int*)malloc(sizeof(int) * 64);
}

void	hardset_color_table(t_view *view)
{
	view->colors = (int*)malloc(sizeof(int) * 64);
	int i;
	int colors[] = {
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

	i = -1;
	while (++i < 64)
		view->colors[i] = colors[i];
}


