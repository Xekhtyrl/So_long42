/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:36:25 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 17:23:23 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	init_player(t_map_info *data, t_point point)
{
	mlx_resize_image(data->player->front, data->p_size, data->p_size);
	mlx_resize_image(data->player->back, data->p_size, data->p_size);
	mlx_resize_image(data->player->left, data->p_size, data->p_size);
	mlx_resize_image(data->player->right, data->p_size, data->p_size);
	mlx_image_to_window(data->mlx, data->player->front, point.x * data->p_size,
		point.y * data->p_size);
	mlx_image_to_window(data->mlx, data->player->back, point.x * data->p_size,
		point.y * data->p_size);
	mlx_image_to_window(data->mlx, data->player->left, point.x * data->p_size,
		point.y * data->p_size);
	mlx_image_to_window(data->mlx, data->player->right, point.x * data->p_size,
		point.y * data->p_size);
	refresh_player(data->player);
	data->player->front->instances[0].enabled = true;
}

mlx_image_t	*load_player_image(mlx_t *mlx, char *sprite_path, char *part)
{
	char		*file_name;
	mlx_image_t	*img;
	xpm_t		*xpm;

	file_name = ft_strjoin(sprite_path, part);
	xpm = mlx_load_xpm42(file_name);
	free(file_name);
	img = mlx_texture_to_image(mlx, &(xpm->texture));
	mlx_delete_xpm42(xpm);
	return (img);
}
