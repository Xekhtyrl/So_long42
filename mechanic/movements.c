/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:17:44 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/12 20:42:27 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	refresh_player(t_pacmon	*player)
{
	player->front->instances[0].enabled = false;
	player->right->instances[0].enabled = false;
	player->left->instances[0].enabled = false;
	player->back->instances[0].enabled = false;
}

void	move_up(t_pacmon *player, t_map_info *data)
{
	refresh_player(player);
	player->back->instances[0].y -= data->p_size / 4;
	player->front->instances[0].y -= data->p_size / 4;
	player->right->instances[0].y -= data->p_size / 4;
	player->left->instances[0].y -= data->p_size / 4;
	player->back->instances[0].enabled = true;
}

void	move_down(t_pacmon *player, t_map_info *data)
{
	refresh_player(player);
	player->back->instances[0].y += data->p_size / 4;
	player->front->instances[0].y += data->p_size / 4;
	player->right->instances[0].y += data->p_size / 4;
	player->left->instances[0].y += data->p_size / 4;
	player->front->instances[0].enabled = true;
}

void	move_right(t_pacmon *player, t_map_info *data)
{
	refresh_player(player);
	player->back->instances[0].x += data->p_size / 4;
	player->right->instances[0].x += data->p_size / 4;
	player->front->instances[0].x += data->p_size / 4;
	player->left->instances[0].x += data->p_size / 4;
	player->right->instances[0].enabled = true;
}

void	move_left(t_pacmon *player, t_map_info *data)
{
	refresh_player(player);
	player->back->instances[0].x -= data->p_size / 4;
	player->front->instances[0].x -= data->p_size / 4;
	player->right->instances[0].x -= data->p_size / 4;
	player->left->instances[0].x -= data->p_size / 4;
	player->left->instances[0].enabled = true;
}
