/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:27:01 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/21 14:54:43 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

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
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free_split(game->map);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_game	game;
	char	*map;

	if (ac != 2)
		return (write(2, "Error: invalid number of arguments\n", 35));
	map = read_map(av[1]);
	if (!map)
		return (write(2, "Error: failed to read map\n", 26));
	if (check_map(map))
		return (free(map), 1);
	game.map = ft_split(map, '\n');
	free(map);
	init_window(&game);
	init_map(game.mlx, &game);
	init_player_position(&game);
	init_collectibles(&game);
	mlx_hook(game.window, 2, 1L, handle_keypress, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}

void	init_window(t_game *game)
{
	int	height;
	int	bpp;
	int	size_line;
	int	endian;
	int	*data;
	int	i;

	i = 0;
	height = 0;
	game->width = ft_strlen(game->map[0]);
	while (game->map[height])
		height++;
	game->height = height;
	game->mlx = mlx_init();
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
