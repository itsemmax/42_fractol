/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaoub <ichaoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:09:07 by ichaoub           #+#    #+#             */
/*   Updated: 2024/07/05 15:53:00 by ichaoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	put_pixel(int x, int y, t_fractal *fractal, int color)
{
	int	offset;

	offset = (y * fractal->line_len) + (x * fractal->bpp / 8);
	*(unsigned int *)(fractal->pixels_ptr + offset) = color;
}

void	draw_mandelbrot(double x, double y, t_fractal *fractal)
{
	double	temp;
	int		i;

	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = map(x, -2, 2, WIDTH) * fractal->zoom + fractal->shift_x;
	fractal->cy = map(y, 2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	while (i < fractal->max_iterations)
	{
		temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = 2 * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = temp;
		if ((fractal->zx * fractal->zx) + (fractal->zy * fractal->zy)
			> fractal->escape_value)
		{
			fractal->color = map(i, BLACK, WHITE, fractal->max_iterations);
			put_pixel(fractal->x, fractal->y, fractal, fractal->color);
			return ;
		}
		i++;
	}
	put_pixel(fractal->x, fractal->y, fractal, BLACK);
}

void	draw_burningship(double x, double y, t_fractal *fractal)
{
	double	temp;
	int		i;

	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = map(x, -2, 2, WIDTH) * fractal->zoom + fractal->shift_x;
	fractal->cy = map(y, 2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	while (i < fractal->max_iterations)
	{
		temp = fabs(fractal->zx * fractal->zx - fractal->zy * fractal->zy
				+ fractal->cx);
		fractal->zy = (fabs(2 * fractal->zx * fractal->zy + fractal->cy)) * -1;
		fractal->zx = temp;
		if ((fractal->zx * fractal->zx) + (fractal->zy * fractal->zy)
			> fractal->escape_value)
		{
			fractal->color = map(i, BLACK, WHITE, fractal->max_iterations);
			put_pixel(fractal->x, fractal->y, fractal, fractal->color);
			return ;
		}
		i++;
	}
	put_pixel(fractal->x, fractal->y, fractal, BLACK);
}

void	draw_julia(double x, double y, t_fractal *fractal)
{
	double	temp;
	int		i;

	i = 0;
	fractal->zx = map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	fractal->zy = map(y, 2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	fractal->cx = fractal->julia_cx ;
	fractal->cy = fractal->julia_cy ;
	while (i < fractal->max_iterations)
	{
		temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = 2. * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = temp;
		if ((fractal->zx * fractal->zx) + (fractal->zy * fractal->zy)
			> fractal->escape_value)
		{
			fractal->color = map(i, BLACK, WHITE, fractal->max_iterations);
			put_pixel(fractal->x, fractal->y, fractal, fractal->color);
			return ;
		}
		i++;
	}
	put_pixel(fractal->x, fractal->y, fractal, BLACK);
}

void	fractal_render(t_fractal *fractal)
{
	fractal->y = -1;
	while (++fractal->y < HEIGHT)
	{
		fractal->x = -1;
		while (++fractal->x < WIDTH)
		{
			if (!ft_strncmp(fractal->name, "mandelbrot", 10))
				draw_mandelbrot(fractal->x, fractal->y, fractal);
			else if (!ft_strncmp(fractal->name, "julia", 5))
				draw_julia(fractal->x, fractal->y, fractal);
			else if (!ft_strncmp(fractal->name, "burningship", 11))
				draw_burningship(fractal->x, fractal->y, fractal);
			else
			{
				write(2, "mandelbrot\n or julia\n or burningship\n", 38);
				exit_fractal(fractal);
			}
		}
		mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
			fractal->image_ptr, 0, 0);
	}
}
