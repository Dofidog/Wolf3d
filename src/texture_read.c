/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:48:28 by tturto            #+#    #+#             */
/*   Updated: 2022/12/07 14:26:32 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
 *	img_width & img_height are auto-defined unless pre-defined.
*/
void	*texture_read(t_wolf3d *data, char *path, void *image)
{
	int	img_width;
	int	img_height;

	image = mlx_xpm_file_to_image(data->mlx_ptr, path, &img_width, &img_height);
	if (image == NULL)
		ft_exit("texture read fail; ensure running .exe at root folder");
	return (image);
}
