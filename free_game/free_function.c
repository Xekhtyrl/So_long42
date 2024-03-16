/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:49:21 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 16:25:28 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
	mlx_delete_image(data->mlx, pacmon->back);
	mlx_delete_image(data->mlx, pacmon->front);
	mlx_delete_image(data->mlx, pacmon->left);
	mlx_delete_image(data->mlx, pacmon->right);
}

void	free_game(t_map_info *data, t_point *last, int flag)
{
	if (data->collectibles)
		free_collectibles(data);
	if (last)
		free_images(data, *last, flag);
	if (data->player)
		delete_pacmon_images(data, data->player);
	mlx_delete_image(data->mlx, data->exit_img);
}

void	free_map(t_maplst **map)
{
	t_maplst	*temp;
	t_maplst	*temp2;

	if (!map || !*map)
		return ;
	temp = *map;
	while (temp)
	{
		temp2 = temp->next;
		free(temp->line);
		free(temp);
		temp = temp2;
	}
	*map = 0;
}
