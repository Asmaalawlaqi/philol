/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:04:02 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:21:06 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	closing_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	mlx_destroy_window(game->mlx, game->mlx_win);
	map_error(game, "<<< thank you !!! >>>");
	exit(0);
}

void	map_error(t_game *game, char *s)
{
	int	i;

	i = 0;
	ft_printf("%s\n", s);
	while (game->map[i] != NULL)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(1);
}

void	temp_map_error(char *tempmap, char *s)
{
	ft_printf("%s\n", s);
	free(tempmap);
	exit(1);
}

void	ft_error(char *s)
{
	ft_printf("%s\n", s);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.w = 0;
	game.h = 0;
	game.collectible = 0;
	game.flag = 0;
	game.find_e = 0;
	game.find_c = 0;
	game.p_pos_x = 0;
	game.p_pos_y = 0;
	game.steps = 0;
	if (argc != 2)
		ft_error("Error\n Add map or check start command!\n");
	ft_parsing(&game, argv[1]);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	rendering_map(&game);
	valid_exitpass(&game);
	mlx_key_hook(game.mlx_win, player_moves, &game);
	mlx_hook(game.mlx_win, 17, 0, closing_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
