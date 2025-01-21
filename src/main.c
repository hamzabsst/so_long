/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:27:01 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/21 08:11:53 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

int	close_window(t_game *game)
{
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
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 800, 600, "so_long");
	game.map = ft_split(map, '\n');
	free(map);
	init_map(game.mlx, &game);
	init_player_position(&game);
	init_collectibles(&game);
	mlx_hook(game.window, 2, 1L, handle_keypress, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
