/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:21:30 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 15:09:48 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	hook_movements(struct mlx_key_data keydata, void *param)
{
	t_map_info	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT))
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_W))
		move_up(data->player, data);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_S))
		move_down(data->player, data);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_A))
		move_left(data->player, data);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_D))
		move_right(data->player, data);
	collect_collectible(data, data->player->front->instances[0]);
	end_game(data, data->player->front->instances[0]);
}

void	hook_menu(struct mlx_key_data keydata, void *param)
{
	t_menu	*menu;

	menu = param;
	menu->cursor->instances[0].enabled = false;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
	{
		mlx_close_window(menu->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
	{
		if (menu->cursor->instances[0].x == 25)
			menu->cursor->instances[0].x = 525;
		menu->cursor->instances[0].x -= 100;
		menu->cursor->instances[0].enabled = true;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
	{
		menu->cursor->instances[0].x += 100;
		if (menu->cursor->instances[0].x == 525)
			menu->cursor->instances[0].x = 25;
		menu->cursor->instances[0].enabled = true;
	}
	if (keydata.key == MLX_KEY_ENTER && (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT))
		mlx_close_window(menu->mlx);
}

void	close_menu(void *param)
{
	t_menu	*menu;
	int	i;

	menu = param;
	i = -1;
	while (++i < 6)
		mlx_delete_image((*menu).mlx, (*menu).all[i]);
	mlx_delete_image((*menu).mlx, (*menu).cursor);
	mlx_close_window((*menu).mlx);
}
