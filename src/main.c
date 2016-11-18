/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 05:57:42 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 06:41:19 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	usage(void)
{
	write(1, "Useage: ./fract_ol #\n"
			"1: Mandelbrot\n2: Julia\n3: Julia^3\n", 55);
	exit(0);
}

int		main(int argc, char **argv)
{
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
			"~   F  R  A  C  T  A  L    F  I  N  D  E  R   ~");
	set_hooks(view);
	mlx_loop_hook(mlx, loop_hook, view);
	mlx_loop(mlx);
}
