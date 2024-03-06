/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:29:10 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 15:10:29 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static char	*wall_file_str(int clue) // !!! resort qqch d'allouer
{
	char	*final;
	char	*p1;
	char	*itoa;

	itoa = ft_itoa(clue);
	p1 = ft_strjoin("./Sprites/Background/wall", itoa);
	free(itoa);
	final = ft_strjoin(p1, ".xpm42");
	free(p1);
	return (final);
}

// xpm = mlx_load_xpm42("./Sprites/Players/grumpy.xpm42");
static int	choose_wall(int clue, t_point *point, t_map_info *data)
{
	xpm_t		*xpm;
	char		*file_wall;

	file_wall = (wall_file_str(clue));
	xpm = mlx_load_xpm42((const char *)file_wall);
	if (!xpm)
		return (perror(file_wall), 0);
	xpm_to_image(data, xpm, *point, 10);
	point->rx += data->p_size;
	return (1);
}

static void	check_borders(t_maplst *lines, t_point point, int *i)
{
	if (lines->prev && point.x && lines->line[point.x - 1] == '1'
		&& lines->prev->line[point.x] == '1' && lines->prev->line[point.x
			- 1] == '1')
		*i += 64;
	if (lines->prev && lines->prev->line[point.x] == '1' && lines->line[point.x
			+ 1] == '1' && lines->prev->line[point.x + 1] == '1')
		*i += 128;
	if (!lines->line[point.x + 1] || lines->line[point.x + 1] == '\n')
		*i += 256;
	if (!lines->next)
		*i += 512;
	if (point.x == 0)
		*i += 1024;
	if (!lines->prev)
		*i += 2048;
}

int	check_surroundings(t_maplst *lines, t_point *point, t_map_info *data)
{
	int	clue;

	clue = 0;
	if (lines->line[point->x + 1] == '1')
		clue += 1;
	if (lines->next && lines->next->line[point->x] == '1')
		clue += 2;
	if (point->x > 0 && lines->line[point->x - 1] == '1')
		clue += 4;
	if (lines->prev && lines->prev->line[point->x] == '1')
		clue += 8;
	if (lines->next && lines->line[point->x + 1] == '1'
		&& lines->next->line[point->x] == '1' && lines->next->line[point->x + 1]
		== '1')
		clue += 16;
	if (lines->next && point->x && lines->next->line[point->x] == '1'
		&& lines->line[point->x - 1] == '1' && lines->next->line[point->x - 1]
		== '1')
		clue += 32;
	check_borders(lines, *point, &clue);
	return (choose_wall(clue, point, data));
}
