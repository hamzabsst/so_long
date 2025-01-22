/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:38:45 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 09:14:52 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	init_window(t_game *game)
{
	int	bpp;
	int	size_line;
	int	endian;
	int	*data;
	int	i;

	i = 0;
	game->width = ft_strlen(game->map[0]);
	while (game->map[i])
		i++;
	game->height = i;
	i = 0;
	game->mlx = mlx_init();
	game->last_was_exit = 0;
	game->window = mlx_new_window(game->mlx, game->width * SIZE,
			game->height * SIZE, "so_long");
	game->black_bg = mlx_new_image(game->mlx, 70, 30);
	data = (int *)mlx_get_data_addr(game->black_bg, &bpp, &size_line, &endian);
	while (i < 70 * 30)
	{
		data[i] = 0x000000;
		i++;
	}
	game->moves = 0;
}

int	close_window(t_game *game)
{
	if (game->black_bg)
		mlx_destroy_image(game->mlx, game->black_bg);
	if (game->txr.wall)
		mlx_destroy_image(game->mlx, game->txr.wall);
	if (game->txr.plr)
		mlx_destroy_image(game->mlx, game->txr.plr);
	if (game->txr.item)
		mlx_destroy_image(game->mlx, game->txr.item);
	if (game->txr.exit)
		mlx_destroy_image(game->mlx, game->txr.exit);
	if (game->txr.empty)
		mlx_destroy_image(game->mlx, game->txr.empty);
	if (game->txr.p_e)
		mlx_destroy_image(game->mlx, game->txr.p_e);
	if (game->txr.boss)
		mlx_destroy_image(game->mlx, game->txr.boss);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free_split(game->map);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}
