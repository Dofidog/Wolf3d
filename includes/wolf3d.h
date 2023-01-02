/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:45:45 by tpaaso            #+#    #+#             */
/*   Updated: 2022/12/06 16:06:22 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <fcntl.h>
# define PI 3.141592654
# define DEGREES 0.01745329
# define SPEED 10
# define BITS 64
# define WIDTH 1280
# define HEIGHT 800
# define LIMIT 100

typedef struct s_wolf3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*img_2d_ptr;
	int			pixel_bits;
	int			line_bytes;
	int			pixel_2d_bits;
	int			line_2d_bytes;
	int			endian;
	int			img_width;
	int			img_height;
	int			color_r;
	int			color_g;
	int			color_b;
	int			y_max;
	int			x_max;
	int			x_2dmax;
	int			y_2dmax;
	int			dimension;
	int			tilt;
	char		*img_buf;
	char		*img_2d_buf;
	char		**map;
	float		dx;
	float		dy;
	float		height;
	float		player_x;
	float		player_y;
	float		player_a;
	void		*img_menu_start_exit;
	char		selector_start_exit;
	int			switch_start_exit;
	void		*img_menu_char_selection;
	int			selector_character;
	int			switch_characters;
	void		*img_hud_char_0;
	void		*img_hud_char_1;
	void		*img_hud_char_0_angry;
	void		*img_hud_char_1_angry;
	void		*img_hud_current;
	void		*img_hud_current_angry;
}				t_wolf3d;

enum e_key_presses
{
	ARR_UP = 126,
	ARR_DN = 125,
	ARR_R = 124,
	ARR_L = 123,
	ENTER = 36,
	ESC = 53,
	P = 35,
	PLUS = 24,
	MINUS = 27,
	W = 13,
	S = 1,
};

int		deal_key(int key, t_wolf3d *data);
void	move_player(int key, t_wolf3d *data);
void	init_mlx(t_wolf3d *data);
void	init_wolf(t_wolf3d *data);
void	read_map(char *file, t_wolf3d *data);
void	map_len(char *file, t_wolf3d *data);
char	*copy_line(char *line, t_wolf3d *data);
void	get_color(t_wolf3d *data, int x, int y);
void	fill_gaps(char *line);
void	render_fov(t_wolf3d *data);
void	clear_image(t_wolf3d *data);
void	draw_clmn(t_wolf3d *data, float distance, int count);
void	clmn_to_img(t_wolf3d *data, int x, int y, float distance);
float	pythagoras(float a, float b);
float	ft_raycast(t_wolf3d *data, float min_fov);
void	draw_skybox(t_wolf3d *data);
void	data_wall_dir(int x, int y, t_wolf3d *data);
void	rotate_player(int key, t_wolf3d *data);
void	create_2d_img(t_wolf3d *data);
void	color_square(t_wolf3d *data, int x, int y);
void	*texture_read(t_wolf3d *data, char *path, void *image);
void	menu_main(t_wolf3d *data);
int		menu_character(int key, t_wolf3d *data);
void	init_new_values(t_wolf3d *data);
int		player_start_pos(t_wolf3d *data);
int		exit_program(t_wolf3d *data);

#endif