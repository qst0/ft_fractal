/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 01:48:07 by myoung            #+#    #+#             */
/*   Updated: 2016/11/16 01:49:05 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	test_hooks(t_view *view)
{
	mlx_hook(view->win, 1, 0, magic_hook1, view);
	mlx_hook(view->win, 7, 0, magic_hook7, view);
	mlx_hook(view->win, 8, 0, magic_hook8, view);
	mlx_hook(view->win, 9, 0, magic_hook9, view);
	mlx_hook(view->win, 10, 0, magic_hook10, view);
	mlx_hook(view->win, 11, 0, magic_hook11, view);
	mlx_hook(view->win, 13, 0, magic_hook13, view);
	mlx_hook(view->win, 14, 0, magic_hook24, view);
	mlx_hook(view->win, 15, 0, magic_hook15, view);
	mlx_hook(view->win, 16, 0, magic_hook16, view);
	mlx_hook(view->win, 18, 0, magic_hook18, view);
	mlx_hook(view->win, 19, 0, magic_hook19, view);
	mlx_hook(view->win, 20, 0, magic_hook20, view);
	mlx_hook(view->win, 21, 0, magic_hook21, view);
	mlx_hook(view->win, 22, 0, magic_hook22, view);
	mlx_hook(view->win, 23, 0, magic_hook23, view);
	mlx_hook(view->win, 24, 0, magic_hook24, view);
	mlx_hook(view->win, 25, 0, magic_hook25, view);
	mlx_hook(view->win, 26, 0, magic_hook26, view);
	mlx_hook(view->win, 27, 0, magic_hook27, view);
	mlx_hook(view->win, 28, 0, magic_hook28, view);
	mlx_hook(view->win, 29, 0, magic_hook29, view);
	mlx_hook(view->win, 30, 0, magic_hook30, view);
	mlx_hook(view->win, 31, 0, magic_hook31, view);
	mlx_hook(view->win, 32, 0, magic_hook32, view);
	mlx_hook(view->win, 33, 0, magic_hook33, view);
	mlx_hook(view->win, 34, 0, magic_hook34, view);
	mlx_hook(view->win, 35, 0, magic_hook35, view);
}
int		magic_hook1(t_view *view)
{
	(void) view;
	printf("MAGIC 1!\n");
	return (0);
}

int		magic_hook7(t_view *view)
{
	(void) view;
	printf("MAGIC 7!\n");
	return (0);
}

int		magic_hook8(t_view *view)
{
	(void) view;
	printf("MAGIC 8!\n");
	return (0);
}

int		magic_hook9(t_view *view)
{
	(void) view;
	printf("MAGIC 9!\n");
	return (0);
}

int		magic_hook10(t_view *view)
{
	(void) view;
	printf("MAGIC 10!\n");
	return (0);
}

int		magic_hook11(t_view *view)
{
	(void) view;
	printf("MAGIC 11!\n");
	return (0);
}

int		magic_hook13(t_view *view)
{
	(void) view;
	printf("MAGIC 13!\n");
	return (0);
}

int		magic_hook14(t_view *view)
{
	(void) view;
	printf("MAGIC 14!\n");
	return (0);
}

int		magic_hook15(t_view *view)
{
	(void) view;
	printf("MAGIC 15!\n");
	return (0);
}

int		magic_hook16(t_view *view)
{
	(void) view;
	printf("MAGIC 16!\n");
	return (0);
}

int		magic_hook18(t_view *view)
{
	(void) view;
	printf("MAGIC 18!\n");
	return (0);
}

int		magic_hook19(t_view *view)
{
	(void) view;
	printf("MAGIC 19!\n");
	return (0);
}

int		magic_hook20(t_view *view)
{
	(void) view;
	printf("MAGIC 20!\n");
	return (0);
}

int		magic_hook21(t_view *view)
{
	(void) view;
	printf("MAGIC 21!\n");
	return (0);
}

int		magic_hook22(t_view *view)
{
	(void) view;
	printf("MAGIC 22!\n");
	return (0);
}

int		magic_hook23(t_view *view)
{
	(void) view;
	printf("MAGIC 23!\n");
	return (0);
}

int		magic_hook24(t_view *view)
{
	(void) view;
	printf("MAGIC 24!\n");
	return (0);
}

int		magic_hook25(t_view *view)
{
	(void) view;
	printf("MAGIC 25!\n");
	return (0);
}

int		magic_hook26(t_view *view)
{
	(void) view;
	printf("MAGIC 26!\n");
	return (0);
}

int		magic_hook27(t_view *view)
{
	(void) view;
	printf("MAGIC 27!\n");
	return (0);
}

int		magic_hook28(t_view *view)
{
	(void) view;
	printf("MAGIC 28!\n");
	return (0);
}

int		magic_hook29(t_view *view)
{
	(void) view;
	printf("MAGIC 29!\n");
	return (0);
}

int		magic_hook30(t_view *view)
{
	(void) view;
	printf("MAGIC 30!\n");
	return (0);
}

int		magic_hook31(t_view *view)
{
	(void) view;
	printf("MAGIC 31!\n");
	return (0);
}

int		magic_hook32(t_view *view)
{
	(void) view;
	printf("MAGIC 32!\n");
	return (0);
}

int		magic_hook33(t_view *view)
{
	(void) view;
	printf("MAGIC 33!\n");
	return (0);
}

int		magic_hook34(t_view *view)
{
	(void) view;
	printf("MAGIC 34!\n");
	return (0);
}

int		magic_hook35(t_view *view)
{
	(void) view;
	printf("MAGIC 35!\n");
	return (0);
}

