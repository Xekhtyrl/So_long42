/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:06:55 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/04 23:55:22 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

void	xpm_to_image(t_map_info *data, xpm_t *xpm, t_point point, int z)
{
	mlx_image_t	*img;
	int			i;

	i = 0;
	if (!xpm)
		return (perror("cheeeh"), /*free func*/exit(0));
	img = mlx_texture_to_image(data->mlx, &(xpm->texture));
	if (!img)
		return (perror("image not loaded!"), /*free func*/ exit(0));
	if (mlx_image_to_window(data->mlx, img, point.rx, point.ry) == -1)
		return (perror("image not loaded!"), /*free func*/ exit(0));
	if (!mlx_resize_image(img, data->p_size, data->p_size))
		return (perror("image not loaded!"), /*free func*/ exit(0));
	mlx_delete_xpm42(xpm);
	(*img).instances[0].z = z;
	if (!data->all_img[point.y][point.x])
		(*data).all_img[point.y][point.x] = img;
	else if (z != 5)
	{
		while (data->coll_img[i])
			i++;
		data->coll_img[i] = img;
	}
	else
		(*data).exit_img = img;
}

static int	place_image(char clue, t_point *point, t_collectibles **collect,
			t_map_info *data)
{
	if (clue == 'C' || clue == 'P' || clue == 'E')
		xpm_to_image(data, mlx_load_xpm42("./Sprites/Background/no_wall.xpm42"),
			*point, 0);
	if (clue == 'E')
	{
		xpm_to_image(data, mlx_load_xpm42("./Sprites/Background/exit.xpm42"),
			*point, 5);
		data->exit_img->instances[0].enabled = false;
	}
	else if (clue == 'P')
		init_player(data, *point);
	else if (clue == 'C' || clue == 'c')
		choose_collectible(data, collect, *point);
	else
		xpm_to_image(data, mlx_load_xpm42("./Sprites/Background/no_wall.xpm42"),
			*point, 0);
	point->rx += data->p_size;
	return (1);
}

static int	init_img_tab(t_map_info	*data)
{
	int	i;

	i = 0;
	data->all_img = ft_calloc(sizeof(mlx_image_t **), (size_t)data->length);
	if (!data->all_img)
		return (/*free function*/ 0);
	while (i < data->length)
	{
		data->all_img[i] = ft_calloc(sizeof(mlx_image_t *),
				(size_t)data->width);
		if (!data->all_img[i++])
			return (/*free function ++ */ 0);
	}
	(*data).coll_img = ft_calloc(sizeof(mlx_image_t *),
			(size_t)data->tot_collectibles);
	return (1);
}

static int	map_maker_x(t_maplst *map, t_point *point, t_map_info *data,
	t_collectibles **collect)
{
	while (map)
	{
		while (map->line[point->x] && map->line[point->x] != '\n')
		{
			if ((map->line[point->x] == '0' || map->line[point->x] == 'E'
					|| map->line[point->x] == 'P' || map->line[point->x] == 'C')
				&& (map->prev || map->next))
			{
				if (!place_image(map->line[point->x], point, collect, data))
					return (0);
			}
			else if (map->line[point->x] == '1')
			{
				if (check_surroundings(map, point, data) < 0)
					return (0);
			}
			else
				return (0);
			point->x++;
		}
		*point = (t_point){0, (*point).y + 1, 0, point->ry + data->p_size, 0};
		map = map->next;
	}
	return (1);
}

int	map_maker(t_maplst *map, t_map_info *data)
{
	t_collectibles	*collect;
	t_point			point;

	point = (t_point){0, 0, 0, 0, 0};
	collect = collectibles_struct(map);
	init_img_tab(data);
	if (!map_maker_x(map, &point, data, &collect))
		return (0);
	return (1);
}
// free map ici ou tjs utile plus tard?