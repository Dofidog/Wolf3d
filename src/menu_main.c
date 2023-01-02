/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:14:47 by tpaaso            #+#    #+#             */
/*   Updated: 2022/12/06 16:01:00 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
 *	Continues to character selection or exits the program.
*/
void	menu_exec_start_exit(int key, t_wolf3d *data)
{
	if (key == ENTER)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_menu_start_exit);
		data->switch_start_exit = 1;
		if (data->selector_start_exit == 'S')
		{
			data->img_menu_char_selection = texture_read(data,
					"./textures/char_select_0.xpm",
					data->img_menu_char_selection);
			mlx_put_image_to_window(data->mlx_ptr,
				data->win_ptr, data->img_menu_char_selection, 0, 0);
			mlx_hook(data->win_ptr, 2, 1L << 0, menu_character, data);
		}
		if (data->selector_start_exit == 'E')
			exit(-1);
	}
}

/*
 *	UP and DOWN arrows move the selector position
*/
void	menu_select_start_exit(int key, t_wolf3d *data)
{
	if (data->switch_start_exit == 0)
	{
		if (key == ARR_DN)
		{
			data->selector_start_exit = 'E';
			mlx_destroy_image(data->mlx_ptr, data->img_menu_start_exit);
			data->img_menu_start_exit = texture_read(data,
					"./textures/menu-exit.xpm", data->img_menu_start_exit);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_menu_start_exit, 0, 0);
		}
		if (key == ARR_UP)
		{
			data->selector_start_exit = 'S';
			mlx_destroy_image(data->mlx_ptr, data->img_menu_start_exit);
			data->img_menu_start_exit = texture_read(data,
					"./textures/menu-start.xpm", data->img_menu_start_exit);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_menu_start_exit, 0, 0);
		}
	}
}

int	menu_start_exit(int key, t_wolf3d *data)
{
	if (key == ESC)
		exit_program(data);
	menu_select_start_exit(key, data);
	menu_exec_start_exit(key, data);
	return (0);
}

void	menu_main(t_wolf3d *data)
{
	data->img_menu_start_exit = texture_read(data,
			"./textures/menu-start.xpm", data->img_menu_start_exit);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img_menu_start_exit,
		0, 0);
	mlx_hook(data->win_ptr, 2, 1L << 0, menu_start_exit, data);
}
