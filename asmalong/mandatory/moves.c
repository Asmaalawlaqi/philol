/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:00:21 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:04:59 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	flag_1_moves(t_game *game, int next_x, int next_y)
{
	if (game->map[next_y][next_x] == '0')
	{
		game->map[next_y][next_x] = 'P';
		game->map[game->p_pos_y][game->p_pos_x] = 'E';
		game->flag = 2;
	}
	if (game->map[next_y][next_x] == 'C')
	{
		game->collectible--;
		game->map[next_y][next_x] = 'P';
		game->map[game->p_pos_y][game->p_pos_x] = 'E';
		game->flag = 2;
	}
	if (game->map[next_y][next_x] == 'E')
	{
		game->map[next_y][next_x] = 'P';
		game->map[game->p_pos_y][game->p_pos_x] = 'E';
		game->flag = 3;
	}
}

void	flag_0_moves(t_game *game, int next_x, int next_y)
{
	if (game->map[next_y][next_x] == '0')
	{
		game->map[next_y][next_x] = 'P';
		game->map[game->p_pos_y][game->p_pos_x] = '0';
	}
	if (game->map[next_y][next_x] == 'C')
	{
		game->collectible--;
		game->map[next_y][next_x] = 'P';
		game->map[game->p_pos_y][game->p_pos_x] = '0';
	}
}

void	next_move(t_game *game, int x, int y)
{
	int	next_x;
	int	next_y;

	next_x = game->p_pos_x + x;
	next_y = game->p_pos_y + y;
	if (game->map[next_y][next_x] == '1')
		return ;
	if (game->flag == 0)
		flag_0_moves(game, next_x, next_y);
	if (game->flag == 1)
		flag_1_moves(game, next_x, next_y);
	exiting_game(game, next_x, next_y);
	rendering_move(game, next_x, next_y);
	ft_printf("step %d\n", ++(game->steps));
}

int	player_moves(int key, t_game *game)
{
	if (key == 13)
		next_move(game, 0, -1);
	if (key == 1)
		next_move(game, 0, 1);
	if (key == 0)
		next_move(game, -1, 0);
	if (key == 2)
		next_move(game, 1, 0);
	if (key == 53)
		closing_window(game);
	return (0);
}
