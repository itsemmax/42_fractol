/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaoub <ichaoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:47:51 by ichaoub           #+#    #+#             */
/*   Updated: 2024/07/01 21:02:57 by ichaoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <math.h>
# define WIDTH	800
# define HEIGHT	800
# define BLACK   0x000000
# define WHITE   0xFFFFFF

typedef struct s_fractal
{
	void	*mlx_connection; //mlx init
	void	*mlx_window; //new_window
	void	*image_ptr; //pointer to image 
	void	*pixels_ptr; // points to the actual pixel
	int		bpp; // bits per pixel
	int		line_len; // Number of bytes in a single row of the image
	int		endian; //(0 for little-endian, 1 for big-endian).
	int		x; // Current x-coordinate in the image.
	int		y; // Current y-coordinate in the image.
	double	zx; // real part of the complex number z.
	double	zy; // Imaginary part of the complex number z.
	double	cx; // real part of the complex constant c.
	double	cy; // Imaginary part of the complex constant c.
	double	julia_cx;
	double	julia_cy;
	double	shift_x;
	double	shift_y;
	int		color; // Current color value used for drawing.
	double	zoom; // Zoom level for zooming in and out
	char	*name; // Name of the fractal type
	int		max_iterations;
	double	escape_value;
}	t_fractal;

void	fractal_init(t_fractal *fractal);
void	data_init(t_fractal *fractal);
void	fractal_render(t_fractal *fractal);
void	draw_julia(double x, double y, t_fractal *fractal);
void	draw_mandelbrot(double x, double y, t_fractal *fractal);
void	draw_burningship(double x, double y, t_fractal *fractal);
double	map(double unscaled_num, double new_min,
			double new_max, double old_max);
int		check_arg(char *str);
double	ft_get_double(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
void	get_value(int argc, char **argv, t_fractal *fractal);
int		exit_fractal(t_fractal *fractal);
void	events_init(t_fractal *fractal);
int		key_handler(int keycode, t_fractal *fractal);
int		mouse_handler(int button, int x, int y, t_fractal *fractal);
int		close_handler(t_fractal *fractal);
#endif