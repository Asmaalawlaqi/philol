/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:00:04 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:04:59 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	rendering_img(t_game *game, char *path, int x, int y)
{
	int	size;

	size = 100;
	x = x * size;
	y = y * size;
	game->img = mlx_xpm_file_to_image(game->mlx, path, &size, &size);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, x, y);
	mlx_destroy_image(game->mlx, game->img);
}

void	locate_items_and_put_img(t_game *game, char c, int x, int y)
{
	if (c == '0')
		rendering_img(game, SPACE, x, y);
	if (c == '1')
	{
		rendering_img(game, SPACE, x, y);
		rendering_img(game, WALL, x, y);
	}
	if (c == 'P')
	{
		game->p_pos_x = x;
		game->p_pos_y = y;
		rendering_img(game, SPACE, x, y);
		rendering_img(game, PLAYER, x, y);
	}
	if (c == 'C')
	{
		rendering_img(game, SPACE, x, y);
		rendering_img(game, COIN, x, y);
	}
	if (c == 'E')
	{
		rendering_img(game, SPACE, x, y);
		rendering_img(game, EXIT, x, y);
	}
}

void	rendering_win(t_game *game)
{
	int	win_wid;
	int	win_hgt;

	win_wid = game->w * 100;
	win_hgt = game->h * 100;
	game->mlx_win = mlx_new_window(game->mlx, win_wid, win_hgt, "SO_LONG");
}

void	rendering_map(t_game *game)
{
	int	x;
	int	y;

	rendering_win(game);
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			locate_items_and_put_img(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
