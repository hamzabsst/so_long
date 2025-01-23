/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:26:58 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/23 07:56:40 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/home/hbousset/includes/minilibx-linux/mlx.h"
# include "../mylib/myLib.h"
# define MAP_BUFFER_SIZE 1000
# define SIZE 64
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_txr
{
	void	*wall;
	void	*plr;
	void	*item;
	void	*exit;
	void	*empty;
	void	*p_e;
	void	*boss;
}	t_txr;

typedef struct s_boss
{
	int		x;
	int		y;
	int		direction;
	char	previous_tile;
}	t_boss;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	char	**map;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	t_txr	txr;
	int		collectibles;
	int		collected;
	int		won;
	void	*black_bg;
	int		moves;
	int		last_was_exit;
	int		anim_frame;
	int		anim_timer;
	int		frame_count;
	int		frames_per_update;
	void	*pframes[3];
	void	*iframes[3];
	int		boss_x;
	int		boss_y;
	int		boss_direction;
	t_boss	*bosses;
	int		boss_count;
}	t_game;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_render
{
	void	*m;
	void	*w;
	t_game	*g;
}	t_render;

//parsing errors
int		check_map(char *map);
int		is_surronded_by_walls(char **lines);
int		check_sprites(int count_p, int count_e, int count_c);
int		is_rectangular(char **lines);
int		has_valid_characters(char **lines, int *p, int *c, int *e);
int		is_valid_path(char **map);
//window
void	init_window(t_game *game);
void	display_moves(t_game *game);
int		close_window(t_game *game);
//map
char	*read_map(const char *map);
void	render_map(void *mlx, void *w, char **map, t_game *game);
//txr
void	load_txr(void *mlx, t_game *game);
void	init_player_position(t_game *game);
void	init_collectibles(t_game *game);
int		handle_keypress(int keycode, t_game *game);
//cleanup
void	free_split(char **lines);
//bonus
int		update_animation(t_game *game);
void	move_boss(t_game *game);
void	init_bosses(t_game *game);

#endif
