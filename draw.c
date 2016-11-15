
/* leftovers not being used */

void	sierpinski(t_view *view)
{
	draw_square(0, 0, width, 0xFF0000, view);
	draw_gasket(0, 0, width, view);
	(void) view;
}

void	draw_square(int x, int y, int size, int color, t_view *view)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(view->mlx, view->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_gasket(int x, int y, int size, t_view *view)
{
	int		sub = size / 3;
	draw_square(x + sub, y + sub, sub - 1, 0x000000, view);

	if (sub >= 3)
	{
		draw_gasket(x, y, sub, view);
		draw_gasket(x + sub, y, sub, view);
		draw_gasket(x + 2 * sub, y, sub, view);
		draw_gasket(x, y + sub, sub, view);
		draw_gasket(x + 2 * sub, y + sub, sub, view);
		draw_gasket(x, y + 2 * sub, sub, view);
		draw_gasket(x + sub, y + 2 * sub, sub, view);
		draw_gasket(x + 2 * sub, y + 2 * sub , sub, view);

	}
}


