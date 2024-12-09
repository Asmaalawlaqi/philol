/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:59:50 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/18 12:04:59 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_check_map(t_game *game, char *read_map)
{
	int	i;

	i = 0;
	if (read_map[0] == '\n' || read_map[(ft_strlen(read_map) - 1)] == '\n')
		ft_error("Error\n Map not valid!");
	game->map = ft_split(read_map, '\n');
	game->w = ft_strlen(game->map[0]);
	while (game->map[++i])
	{
		if (ft_strlen(game->map[i]) != game->w)
			map_error(game, "Error\n Map invalid\n");
	}
	game->h = i;
}

char	*ft_read_map(char *file)
{
	int		fd;
	char	*read_map;
	char	*temp_map;

	read_map = "";
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error\n Can't read map\n");
	temp_map = get_next_line(fd);
	if (temp_map == NULL)
		temp_map_error(temp_map, "Error\n Map invalid\n");
	while (temp_map != NULL)
	{
		if (temp_map != NULL && temp_map[0] == '\n')
			temp_map_error(temp_map, "Error\n Map invalid\n");
		read_map = ft_strjoin(read_map, temp_map);
		temp_map = get_next_line(fd);
	}
	if (temp_map != NULL)
		free(temp_map);
	close (fd);
	return (read_map);
}

void	ft_check_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 1] != 'r' && file[len - 2] != 'e'
		&& file[len - 3] != 'b' && file[len - 4] != '.')
		ft_error("Error\n Invalid Map\n");
}

void	ft_parsing(t_game *game, char *file)
{
	ft_check_file_extension(file);
	ft_check_map(game, ft_read_map(file));
	check_walls(game);
	game_elements(game);
	check_map_chars(game);
}
