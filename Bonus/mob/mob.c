/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:05:56 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 15:20:57 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	load_mob_struct(t_map_info *dt, char *path, char *name, int i)
{
	(*dt).mobs_img[i].name = name;
	(*dt).mobs_img[i].back = load_player_image(dt->mlx, path, "back.xpm42");
	(*dt).mobs_img[i].front = load_player_image(dt->mlx, path, "front.xpm42");
	(*dt).mobs_img[i].left = load_player_image(dt->mlx, path, "left.xpm42");
	(*dt).mobs_img[i].right = load_player_image(dt->mlx, path, "right.xpm42");
}

static void	place_mobs(t_map_info *dt, t_point point, int i)
{
	mlx_resize_image(dt->mobs_img[i].front, dt->p_size, dt->p_size);
	mlx_resize_image(dt->mobs_img[i].back, dt->p_size, dt->p_size);
	mlx_resize_image(dt->mobs_img[i].left, dt->p_size, dt->p_size);
	mlx_resize_image(dt->mobs_img[i].right, dt->p_size, dt->p_size);
	mlx_image_to_window(dt->mlx, dt->mobs_img[i].front, point.x * dt->p_size,
		point.y * dt->p_size);
	mlx_image_to_window(dt->mlx, dt->mobs_img[i].back, point.x * dt->p_size,
		point.y * dt->p_size);
	mlx_image_to_window(dt->mlx, dt->mobs_img[i].left, point.x * dt->p_size,
		point.y * dt->p_size);
	mlx_image_to_window(dt->mlx, dt->mobs_img[i].right, point.x * dt->p_size,
		point.y * dt->p_size);
	dt->mobs_img[i].back->instances[0].z = 20 + i;
	dt->mobs_img[i].front->instances[0].z = 20 + i;
	dt->mobs_img[i].left->instances[0].z = 20 + i;
	dt->mobs_img[i].right->instances[0].z = 20 + i;
	refresh_player(&(dt->mobs_img[i]));
	dt->mobs_img[i].front->instances[0].enabled = true;
}

int	init_mobs(t_map_info *data, t_point point)
{
	if (data->mobs_count < 0)
		return (0);
	if (--(data->mobs_count) < 0)
		return (0);
	if (data->mobs_count % 5 == 0)
		load_mob_struct(data, "./Sprites/Mobs/duskull/", "duskull",
			data->mobs_count);
	else if (data->mobs_count % 5 == 1)
		load_mob_struct(data, "./Sprites/Mobs/gastly/", "gastly",
			data->mobs_count);
	else if (data->mobs_count % 5 == 2)
		load_mob_struct(data, "./Sprites/Mobs/haunter/", "haunter",
			data->mobs_count);
	else if (data->mobs_count % 5 == 3)
		load_mob_struct(data, "./Sprites/Mobs/sableye/", "sableye",
			data->mobs_count);
	else if (data->mobs_count % 5 == 4)
		load_mob_struct(data, "./Sprites/Mobs/yamask/", "yamask",
			data->mobs_count);
	place_mobs(data, point, data->mobs_count);
	return (1);
}

int	update_rand(int r, int count)
{
	if (count % 16 == 1)
		r = rand();
	return (r);
}

int	mob_hook(t_map_info	*data, int key)
{
	int	i;

	i = -1;
	while (++i < data->mobs_count)
	{
		if (!ft_memcmp(data->mobs_img[i].name, "duskull", 7))
			duskull_moveset(data, &(data->mobs_img[i]), key);
		else if (!ft_memcmp(data->mobs_img[i].name, "haunter", 7))
			haunter_moveset(data, &(data->mobs_img[i]), key);
		else if (!ft_memcmp(data->mobs_img[i].name, "gastly", 6))
			gastly_moveset(data, &(data->mobs_img[i]), key);
		else if (!ft_memcmp(data->mobs_img[i].name, "sableye", 7))
			sableye_moveset(data, &(data->mobs_img[i]), key);
		else if (!ft_memcmp(data->mobs_img[i].name, "yamask", 6))
			yamask_moveset(data, &(data->mobs_img[i]), key);
	}
	return (1);
}
