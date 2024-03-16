/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:21:30 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 16:29:15 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	hook_movements_bis(t_map_info *data)
{
	print_move(data, data->player);
	collect_collectible(data, data->player->front->instances[0]);
	end_game(data, data->player->front->instances[0], 1);
	if (mob_hit(data->player->back->instances[0], data->mobs_img, data->p_size,
			data->mobs_count))
	{
		end_game(data, data->player->front->instances[0], 0);
		return (1);
	}
	return (0);
}

void	hook_movements(void *param)
{
	t_map_info	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_W) && mob_hook(data,
			MLX_KEY_W))
		move_up(data->player, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_S) && mob_hook(data,
			MLX_KEY_S))
		move_down(data->player, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_A) && mob_hook(data,
			MLX_KEY_A))
		move_left(data->player, data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) && !next_step_is_wall(*data,
			data->player->front->instances[0], MLX_KEY_D) && mob_hook(data,
			MLX_KEY_D))
		move_right(data->player, data);
	if (hook_movements_bis(data))
		return ;
}

void	hook_menu(struct mlx_key_data keydata, void *param)
{
	t_menu	*menu;

	menu = param;
	menu->cursor->instances[0].enabled = false;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT))
		return (mlx_close_window(menu->mlx));
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT))
	{
		if (menu->cursor->instances[0].x == 25)
			menu->cursor->instances[0].x = 525;
		menu->cursor->instances[0].x -= 100;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT))
	{
		menu->cursor->instances[0].x += 100;
		if (menu->cursor->instances[0].x == 525)
			menu->cursor->instances[0].x = 25;
	}
	menu->cursor->instances[0].enabled = true;
	if (keydata.key == MLX_KEY_ENTER && (keydata.action == MLX_RELEASE
			|| keydata.action == MLX_REPEAT))
		mlx_close_window(menu->mlx);
}

void	close_menu(void *param)
{
	t_menu	*menu;
	int		i;

	menu = param;
	i = -1;
	while (++i < 6)
		mlx_delete_image((*menu).mlx, (*menu).all[i]);
	mlx_delete_image((*menu).mlx, (*menu).cursor);
	mlx_close_window((*menu).mlx);
}
