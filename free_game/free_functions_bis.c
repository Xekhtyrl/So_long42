/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:25:30 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/15 21:00:46 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_coll_lst(t_collectibles **lst)
{
	t_collectibles	*temp;
	t_collectibles	*temp2;
	int				i;

	i = 0;
	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (i++ < 8)
	{
		temp2 = temp->next;
		if (temp->unused)
			mlx_delete_xpm42(temp->badges);
		free(temp);
		temp = temp2;
	}
	*lst = 0;
}
