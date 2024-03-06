/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:28:22 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 15:28:10 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	change_char_path(t_maplst *map, t_map_info *info, int i)
{
	if (map->line[i] == '0' || map->line[i] == 'P' || map->line[i] == 'G')
		map->line[i] = '.';
	else if (map->line[i] == 'C')
	{
		map->line[i] = '.';
		info->collectibles++;
	}
	else if (map->line[i] == 'E')
	{
		map->line[i] = '.';
		info->exit++;
	}
}

int	backtracking(t_maplst *map, t_map_info *info, int i)
{
	if (info->collectibles != info->tot_collectibles || !info->exit)
	{
		change_char_path(map, info, i);
		if (map->line[i + 1] != '1' && map->line[i + 1] != '.')
			backtracking(map, info, i + 1);
		if (map->line[i - 1] != '1' && map->line[i - 1] != '.')
			backtracking(map, info, i - 1);
		if (map->prev->line[i] != '1' && map->prev->line[i] != '.')
			backtracking(map->prev, info, i);
		if (map->next->line[i] != '1' && map->next->line[i] != '.')
			backtracking(map->next, info, i);
		else
			return (0);
	}
	if (info->collectibles == info->tot_collectibles && info->exit)
		info->possible = 1;
	return (1);
}

static int	check_map_line(t_maplst *map, t_map_info *info, int *start,
			t_maplst **start_line)
{
	int	i;

	i = 0;
	while (map->line[i] != '\n' && map->line[i])
	{
		if ((!map->prev || !map->next || i == 0 || i == info->width)
			&& map->line[i] != '1')
			return (perror("border not full"), -1);
		else if (map->line[i] == 'E' && (info->exit)++ > 1)
			return (perror("too many exit"), -1);
		else if (map->line[i] == 'G')
			info->mobs_count++;
		if (map->line[i++] == 'P' && *start == -1)
		{
			*start_line = map;
			*start = i - 1;
		}
		else if (map->line[i - 1] == 'P' && *start != -1)
			return (perror("too many players"), -1);
	}
	return (i);
}

int	check_map_value(t_maplst *map, t_map_info *info, int *start,
			t_maplst **start_line)
{
	int	i;

	while (map)
	{
		i = check_map_line(map, info, start, start_line);
		if (i == -1)
			return (0);
		if (++(info->length) && info->width == 0)
			info->width = i;
		else if (info->width != i)
			return (perror("map not rectangular"), 0);
		map = map->next;
	}
	return (1);
}
