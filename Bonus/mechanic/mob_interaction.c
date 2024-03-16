/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_interaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:54 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 16:30:44 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static t_point	*get_g_point(char *name, t_pacmon *mobs, int count, int p_size)
{
	t_point	*tab;
	int		i;
	int		j;

	if (!name)
		count++;
	tab = malloc(sizeof(t_point) * count - 1);
	if (!tab)
		return (0);
	i = 0;
	j = 0;
	while (i < count - 1)
	{
		if (!name || ft_memcmp(name, mobs[j].name, ft_strlen(name)))
		{
			tab[i] = (t_point){mobs[j].front->instances[0].x,
				mobs[j].front->instances[0].y, 0, 0, 0};
			tab[i].rx = tab[i].x + p_size - 1;
			tab[i].ry = tab[i].y + p_size - 1;
			i++;
		}
		j++;
	}
	return (tab);
}

static int	mob_collision(t_point *tab, t_point g, int dir, t_map_info data)
{
	int	j;

	j = -1;
	while (++j < data.mobs_count - 1)
	{
		if (!(tab[j].x == g.x && tab[j].y == g.y))
		{
			if (dir == MLX_KEY_W && (g.y - data.p_size == tab[j].y
					&& (g.x >= tab[j].x && g.x <= tab[j].rx))) 
				return (1);
			else if (dir == MLX_KEY_S && (g.y + data.p_size == tab[j].y
					&& (g.x >= tab[j].x && g.x <= tab[j].rx)))
				return (1);
			else if (dir == MLX_KEY_A && ((g.y >= tab[j].y && g.y <= tab[j].ry)
					&& g.x == tab[j].x - data.p_size))
				return (1);
			else if (dir == MLX_KEY_D && ((g.y >= tab[j].y && g.y <= tab[j].ry)
					&& g.x == tab[j].x + data.p_size))
				return (1);
		}
	}
	return (0);
}

int	next_step_is_mob(t_map_info data, t_pacmon *mob, int dir)
{
	t_point	g;
	t_point	*tab;
	int		i;

	tab = get_g_point(mob->name, data.mobs_img, data.mobs_count, data.p_size);
	if (!tab)
		return (0);
	i = -1;
	g = (t_point){mob->back->instances[0].x, mob->back->instances[0].y, 0, 0,
		0};
	g.rx = g.x + data.p_size - 1;
	g.ry = g.y + data.p_size - 1;
	while (++i < data.mobs_count - 1)
		if (mob_collision(tab, g, dir, data))
			return (free(tab), 1);
	free(tab);
	return (0);
}

int	mob_hit(mlx_instance_t player, t_pacmon *mobs, int p_size, int mob_count)
{
	t_point	p;
	t_point	*mob;
	int		i;

	p = (t_point){player.x, player.y, player.x + p_size, player.y + p_size, 0};
	mob = get_g_point(NULL, mobs, mob_count, p_size);
	i = -1;
	while (++i < mob_count)
	{
		if (p.x <= mob[i].rx && p.x >= mob[i].x && p.y <= mob[i].ry && p.y
			>= mob[i].y)
			return (free(mob), 1);
		if (p.x <= mob[i].rx && p.x >= mob[i].x && p.ry >= mob[i].y && p.ry
			<= mob[i].ry)
			return (free(mob), 1);
		if (p.rx >= mob[i].x && p.rx <= mob[i].rx && p.y <= mob[i].ry && p.y
			>= mob[i].y)
			return (free(mob), 1);
		if (p.rx >= mob[i].x && p.rx <= mob[i].rx && p.ry >= mob[i].y && p.ry
			<= mob[i].ry)
			return (free(mob), 1);
	}
	return (free(mob), 0);
}
