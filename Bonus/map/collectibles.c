/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:30:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 15:10:13 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	choose_collectible(t_map_info *data, t_collectibles **collect,
		t_point point)
{
	if (*collect && (*collect)->left > 0)
		(*collect)->left -= 1;
	if ((*collect)->nbr > 8 && (*collect)->left >= 0 && (((*collect)->left)
			% (int)((*collect)->nbr / 8)))
		xpm_to_image(data,
			mlx_load_xpm42("./Sprites/Collectibles/Rare_Candy.xpm42"),
			point, 1);
	else
	{
		while (point.z++ < 9)
		{
			if ((*collect)->unused)
				break ;
			*collect = (*collect)->next;
		}
		if ((*collect)->unused)
		{
			xpm_to_image(data, (*collect)->badges, point, 1);
			(*collect)->unused = 0;
		}
		else
			xpm_to_image(data,
				mlx_load_xpm42("./Sprites/Collectibles/Rare_Candy.xpm42"),
				point, 1);
	}
}

static xpm_t	*pick_collect_text(int i)
{
	xpm_t	*xpm;

	if (i == 0)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/BoulderB.xpm42");
	else if (i == 1)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/CascadeB.xpm42");
	else if (i == 2)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/EarthB.xpm42");
	else if (i == 3)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/MarshB.xpm42");
	else if (i == 4)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/RainbowB.xpm42");
	else if (i == 5)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/SoulB.xpm42");
	else if (i == 6)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/ThunderB.xpm42");
	else if (i == 7)
		xpm = mlx_load_xpm42("./Sprites/Collectibles/VolcanoB.xpm42");
	else
		return (0);
	return (xpm);
}

static t_collectibles	*new_collect(int count, int i)
{
	t_collectibles	*new;

	new = malloc(sizeof(t_collectibles));
	if (!new)
		return (0);
	new->badges = pick_collect_text(i);
	new->left = count;
	new->nbr = count;
	new->unused = i + 1;
	new->next = NULL;
	return (new);
}

static void	put_endlist_coll(t_collectibles **coll, t_collectibles *new)
{
	t_collectibles	*last;

	last = *coll;
	if (!*coll)
	{
		*coll = new;
		return ;
	}
	while (last->next != 0)
		last = last->next;
	last->next = new;
}

t_collectibles	*collectibles_struct(t_maplst *map)
{
	int				i;
	int				count;
	t_collectibles	*collect;
	t_collectibles	*start;

	i = 0;
	count = count_collect(map);
	start = 0;
	while (i < 8)
	{
		collect = new_collect(count, i);
		put_endlist_coll(&start, collect);
		i++;
	}
	collect->next = start;
	return (start);
}
