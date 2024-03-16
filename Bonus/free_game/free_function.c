/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:49:21 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 16:27:21 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	free_collectibles(t_map_info *data)
{
	int	i;

	i = -1;
	while (++i < data->collectibles)
		mlx_delete_image(data->mlx, data->coll_img[i]);
	free(data->coll_img);
	data->coll_img = NULL;
}

static void	free_images(t_map_info *data, t_point last, int flag)
{
	int			i;
	int			j;

	if (last.x || last.y)
	{
		j = last.x + 1;
		while (--j >= 0)
			mlx_delete_image(data->mlx, data->all_img[last.y][j]);
		free(data->all_img[last.y]);
		i = last.y + 1;
	}
	else
		i = data->length;
	while (--i >= 0)
	{
		j = data->width;
		if (!flag)
			while (--j >= 0)
				mlx_delete_image(data->mlx, data->all_img[i][j]);
		free(data->all_img[i]);
		data->all_img[i] = NULL;
	}
	free(data->all_img);
	data->all_img = NULL;
}

static void	delete_pacmon_images(t_map_info *data, t_pacmon *pacmon)
{
	mlx_delete_image(data->mlx, (*pacmon).back);
	mlx_delete_image(data->mlx, (*pacmon).front);
	mlx_delete_image(data->mlx, (*pacmon).left);
	mlx_delete_image(data->mlx, (*pacmon).right);
	(*pacmon).back = NULL;
	(*pacmon).front = NULL;
	(*pacmon).left = NULL;
	(*pacmon).right = NULL;
}

static void	delete_pacmons_images(t_map_info *data, t_pacmon **pacmon)
{
	while (--data->mobs_count >= 0)
	{
		mlx_delete_image(data->mlx, (*pacmon)[data->mobs_count].back);
		mlx_delete_image(data->mlx, (*pacmon)[data->mobs_count].front);
		mlx_delete_image(data->mlx, (*pacmon)[data->mobs_count].left);
		mlx_delete_image(data->mlx, (*pacmon)[data->mobs_count].right);
		(*pacmon)[data->mobs_count].back = NULL;
		(*pacmon)[data->mobs_count].front = NULL;
		(*pacmon)[data->mobs_count].left = NULL;
		(*pacmon)[data->mobs_count].right = NULL;
	}
	free(data->mobs_img);
	data->mobs_img = NULL;
}

void	free_game(t_map_info *data, t_point *last, int flag)
{
	if (data->collectibles)
		free_collectibles(data);
	if (last)
		free_images(data, *last, flag);
	if (data->player)
		delete_pacmon_images(data, data->player);
	if (data->mobs_count)
		delete_pacmons_images(data, &data->mobs_img);
	mlx_delete_image(data->mlx, data->exit_img);
}
