/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:27:01 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/18 20:49:47 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

int	main(int ac, char **av)
{
	char	*map;

	if (ac != 2)
		return (write(2, "Error: invalid number of arguments\n", 35));
	map = read_map("maps/test.ber");
	if (!map)
	{
		free(map);
		return(write(2, "Error: failed to read map\n", 26));
	}
	if(check_map(map) == 1)
		free(map);
	free(map);
	if(!av)
		return (1);
}
