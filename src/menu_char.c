/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:43:33 by tturto            #+#    #+#             */
/*   Updated: 2022/12/06 16:01:07 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
 * Continues to image rendering based on the selected character
*/
void	menu_exec_char_select(int key, t_wolf3d *data)
{
	if (key == ENTER)
	{
		data->switch_characters = 1;
		if (data->selector_character == 0)
		{
			data->img_hud_current = data->img_hud_char_0;
			data->img_hud_current_angry = data->img_hud_char_0_angry;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_ptr, 0, 0);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_hud_current, 0, HEIGHT);
			mlx_hook(data->win_ptr, 2, 1L << 0, deal_key, data);
		}
		if (data->selector_character == 1)
		{
			data->img_hud_current = data->img_hud_char_1;
			data->img_hud_current_angry = data->img_hud_char_1_angry;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_ptr, 0, 0);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_hud_current, 0, HEIGHT);
			mlx_hook(data->win_ptr, 2, 1L << 0, deal_key, data);
		}
		data->dimension = 3;
	}
}

/*
 *	Continues to image rendering after character selection
*/
int	menu_select_char(int key, t_wolf3d *data)
{
	if (data->switch_characters == 0)
	{
		if (key == ARR_DN)
		{
			data->selector_character = 1;
			mlx_destroy_image(data->mlx_ptr, data->img_menu_char_selection);
			data->img_menu_char_selection = texture_read(data,
					"./textures/char_select_1.xpm",
					data->img_menu_char_selection);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_menu_char_selection, 0, 0);
		}
		if (key == ARR_UP)
		{
			data->selector_character = 0;
			mlx_destroy_image(data->mlx_ptr, data->img_menu_char_selection);
			data->img_menu_char_selection = texture_read(data,
					"./textures/char_select_0.xpm",
					data->img_menu_char_selection);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_menu_char_selection, 0, 0);
		}
	}
	return (0);
}

void	hud_images(t_wolf3d *data)
{
	data->img_hud_char_0 = texture_read(data,
			"./textures/hud_tp.xpm", data->img_hud_char_0);
	data->img_hud_char_1 = texture_read(data,
			"./textures/hud_tt.xpm", data->img_hud_char_1);
	data->img_hud_char_0_angry = texture_read(data,
			"./textures/hud_tp_angry.xpm",
			data->img_hud_char_0_angry);
	data->img_hud_char_1_angry = texture_read(data,
			"./textures/hud_tt_angry.xpm",
			data->img_hud_char_1_angry);
}

int	menu_character(int key, t_wolf3d *data)
{
	if (key == ESC)
		exit_program(data);
	hud_images(data);
	menu_select_char(key, data);
	menu_exec_char_select(key, data);
	return (0);
}
