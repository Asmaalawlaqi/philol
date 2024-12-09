/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:02:28 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:04:59 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_map_chars(t_game *game)
{
	int		i;
	int		k;
	char	ch;

	i = 0;
	while (game->map[i])
	{
		k = 0;
		while (game->map[i][k])
		{
			ch = game->map[i][k];
			if (ch != 'P' && ch != 'C' && ch != 'E' && ch != '0' && ch != '1')
				map_error(game, "Error\n Invalid simbol(s) on the map!");
			k++;
		}
		i++;
	}
}

int	count_game_elem(t_game *game, char c)
{
	int	y;
	int	x;
	int	num;

	y = 0;
	num = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == c)
				num++;
			x++;
		}
		y++;
	}
	return (num);
}

void	game_elements(t_game *game)
{
	game->collectible = count_game_elem(game, 'C');
	if (game->collectible < 1)
		map_error(game, "Error\n There must be 1 or more Coins on the map!");
	if (count_game_elem(game, 'P') != 1)
		map_error(game, "Error\n There must be only 1 Player on the map!");
	if (count_game_elem(game, 'E') < 1)
		map_error(game, "Error\n There must be 1 or more Exits on the map!");
}

void	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1')
			map_error(game, "Error\n The Upper boundary isn`t correct!");
		if (game->map[game->h - 1][i] != '1')
			map_error(game, "Error\n The Lower boundary isn`t correct!");
		i++;
	}
	i = 1;
	while (game->map[i])
	{
		if (game->map[i][0] != '1')
			map_error(game, "Error\n The Left boundary isn`t correct!");
		if (game->map[i][game->w - 1] != '1')
			map_error(game, "Error\n The Right boundary isn`t correct!");
		i++;
	}
}
