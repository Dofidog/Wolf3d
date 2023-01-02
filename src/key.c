/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:16:26 by tpaaso            #+#    #+#             */
/*   Updated: 2022/12/06 16:01:11 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
 * It deals with the key presses
 * @param key the key that was pressed
 */
int	deal_key(int key, t_wolf3d *data)
{
	if (key == ESC)
		exit_program(data);
	if (data->dimension == 4)
		return (0);
	if (key == ARR_UP || key == ARR_DN)
		move_player(key, data);
	if (key == ARR_L || key == ARR_R)
		rotate_player(key, data);
	if (key == P)
	{
		if (data->dimension == 2)
			data->dimension = 3;
		else
			data->dimension = 2;
	}
	if (key == W && data->tilt <= 500)
		data->tilt += 100;
	if (key == S && data->tilt >= -500)
		data->tilt -= 100;
	if (key == PLUS && data->height <= 15)
		data->height += 0.1;
	if (key == MINUS && data->height >= -1.1)
		data->height -= 0.1;
	init_new_values(data);
	return (0);
}

/*
 * It clears the image, draws the skybox, renders the fov,
 * creates the 2d image, and puts the image to the window
 */
void	init_new_values(t_wolf3d *data)
{
	clear_image(data);
	draw_skybox(data);
	render_fov(data);
	create_2d_img(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	if (ft_raycast(data, data->player_a) <= SPEED)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_hud_current_angry, 0, HEIGHT);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_hud_current, 0, HEIGHT);
	if (data->dimension == 2)
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img_2d_ptr, 0, 0);
}

/*
 * It rotates the player's direction by 10 degrees to the left or right
 */
void	rotate_player(int key, t_wolf3d *data)
{
	if (key == ARR_L)
	{
		data->player_a -= 10 * DEGREES;
		if (data->player_a < 0)
			data->player_a += 2 * PI;
		data->dx = cosf(data->player_a);
		data->dy = sinf(data->player_a);
	}
	if (key == ARR_R)
	{
		data->player_a += 10 * DEGREES;
		if (data->player_a > 2 * PI)
			data->player_a -= 2 * PI;
		data->dx = cosf(data->player_a);
		data->dy = sinf(data->player_a);
	}
}

/*
 * It moves the player in the direction of the key pressed, 
 * if there's no wall in the way
 */
void	move_player(int key, t_wolf3d *data)
{
	if (key == ARR_UP && ft_raycast(data, data->player_a)
		> pythagoras(roundf(data->dx), roundf(data->dy)) * SPEED)
	{
		data->player_x -= data->dx * SPEED;
		data->player_y -= data->dy * SPEED;
	}
	if (key == ARR_DN && ft_raycast(data, data->player_a + (180 * DEGREES))
		> pythagoras(roundf(data->dx), roundf(data->dy)) * SPEED)
	{
		data->player_x += data->dx * SPEED;
		data->player_y += data->dy * SPEED;
	}
}
