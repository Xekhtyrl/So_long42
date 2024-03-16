/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:07:38 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 21:32:02 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"
#include <fcntl.h>
#include <unistd.h>

static t_maplst	*file_to_list(int fd)
{
	t_maplst	*lst;
	t_maplst	*prev;
	char		*temp;

	prev = NULL;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		lst = malloc(sizeof(t_maplst));
		if (!lst)
			return (0);
		lst->line = temp;
		lst->prev = prev;
		if (lst->prev)
			lst->prev->next = lst;
		lst->next = NULL;
		prev = lst;
		lst = lst->next;
	}
	lst = prev;
	while (lst && lst->prev)
		lst = lst->prev;
	return (lst);
}

int	count_collect(t_maplst *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map)
	{
		i = 0;
		while (map->line[i] && map->line[i] != '\n')
			if (map->line[i++] == 'C')
				count++;
		map = map->next;
	}
	return (count);
}

static t_map_info	parsing(t_maplst *map)
{
	int			start;
	t_maplst	*start_line;
	t_map_info	info;

	info = (t_map_info){0};
	info.tot_collectibles = count_collect(map);
	if (!info.tot_collectibles)
		return (ft_putstr_fd(ERR_NOCOLL, 2), (t_map_info){0});
	start = -1;
	if (!check_map_value(map, &info, &start, &start_line))
		return ((t_map_info){0});
	if (!(info.exit))
		return (ft_putstr_fd("Error\nnExit not found!\n", 2), (t_map_info){0});
	info.exit = 0;
	if (start >= 0)
	{
		backtracking(start_line, &info, start);
		if (!info.possible)
			return (ft_putstr_fd("Error\nImpossiburu map\n", 2), (t_map_info){0});
	}
	else
		return (ft_putstr_fd("Error\nPlayer not founded!\n", 2), (t_map_info){0});
	if (info.collectibles != info.tot_collectibles)
		return (ft_putstr_fd(ERR_IMP_COLL, 2), (t_map_info){0});
	return (info);
}

void	recalculate_window_size(t_map_info *info)
{
	int	ppt;

	if (WIDTH / info->width < LENGTH / info->length)
		ppt = WIDTH / info->width;
	else
		ppt = LENGTH / info->length;
	(*info).p_size = ppt - ppt % 4;
}

t_maplst	*init_parsing(char *file, t_map_info *info)
{
	int				fd;
	t_maplst		*map;
	t_maplst		*map_copy;

	if (!ft_strnstr(file + (ft_strlen(file) - 4), ".ber", 4))
		return (perror("Error\nMap not found"), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nMap not found"), NULL);
	map = file_to_list(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	map_copy = file_to_list(fd);
	close(fd);
	*info = parsing(map_copy);
	if (!info->length && !info->width && !info->tot_collectibles)
		return (free_map(&map_copy), free_map(&map), NULL);
	info->mobs_img = ft_calloc(sizeof(t_pacmon), info->mobs_count);
	if (!info->mobs_img)
		return (free_map(&map_copy), free_map(&map), NULL);
	recalculate_window_size(info);
	free_map(&map_copy);
	return (map);
}
