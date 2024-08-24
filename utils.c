/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaoub <ichaoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:38:17 by ichaoub           #+#    #+#             */
/*   Updated: 2024/07/05 15:48:09 by ichaoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	double	old_min;

	old_min = 0;
	return ((new_max - new_min) * (unscaled_num - old_min)
		/ (old_max - old_min) + new_min);
}

void	get_value(int argc, char **argv, t_fractal *fractal)
{
	if (argc == 2)
	{
		fractal->julia_cx = -0.745429;
		fractal->julia_cy = 0.05;
	}
	else
	{
		if (check_arg(argv[2]) && check_arg(argv[3]))
		{
			fractal->julia_cx = ft_get_double(argv[2]);
			fractal->julia_cy = ft_get_double(argv[3]);
		}
		else
		{
			write(2, "./fractol mandelbrot\n or julia\n or burningship\n", 48);
			exit(EXIT_FAILURE);
		}
	}
}

int	check_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
		i++;
	if (s[i] == '.' && s[i])
		i++;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

double	ft_get_double(char *str)
{
	int		i;
	double	j;
	int		sign;
	double	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i++] == '-')
		sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
	}
	if (str[i] == '.')
		i++;
	j = 10;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res + (str[i++] - '0') / j;
		j *= 10;
	}
	return (res * sign);
}

int	exit_fractal(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->image_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	free(fractal->mlx_connection);
	free(fractal);
	exit(1);
	return (0);
}
