/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:02:14 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:04:59 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_if_flag2_flag3_render(t_game *game, int next_x, int next_y)
{
	if (game->flag == 2)
	{
		rendering_img(game, SPACE, next_x, next_y);
		rendering_img(game, PLAYER, next_x, next_y);
		rendering_img(game, EXIT, game->p_pos_x, game->p_pos_y);
		game->p_pos_x = next_x;
		game->p_pos_y = next_y;
		game->flag = 0;
	}
	if (game->flag == 3)
	{
		rendering_img(game, EXIT, next_x, next_y);
		rendering_img(game, PLAYER, next_x, next_y);
		rendering_img(game, EXIT, game->p_pos_x, game->p_pos_y);
		game->p_pos_x = next_x;
		game->p_pos_y = next_y;
		game->flag = 1;
	}
}

void	rendering_move(t_game *game, int next_x, int next_y)
{
	if (game->flag == 0)
	{
		rendering_img(game, SPACE, next_x, next_y);
		rendering_img(game, PLAYER, next_x, next_y);
		rendering_img(game, SPACE, game->p_pos_x, game->p_pos_y);
		game->p_pos_x = next_x;
		game->p_pos_y = next_y;
	}
	if (game->flag == 1)
	{
		rendering_img(game, EXIT, next_x, next_y);
		rendering_img(game, PLAYER, next_x, next_y);
		rendering_img(game, SPACE, game->p_pos_x, game->p_pos_y);
		game->p_pos_x = next_x;
		game->p_pos_y = next_y;
	}
	ft_if_flag2_flag3_render(game, next_x, next_y);
}

void	exiting_game(t_game *game, int next_x, int next_y)
{
	if (game->map[next_y][next_x] == 'E' && game->collectible == 0)
		closing_window(game);
	if (game->map[next_y][next_x] == 'E' && game->collectible > 0)
	{
		game->flag = 1;
		game->map[next_y][next_x] = 'P';
		game->map[game->p_pos_y][game->p_pos_x] = '0';
	}
}
