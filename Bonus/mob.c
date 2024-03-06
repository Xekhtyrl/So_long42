/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:05:56 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 17:30:37 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	load_mob_image(t_map_info *data, char *path, char *name, int i)
{
	data->mobs_img[i].name = name;
	data->mobs_img[i].back = load_player_image(data->mlx, path, "back");
	data->mobs_img[i].front = load_player_image(data->mlx, path, "front");
	data->mobs_img[i].left = load_player_image(data->mlx, path, "left");
	data->mobs_img[i].right = load_player_image(data->mlx, path, "right");
}

int	init_mobs(t_map_info *data)
{
	int	i;

	i = -1;
	if (data->mobs_count < 1)
		return (0);
	data->mobs_img = ft_calloc(sizeof(t_pacmon), data->mobs_count);
	if (!data->mobs_img)
		return (-1);
	while (++i < data->mobs_count)
	{
		if (i % 5 == 0)
			load_mob_image(data, "./Sprites/Mobs/duskull/", "duskull", i);
		else if (i % 5 == 1)
			load_mob_image(data, "./Sprites/Mobs/gastly/", "gastly", i);
		else if (i % 5 == 2)
			load_mob_image(data, "./Sprites/Mobs/haunter/", "haunter", i);
		else if (i % 5 == 3)
			load_mob_image(data, "./Sprites/Mobs/sableye/", "sableye", i);
		else if (i % 5 == 4)
			load_mob_image(data, "./Sprites/Mobs/yamask/", "yamask", i);
		if (data->mobs_count == -1)
			return (0);
	}
	return (1);
}
