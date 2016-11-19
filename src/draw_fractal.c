/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 06:42:00 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 21:54:31 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void		fractal_thread(void *passed_thread)
{
	int			y;
	int			x;
	int			i;
	t_view		*v;
	t_thread	*thread;

	thread = (t_thread*)passed_thread;
	v = thread->view;
	i = 0;
	y = (v->height / thread->count * (thread->num - 1)) - 1;
	while (++y < v->height / thread->count * thread->num)
	{
		x = -1;
		while (++x < v->width)
		{
			i = v->fractal_func(v, x, y);
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

pthread_t	make_thread(t_view *v, int thread_index, int thread_count)
{
	pthread_t	pth;
	t_thread	*thread;

	thread = (t_thread*)malloc(sizeof(t_thread));
	thread->count = thread_count;
	thread->num = thread_index;
	thread->view = v;
	pthread_create(&pth, NULL, (void*)fractal_thread, thread);
	return (pth);
}

void		thread_fractal(t_view *v)
{
	int			i;
	int			num_of_threads;
	pthread_t	threads[THREAD_COUNT];

	num_of_threads = THREAD_COUNT;
	i = 1;
	while (i < num_of_threads + 1)
	{
		threads[i - 1] = make_thread(v, i, num_of_threads);
		i++;
	}
	i = 0;
	while (i < num_of_threads)
		pthread_join(threads[i++], NULL);
}

void		show_fractal(t_view *v)
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
			i = v->fractal_func(v, x, y);
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
