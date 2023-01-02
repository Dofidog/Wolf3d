/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dimage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:45:29 by tpaaso            #+#    #+#             */
/*   Updated: 2022/11/29 16:14:05 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
 * It colors a square of 10x10 pixels in the 2D map
 *
 * @param x the x coordinate of the square
 * @param y the y coordinate of the square
 */
void	color_square(t_wolf3d *data, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
			data->img_2d_buf[((x + i) * 4) + ((y + j)
					* data->line_2d_bytes)] = data->color_b;
			data->img_2d_buf[((x + i) * 4) + ((y + j)
					* data->line_2d_bytes) + 1] = data->color_g;
			data->img_2d_buf[((x + i) * 4) + ((y + j)
					* data->line_2d_bytes) + 2] = data->color_r;
			i++;
		}
		j++;
	}
}

/*
 * It creates a 2d image of the map
 */
void	create_2d_img(t_wolf3d *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < data->y_2dmax)
	{
		x = 0;
		while (x < data->x_2dmax)
		{
			get_color(data, x / 10 * BITS, y / 10 * BITS);
			color_square(data, x, y);
			x += 10;
		}
		y += 10;
	}
}
