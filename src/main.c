/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:27:01 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/20 09:20:09 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

static int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free_split(game->map);
	free(game->mlx);
	exit(0);
	return (0);
}

static int handle_keypress(int keycode, t_game *game)
{
	// ESC key is usually 65307
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free_split(game->map);
		free(game->mlx);
		exit(0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	char	*map;

	if (ac != 2)
		return (write(2, "Error: invalid number of arguments\n", 35));
	map = read_map("maps/test.ber");
	if (!map)
		return (write(2, "Error: failed to read map\n", 26));
	if (check_map(map) == 1)
		return (free(map), 1);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 800, 600, "so_long");
	game.map = ft_split(map, '\n');
	free (map);
	init_map(game.mlx, game.window, game.map);
	mlx_hook(game.window, 2, 1L, handle_keypress, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	if (!av)
		return (1);
}
