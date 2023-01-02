/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:29:23 by tpaaso            #+#    #+#             */
/*   Updated: 2022/12/07 14:17:21 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
 * It takes a line of the map, and converts it into a string of the 
 * same length as the map's width.
 * @return A string of characters.
 */
char	*copy_line(char *line, t_wolf3d *data)
{
	char	*str;
	int		i;
	int		x;

	i = 0;
	x = 0;
	str = (char *)malloc(sizeof(char) * data->x_max + 1);
	if (str == NULL)
		ft_exit("malloc error");
	while (i < (int)ft_strlen(line))
	{
		while (x <= (i + 1) * BITS - 1)
		{
			str[x] = line[i];
			x++;
		}
		i++;
	}
	while (x - 1 < data->x_max)
	{
		str[x - 1] = '#';
		x++;
	}
	str[x - 1] = '\0';
	return (str);
}

/*
 * It opens the file, reads the first line, and then reads the rest 
 * of the file to determine the size of the map.
 */
void	map_len(char *file, t_wolf3d *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (get_next_line(fd, &line) <= 0)
		ft_exit("error; invalid file");
	if (line == NULL)
		ft_exit("error");
	data->x_max = ft_strlen(line) * BITS;
	free(line);
	while (get_next_line(fd, &line))
	{
		i++;
		if ((int)ft_strlen(line) * BITS > data->x_max)
			data->x_max = ft_strlen(line) * BITS;
		free(line);
	}
	if (data->x_max <= 2 * BITS || i < 2
		|| data->x_max >= LIMIT * BITS || i > LIMIT - 1)
		ft_exit("error; invalid map");
	i++;
	fd = close(fd);
	data->y_max = i * BITS;
}

/*
 * It takes a string and fills it with '#' characters
 * @param line the line that is being filled with #'s
 */
void	fill_gaps(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		ft_exit("error; empty line");
	while (line [i] != '\0')
	{
		line[i] = '#';
		i++;
	}
}

/*
 * It reads the map file,
 * and fills the data->map array with the map.
 * @param file the name of the file to be read
 */
void	read_map(char *file, t_wolf3d *data)
{
	int		fd;
	char	*line;
	int		i;
	int		y;

	i = 0;
	y = 0;
	map_len(file, data);
	data->map = (char **)malloc(sizeof(char *) * data->y_max);
	if (data->map == NULL)
		ft_exit("malloc error");
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] != '#' || y == 0 || y > data->y_max - BITS * 2)
			fill_gaps(line);
		while (y <= (i + 1) * BITS - 1)
		{
			data->map[y] = copy_line(line, data);
			y++;
		}
		i++;
		free(line);
	}
	fd = close(fd);
}

/**
 * It checks the surrounding
 * tiles of the current tile and sets the color of the wall accordingly
 * 
 * @param x the x position of the wall
 * @param y the y coordinate of the map
 * @param data the structure that holds all the data for the program
 */
void	data_wall_dir(int x, int y, t_wolf3d *data)
{
	data->color_r = 0x00;
	data->color_g = 0x00;
	data->color_b = 0x00;
	if (data->map[y][x - 1] == ' ')
		data->color_g = 0x55;
	if (data->map[y][x + 1] == ' ')
		data->color_b = 0x55;
	if (data->map[y - 1][x] == ' ')
		data->color_r = 0x55;
	if (data->map[y + 1][x] == ' ')
	{
		data->color_b = 0x66;
		data->color_r = 0x44;
		if (data->map[y][x + 1] == ' ')
			data->color_g = 0x55;
	}
}
