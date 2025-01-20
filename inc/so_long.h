/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:26:58 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/20 11:01:16 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../mylib/myLib.h"
# define SIZE 64

typedef struct s_txr
{
	void	*wall;
	void	*plr;
	void	*item;
	void	*exit;
	void	*empty;
}	t_txr;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	char	**map;
	t_txr	textures;
}	t_game;

typedef struct s_point
{
	int x;
	int y;
}	t_point;

//map
char	*read_map(const char *map);
int		check_map(char *map);
int		is_valid_path(char **map);
void	init_map(void *mlx, void *window, char **map);
void	render_map(void *mlx, void *window, char **map, t_txr *textures);
void	free_split(char **lines);

#endif
