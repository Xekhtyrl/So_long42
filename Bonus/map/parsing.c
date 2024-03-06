/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:07:38 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 17:29:19 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"
#include <fcntl.h>
#include <unistd.h>

static t_maplst	*file_to_list(int fd)
{
	t_maplst	*lst;
	t_maplst	*prev;

	prev = NULL;
	lst = NULL;
	while (1)
	{
		lst = malloc(sizeof(t_maplst));
		if (!lst)
			return (0);
		lst->line = get_next_line(fd);
		if (lst->line == NULL)
			break ;
		lst->prev = prev;
		if (lst->prev)
			lst->prev->next = lst;
		lst->next = NULL;
		prev = lst;
		lst = lst->next;
	}
	lst = prev;
	while (lst->prev)
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
	start = -1;
	if (!check_map_value(map, &info, &start, &start_line))
		return ((t_map_info){0});
	if (!(info.exit))
		return (ft_putstr_fd("no exit", 2), (t_map_info){0});
	info.exit = 0;
	if (start >= 0)
	{
		backtracking(start_line, &info, start);
		if (!info.possible)
			return (ft_putstr_fd("impossible map", 2), (t_map_info){0});
	}
	else
		return (ft_putstr_fd("no player", 2), (t_map_info){0});
	if (info.collectibles != info.tot_collectibles)
		return (ft_putstr_fd("collectibles not collected", 2), (t_map_info){0});
	return (info);
}

void	recalculate_window_size(t_map_info *info)
{
	int	ppt;

	if (WIDTH / info->width < LENGTH / info->length)
		ppt = WIDTH / info->width;
	else
		ppt = LENGTH / info->length;
	(*info).p_size = ppt - 1;
}

t_maplst	*init_parsing(char *file, t_map_info *info)
{
	int				fd;
	t_maplst		*map;
	t_maplst		*map_copy;

	fd = open(file, O_RDONLY);
	map = file_to_list(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	map_copy = file_to_list(fd);
	close(fd);
	*info = parsing(map_copy);
	if (!info->length && !info->width && !info->tot_collectibles)
		return (0);
	recalculate_window_size(info);
	return (map);
}
