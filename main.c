/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:24:20 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/16 18:24:59 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_maplst	*map;
	t_map_info	info;
	t_pacmon	player;
	int			player_info;

	map = init_parsing(argv[argc - 1], &info);
	if (!map)
		return (0);
	player_info = player_construction();
	info.mlx = mlx_init(info.p_size * info.width, info.p_size * info.length,
			"Game", true);
	take_starter_sprites(info.mlx, player_info, &player);
	info.player = &player;
	map_maker(map, &info);
	free_map(&map);
	mlx_loop_hook(info.mlx, &hook_movements, &info);
	mlx_loop(info.mlx);
	info.collectibles = info.tot_collectibles;
	free_game(&info, &(t_point){0}, 1);
	mlx_terminate(info.mlx);
}
