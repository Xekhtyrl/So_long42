/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:49:51 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/07 18:09:04 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	next_step_is_wall(t_map_info data, mlx_instance_t instance, int dir)
{
	t_point	p0;
	t_point	p1;
	t_point	w;

	p0 = (t_point){instance.x, instance.y, 0, 0, 0};
	p1 = (t_point){p0.x + data.p_size - 1, p0.y + data.p_size - 1, 0, 0, 0};
	if (dir == MLX_KEY_W)
		w = (t_point){p0.x, p0.y - 1, p1.x, p0.y - 1, 0};
	if (dir == MLX_KEY_S)
		w = (t_point){p0.x, p1.y + 1, p1.x, p1.y + 1, 0};
	if (dir == MLX_KEY_A)
		w = (t_point){p0.x - 1, p0.y, p0.x - 1, p1.y, 0};
	if (dir == MLX_KEY_D)
		w = (t_point){p1.x + 1, p0.y, p1.x + 1, p1.y, 0};
	if (data.all_img[w.y / data.p_size][w.x / data.p_size]->instances[0].z == 10
		|| data.all_img[w.ry / data.p_size][w.rx / data.p_size]->instances[0].z
			== 10)
		return (1);
	return (0);
}

void	collect_collectible(t_map_info *data, mlx_instance_t instance)
{
	int	i;

	i = -1;
	while (++i < data->tot_collectibles)
	{
		if (data->coll_img[i]->instances[0].enabled == true)
		{
			if (data->coll_img[i]->instances[0].x == instance.x
				&& data->coll_img[i]->instances[0].y == instance.y)
			{
				data->coll_img[i]->instances[0].enabled = false;
				(*data).collectibles -= 1;
				return ;
			}
		}
	}
	if (data->collectibles == 0)
		data->exit_img->instances[0].enabled = true;
}

void	end_game(t_map_info *data, mlx_instance_t instance)
{
	if (instance.x == data->exit_img->instances[0].x && instance.y
		== data->exit_img->instances[0].y)
	{
		if (data->exit_img->instances[0].enabled == true)
		{
			mlx_close_window(data->mlx);
			ft_printf("You Won! Time to face the Council 4!!!\n");
		}
	}
}
