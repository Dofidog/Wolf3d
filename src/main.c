/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:56:32 by tpaaso            #+#    #+#             */
/*   Updated: 2022/12/07 14:17:04 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_mlx(t_wolf3d *data)
{
	data->mlx_ptr = mlx_init();
	data->img_width = WIDTH;
	data->img_height = HEIGHT;
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->img_width, data->img_height + 135, "wolf3d");
	data->img_ptr = mlx_new_image(data->mlx_ptr,
			data->img_width, data->img_height);
	data->img_buf = mlx_get_data_addr(data->img_ptr,
			&data->pixel_bits, &data->line_bytes, &data->endian);
	if (!data->mlx_ptr || !data->win_ptr || !data->img_ptr)
		exit (-1);
}

void	init_wolf(t_wolf3d *data)
{
	init_mlx(data);
	data->color_b = 0x00;
	data->color_g = 0x00;
	data->color_r = 0x00;
	data->player_x = BITS * 1.5;
	data->player_y = BITS * 1.5;
	data->player_a = PI;
	data->height = 1;
	data->tilt = 0;
	data->dx = cosf(data->player_a * 5);
	data->dy = sinf(data->player_a * 5);
	data->switch_start_exit = 0;
	data->switch_characters = 0;
	data->selector_start_exit = 'S';
	data->selector_character = 0;
	data->x_max = 0;
	data->dimension = 4;
}

/*
 * It finds the first space in the map and sets the player's 
 * position to the middle of that space.
 * @param data the structure that holds all the data for the program
 */
int	player_start_pos(t_wolf3d *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->y_max)
	{
		x = 0;
		while (x < data->x_max)
		{
			if (data->map[y][x] == ' ')
			{
				data->player_x = x + (BITS / 2);
				return (y + (BITS / 2));
			}
			x++;
		}
		y++;
	}
	ft_exit("error; invalid map");
	return (0);
}

int	main(int ac, char **av)
{
	t_wolf3d	*data;

	data = (t_wolf3d *)malloc(sizeof(t_wolf3d));
	if (data == NULL || ac != 2)
		ft_exit("error");
	init_wolf(data);
	read_map(av[1], data);
	draw_skybox(data);
	data->player_y = player_start_pos(data);
	render_fov(data);
	data->x_2dmax = data->x_max / 64 * 10;
	data->y_2dmax = data->y_max / 64 * 10;
	data->img_2d_ptr = mlx_new_image(data->mlx_ptr,
			data->x_2dmax, data->y_2dmax);
	if (!data->img_2d_ptr)
		exit (-1);
	data->img_2d_buf = mlx_get_data_addr(data->img_2d_ptr,
			&data->pixel_2d_bits, &data->line_2d_bytes, &data->endian);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	menu_main(data);
	if (data->dimension != 4)
		mlx_hook(data->win_ptr, 2, 0L, deal_key, data);
	mlx_hook(data->win_ptr, 17, 0L, exit_program, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
