/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:36:25 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 16:27:44 by lvodak           ###   ########.fr       */
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

void	moves_display(t_map_info *data)
{
	char				*nb;
	char				*str;
	static mlx_image_t	*img;

	if (data->possible != 0)
		mlx_delete_image(data->mlx, img);
	nb = ft_itoa(data->possible - 1);
	str = ft_strjoin("Moves:", nb);
	img = mlx_put_string(data->mlx, str, data->p_size / 2, 0);
	free(nb);
	free(str);
}

void	print_move(t_map_info *data, t_pacmon *pacmon)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && !mlx_is_key_down(data->mlx,
			MLX_KEY_D) && !next_step_is_wall(*data, pacmon->back->instances[0],
			MLX_KEY_A))
		data->possible++;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_S) && !next_step_is_wall(*data,
			pacmon->back->instances[0], MLX_KEY_W))
		data->possible++;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_W) && !next_step_is_wall(*data,
			pacmon->back->instances[0], MLX_KEY_S))
		data->possible++;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_A) && !next_step_is_wall(*data,
			pacmon->back->instances[0], MLX_KEY_D))
		data->possible++;
	moves_display(data);
}
