/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_moveset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:57:52 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/12 22:00:35 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	sableye_moveset(t_map_info *data, t_pacmon *mob, int key)
{
	static int	r;
	static int	count;

	if (data->possible <= 1)
		count = 0;
	count++;
	r = update_rand(r, count);
	(void)key;
	if (r % 4 == 0 && !next_step_is_wall(*data, mob->front->instances[0],
			MLX_KEY_D) && !next_step_is_mob(*data, mob, MLX_KEY_D))
		return (move_right(mob, data));
	if ((r % 4 == 1) && !next_step_is_wall(*data, mob->right->instances[0],
			MLX_KEY_S) && !next_step_is_mob(*data, mob, MLX_KEY_S))
		return (move_down(mob, data));
	if ((r % 4 == 2) && !next_step_is_wall(*data, mob->left->instances[0],
			MLX_KEY_A) && !next_step_is_mob(*data, mob, MLX_KEY_A))
		return (move_left(mob, data));
	if ((r % 4 == 3) && !next_step_is_wall(*data, mob->back->instances[0],
			MLX_KEY_W) && !next_step_is_mob(*data, mob, MLX_KEY_W))
		return (move_up(mob, data));
	r++;
}

void	duskull_moveset(t_map_info *data, t_pacmon *mob, int key)
{
	static int	r;
	static int	count4;

	if (data->possible <= 1)
		count4 = 0;
	count4++;
	r = update_rand(r, count4);
	(void)key;
	if (r % 4 == 3 && !next_step_is_wall(*data, mob->front->instances[0],
			MLX_KEY_D) && !next_step_is_mob(*data, mob, MLX_KEY_D))
		return (move_right(mob, data));
	if ((r % 4 == 2) && !next_step_is_wall(*data, mob->right->instances[0],
			MLX_KEY_S) && !next_step_is_mob(*data, mob, MLX_KEY_S))
		return (move_down(mob, data));
	if ((r % 4 == 1) && !next_step_is_wall(*data, mob->left->instances[0],
			MLX_KEY_A) && !next_step_is_mob(*data, mob, MLX_KEY_A))
		return (move_left(mob, data));
	if ((r % 4 == 0) && !next_step_is_wall(*data, mob->back->instances[0],
			MLX_KEY_W) && !next_step_is_mob(*data, mob, MLX_KEY_W))
		return (move_up(mob, data));
	r++;
}

void	gastly_moveset(t_map_info *data, t_pacmon *mob, int key)
{
	static int	r;
	static int	count3;

	if (data->possible <= 1)
		count3 = 0;
	count3++;
	r = update_rand(r, count3);
	(void)key;
	if (r % 4 == 3 && !next_step_is_wall(*data, mob->front->instances[0],
			MLX_KEY_D) && !next_step_is_mob(*data, mob, MLX_KEY_D))
		return (move_right(mob, data));
	if ((r % 4 == 2) && !next_step_is_wall(*data, mob->right->instances[0],
			MLX_KEY_S) && !next_step_is_mob(*data, mob, MLX_KEY_S))
		return (move_down(mob, data));
	if ((r % 4 == 1) && !next_step_is_wall(*data, mob->left->instances[0],
			MLX_KEY_A) && !next_step_is_mob(*data, mob, MLX_KEY_A))
		return (move_left(mob, data));
	if ((r % 4 == 0) && !next_step_is_wall(*data, mob->back->instances[0],
			MLX_KEY_W) && !next_step_is_mob(*data, mob, MLX_KEY_W))
		return (move_up(mob, data));
	r++;
}

void	haunter_moveset(t_map_info *data, t_pacmon *mob, int key)
{
	static int	r;
	static int	count2;

	if (data->possible <= 1)
		count2 = 0;
	count2++;
	r = update_rand(r, count2);
	(void)key;
	if (r % 4 == 0 && !next_step_is_wall(*data, mob->front->instances[0],
			MLX_KEY_D) && !next_step_is_mob(*data, mob, MLX_KEY_D))
		return (move_right(mob, data));
	if ((r % 4 == 1) && !next_step_is_wall(*data, mob->right->instances[0],
			MLX_KEY_S) && !next_step_is_mob(*data, mob, MLX_KEY_S))
		return (move_down(mob, data));
	if ((r % 4 == 2) && !next_step_is_wall(*data, mob->left->instances[0],
			MLX_KEY_A) && !next_step_is_mob(*data, mob, MLX_KEY_A))
		return (move_left(mob, data));
	if ((r % 4 == 3) && !next_step_is_wall(*data, mob->back->instances[0],
			MLX_KEY_W) && !next_step_is_mob(*data, mob, MLX_KEY_W))
		return (move_up(mob, data));
	r++;
}

void	yamask_moveset(t_map_info *data, t_pacmon *mob, int key)
{
	static int	r;
	static int	count1;

	if (data->possible <= 1)
		count1 = 0;
	count1++;
	r = update_rand(r, count1);
	(void)key;
	if (r % 4 == 0 && !next_step_is_wall(*data, mob->front->instances[0],
			MLX_KEY_D) && !next_step_is_mob(*data, mob, MLX_KEY_D))
		return (move_right(mob, data));
	if ((r % 4 == 1) && !next_step_is_wall(*data, mob->right->instances[0],
			MLX_KEY_S) && !next_step_is_mob(*data, mob, MLX_KEY_S))
		return (move_down(mob, data));
	if ((r % 4 == 2) && !next_step_is_wall(*data, mob->left->instances[0],
			MLX_KEY_A) && !next_step_is_mob(*data, mob, MLX_KEY_A))
		return (move_left(mob, data));
	if ((r % 4 == 3) && !next_step_is_wall(*data, mob->back->instances[0],
			MLX_KEY_W) && !next_step_is_mob(*data, mob, MLX_KEY_W))
		return (move_up(mob, data));
	r++;
}
