/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:28:47 by tpaaso            #+#    #+#             */
/*   Updated: 2022/12/01 15:24:30 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

float	pythagoras(float a, float b)
{
	double	c;

	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	c = (a * a) + (b * b);
	c = sqrt(c);
	return (c);
}

/*
 * It takes a column of pixels and draws them to the image buffer
 * @param x the x coordinate of the pixel to be drawn
 * @param y the y coordinate of the pixel to be drawn
 * @param distance the distance from the player to the wall
 */
void	clmn_to_img(t_wolf3d *data, int x, int y, float distance)
{
	float	shade;

	shade = 1;
	if (distance > 700)
	{
		while (distance > 500 || shade > 0.5)
		{
			distance -= 200;
			shade -= 0.05;
		}
	}
	if (shade < 0)
		shade = 0;
	if (y < data->img_height && x < data->img_width)
	{
		data->img_buf[((x) * 4) + (y * data->line_bytes)]
			= data->color_b * shade;
		data->img_buf[((x) * 4) + (y * data->line_bytes) + 1]
			= data->color_g * shade;
		data->img_buf[((x) * 4) + (y * data->line_bytes) + 2]
			= data->color_r * shade;
	}
}

/**
 * It draws a column of pixels to the image
 * 
 * @param data the structure that holds all the data for the program
 * @param distance the distance from the player to the wall
 * @param count the column number
 */
void	draw_clmn(t_wolf3d *data, float distance, int count)
{
	int		x;
	int		y;
	int		max_y;
	float	shade;

	x = data->img_width / WIDTH * count;
	y = (data->img_height / 2) - (BITS * 554 / (int)roundf(distance))
		* data->height + data->tilt;
	shade = 1;
	if (y < 0)
		y = 1;
	max_y = (data->img_height / 2) + (BITS * 554 / (int)roundf(distance))
		+ data->tilt;
	if (max_y > data->img_height)
		max_y = data->img_height;
	while (y < data->img_height && y <= max_y)
	{
		clmn_to_img(data, x, y, distance);
		y++;
	}
}

/*
 * It casts a ray from the player's position in the direction 
 * of the minimum fov, and returns the
 * distance to the first wall it hits
 * 
 * @param min_fov The minimum field of view.
 * @return The distance from the player to the wall.
 */
float	ft_raycast(t_wolf3d *data, float min_fov)
{
	float	dx;
	float	dy;
	float	x;
	float	y;

	if (min_fov > 2 * PI)
		min_fov -= 2 * PI;
	if (min_fov < 0)
		min_fov += 2 * PI;
	x = roundf(data->player_x);
	y = roundf(data->player_y);
	dx = cosf(min_fov);
	dy = sinf(min_fov);
	while (data->map[(int)roundf(y)][(int)roundf(x)] == ' ')
	{
		if ((data->map[(int)roundf(y)][(int)roundf(x + dx)]
			!= ' ' && data->map[(int)roundf(y + dy)][(int)roundf(x)] != ' '))
			break ;
		x -= dx;
		y -= dy;
	}
	data_wall_dir((int)roundf(x), (int)roundf(y), data);
	x -= roundf(data->player_x);
	y -= roundf(data->player_y);
	return (pythagoras(x, y));
}

/*
 * It renders the field of view of the player
 * @param data the structure that holds all the data for the game
 */
void	render_fov(t_wolf3d *data)
{
	float	max_fov;
	float	min_fov;
	float	distance;
	int		count;

	max_fov = data->player_a + 30 * DEGREES;
	min_fov = data->player_a - 30 * DEGREES;
	count = 0;
	while (count < WIDTH)
	{
		distance = ft_raycast(data, min_fov);
		distance *= cosf(data->player_a - min_fov);
		if (distance < 1)
			distance = 1;
		draw_clmn(data, distance, count);
		min_fov += DEGREES * 30 / (WIDTH / 2);
		count++;
	}
}
