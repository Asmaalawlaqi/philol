/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:04:10 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/29 10:42:02 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "minilibx/mlx.h"
# include <fcntl.h>

# define SPACE		"img/space.xpm"
# define WALL		"img/wall.xpm"
# define PLAYER		"img/player.xpm"
# define COIN		"img/coin.xpm"
# define EXIT		"img/exit.xpm"

typedef struct s_game
{
	int		w;
	int		h;
	char	**map;
	int		collectible;
	int		flag;
	char	hash_map[256][256];
	int		find_e;
	int		find_c;
	int		p_pos_x;
	int		p_pos_y;
	int		steps;
	void	*mlx;
	void	*mlx_win;
	void	*img;
}	t_game;

void	ft_error(char *string);
void	temp_map_error(char *tempmap, char *string);
void	map_error(t_game *game, char *string);

char	*get_next_line(int fd);
int		gnl_strlen(char *s);
char	*gnl_strchr(char *s);
char	*gnl_strdup(char *remainder);
char	*gnl_strjoin(char *old, char *new);

void	ft_parsing(t_game *game, char *file);
void	ft_check_file_extension(char *file);
char	*ft_read_map(char *file);
void	ft_check_map(t_game *game, char *read_map);
void	check_walls(t_game *game);
void	game_elements(t_game *game);
int		count_game_elem(t_game *game, char c);
void	check_map_chars(t_game *game);

void	rendering_map(t_game *game);
void	rendering_win(t_game *game);
void	locate_items_and_put_img(t_game *game, char c, int x, int y);
void	rendering_img(t_game *game, char *path, int x, int y);

void	valid_exitpass(t_game *game);
void	scanning_map(t_game *game, int x, int y);
int		scan_exitpass(t_game *game, int x, int y);

int		player_moves(int key, t_game *game);
void	next_move(t_game *game, int x, int y);
void	flag_0_moves(t_game *game, int next_x, int next_y);
void	flag_1_moves(t_game *game, int next_x, int next_y);
void	exiting_game(t_game *game, int next_x, int next_y);
void	rendering_move(t_game *game, int next_x, int next_y);
void	ft_if_flag2_flag3_render(t_game *game, int next_x, int next_y);
int		closing_window(t_game *game);

#endif
