/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pass_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:15:20 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:04:59 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	scan_exitpass(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return (0);
	if (game->hash_map[y][x] == '1')
		return (0);
	return (1);
}

void	scanning_map(t_game *game, int x, int y)
{
	game->hash_map[y][x] = '1';
	if (game->map[y][x] == 'E')
		game->find_e = 1;
	if (game->map[y][x] == 'C')
		game->find_c++;
	if (scan_exitpass(game, x, y - 1) == 1)
		scanning_map(game, x, y - 1);
	if (scan_exitpass(game, x + 1, y) == 1)
		scanning_map(game, x + 1, y);
	if (scan_exitpass(game, x, y + 1) == 1)
		scanning_map(game, x, y + 1);
	if (scan_exitpass(game, x - 1, y) == 1)
		scanning_map(game, x - 1, y);
}

void	valid_exitpass(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			game->hash_map[y][x] = '0';
			x++;
		}
		y++;
	}
	x = game->p_pos_x;
	y = game->p_pos_y;
	scanning_map(game, x, y);
	if (game->find_e != 1 || \
		game->find_c != game->collectible)
		map_error(game, "Error\n Map invalid\n");
}
