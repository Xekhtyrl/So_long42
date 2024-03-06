/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:53:24 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/06 15:10:40 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	take_starter_sprites(mlx_t *mlx, int player_info, t_pacmon *player)
{
	char	*path;

	if (player_info == 25)
		path = "./Sprites/Players/bulbasaur/";
	else if (player_info == 125)
		path = "./Sprites/Players/cyndaquil/";
	else if (player_info == 225)
		path = "./Sprites/Players/pikachu/";
	else if (player_info == 325)
		path = "./Sprites/Players/piplup/";
	else
		path = "./Sprites/Players/umbreon/";
	(*player).back = load_player_image(mlx, path, "back.xpm42");
	(*player).front = load_player_image(mlx, path, "front.xpm42");
	(*player).left = load_player_image(mlx, path, "left.xpm42");
	(*player).right = load_player_image(mlx, path, "right.xpm42");
}

static mlx_image_t	*xpm_to_img(xpm_t *xpm, mlx_t *mlx, int i)
{
	mlx_image_t	*img;

	if (!xpm)
		return (perror("cheeeh"), exit(0), NULL);
	img = mlx_texture_to_image(mlx, &(xpm->texture));
	if (i >= 0)
	{
		mlx_image_to_window(mlx, img, i * 100, 200);
		mlx_resize_image(img, 100, 100);
	}
	else
	{
		mlx_image_to_window(mlx, img, 25, 300);
		mlx_resize_image(img, 50, 50);
	}
	mlx_delete_xpm42(xpm);
	return (img);
}

mlx_image_t	*display_choice(mlx_t *mlx, t_menu *menu)
{
	mlx_image_t	*cursor;
	xpm_t		*xpm;

	xpm = mlx_load_xpm42("./Sprites/Players/bulbasaur/front.xpm42");
	menu->all[1] = xpm_to_img(xpm, mlx, 0);
	xpm = mlx_load_xpm42("./Sprites/Players/cyndaquil/front.xpm42");
	menu->all[2] = xpm_to_img(xpm, mlx, 1);
	xpm = mlx_load_xpm42("./Sprites/Players/pikachu/front.xpm42");
	menu->all[3] = xpm_to_img(xpm, mlx, 2);
	xpm = mlx_load_xpm42("./Sprites/Players/piplup/front.xpm42");
	menu->all[4] = xpm_to_img(xpm, mlx, 3);
	xpm = mlx_load_xpm42("./Sprites/Players/umbreon/front.xpm42");
	menu->all[5] = xpm_to_img(xpm, mlx, 4);
	cursor = xpm_to_img(mlx_load_xpm42("./Sprites/pokeball.xpm42"), mlx, -1);
	cursor->instances[0].z = 2;
	return (cursor);
}

int	player_construction(void)
{
	xpm_t		*xpm;
	t_menu		menu;
	int			return_val;

	menu.mlx = mlx_init(500, 500, "pick_starter", true);
	xpm = mlx_load_xpm42("./Sprites/Starter_screen.xpm42");
	menu.all[0] = mlx_texture_to_image(menu.mlx, &(xpm->texture));
	mlx_image_to_window(menu.mlx, menu.all[0], 0, 0);
	mlx_resize_image(menu.all[0], 500, 500);
	mlx_delete_xpm42(xpm);
	menu.cursor = display_choice(menu.mlx, &menu);
	mlx_key_hook(menu.mlx, &hook_menu, &menu);
	mlx_loop(menu.mlx);
	return_val = menu.cursor->instances[0].x;
	mlx_close_hook(menu.mlx, &close_menu, &menu);
	mlx_terminate(menu.mlx);
	return (return_val);
}
