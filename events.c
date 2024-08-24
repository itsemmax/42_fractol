/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaoub <ichaoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 02:05:55 by ichaoub           #+#    #+#             */
/*   Updated: 2024/07/01 20:20:24 by ichaoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handler(int keycode, t_fractal *fractal)
{
	if (keycode == 65307)
		close_handler(fractal);
	if (keycode == 65361)
		fractal->shift_x -= 0.5 * fractal->zoom;
	else if (keycode == 65363)
		fractal->shift_x += 0.5 * fractal->zoom;
	else if (keycode == 65362)
		fractal->shift_y += 0.5 * fractal->zoom;
	else if (keycode == 65364)
		fractal->shift_y -= 0.5 * fractal->zoom;
	else if (keycode == 61)
		fractal->max_iterations += 10;
	else if (keycode == 45)
		fractal->max_iterations -= 10;
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == 5)
	{
		fractal->zoom *= 0.95;
	}
	else if (button == 4)
	{
		fractal->zoom *= 1.5;
	}
	fractal_render(fractal);
	return (0);
}

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->image_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}
