/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:26:58 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/20 08:01:23 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../mylib/myLib.h"
# define TILE_SIZE 64
char	*read_map(const char *map);

int		check_map(char *map);
void	free_lines(char **lines);
void	init_map(void *mlx, void *window, char **map);
void	render_map(void *mlx, void *window, char **map,
	void *wall_img, void *player_img, void *collectible_img,
	void *exit_img, void *empty_img);
void cleanup(void *mlx, void *window, char **map, void *wall_img, void *player_img,
			void *collectible_img, void *exit_img, void *empty_img);


#endif
