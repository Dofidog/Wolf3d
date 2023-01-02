/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:37:04 by tpaaso            #+#    #+#             */
/*   Updated: 2022/12/01 14:24:43 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
 * It draws the skybox
 */
void	draw_skybox(t_wolf3d *data)
{
	int		x;
	int		y;

	y = 0;
	data->color_b = 0x82;
	data->color_g = 0x44;
	data->color_r = 0x2E;
	while (y < data->img_height)
	{
		x = 0;
		if (y > data->img_height / 2 + data->tilt)
		{
			data->color_b = 0x3F;
			data->color_g = 0x85;
			data->color_r = 0xCD;
		}
		while (x < data->img_width)
		{
			data->img_buf[(x * 4) + (y * data->line_bytes)] = data->color_b;
			data->img_buf[(x * 4) + (y * data->line_bytes) + 1] = data->color_g;
			data->img_buf[(x * 4) + (y * data->line_bytes) + 2] = data->color_r;
			x++;
		}
		y++;
	}
}

/**
 * It clears the image buffer
 * 
 * @param data the structure that holds all the data for the program
 */
void	clear_image(t_wolf3d *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->img_height)
	{
		x = 0;
		while (x < data->img_width)
		{
			data->img_buf[(x * 4) + (y * data->line_bytes)] = 0x00;
			data->img_buf[(x * 4) + (y * data->line_bytes) + 1] = 0x00;
			data->img_buf[(x * 4) + (y * data->line_bytes) + 2] = 0x00;
			x++;
		}
		y++;
	}
}

/*
 * It gets the color of the pixel
 * @param x the x coordinate of the pixel to be drawn
 * @param y the y coordinate of the pixel to be drawn
 */
void	get_color(t_wolf3d *data, int x, int y)
{
	data->color_b = 0x00;
	data->color_g = 0x00;
	data->color_r = 0x00;
	if (data->map[y][x] != ' ')
	{
		data->color_b = 0x99;
		data->color_g = 0x99;
		data->color_r = 0x99;
	}
	if ((int)data->player_x >= x && (int)data->player_y >= y
		&& (int)data->player_x < x + BITS && (int)data->player_y < y + BITS)
	{
		data->color_b = 0x00;
		data->color_g = 0x00;
		data->color_r = 0x99;
	}
}
