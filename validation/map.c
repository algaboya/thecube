/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 02:40:21 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:42:13 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	map(t_config *data, int fd)
{
	char	*map;

	map = map_reading(fd);
	close(fd);
	empty_lines(data, map);
	char_check(data, map);
	map_to_matrix(map, data);
	valid_walls(data);
}

char	*map_reading(int fd)
{
	char	*str;
	char	*result;
	char	*tmp;

	result = "";
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		tmp = result;
		result = ft_strjoin(tmp, str);
		if (ft_strncmp(result, str, ft_strlen(result)) != 0)
			free(tmp);
		free(str);
	}
	return (result);
}

void	empty_lines(t_config *data, char *map)
{
	int	i;
	int	empty;
	
	i = 0;
	empty = 0;
	while (map[i])
	{
		empty = 0;
		while (map[i] == '\n')
			i++;
		while (map[i] && map[i] != '\n')
		{
			if (map[i] == '1' || map[i] == '0' || map[i] == 'N' || map[i] == 'S'
				|| map[i] == 'E' || map[i] == 'W')
				empty = 1;
			i++;
		}
		while (map[i] && map[i] == '\n')
			i++;
		if (empty == 0)
			clean_and_exit("EMPTY LINE!\n", map, data);
	}
}

void	char_check(t_config *data, char *map)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'E' || map[i] == 'W')
		{
			player++;
		}
		else if (map[i] != '0' && map[i] != '1' && map[i] != '\n'
			&& map[i] != ' ')
		{
			clean_and_exit("Forbidden character in the map\n", map, data);
		}
		i++;
	}
	if (player != 1)
		clean_and_exit("MORE THAN 1 player\n", map, data);
}

void	map_to_matrix(char *map, t_config *data)
{
	data->map = ft_split(map, '\n');
	free_set_null(map);
	if (!data->map)
	{
		free_data(data);
		error_msg_exit("MALLOC ERROR\n", 1);
	}
// 	int j = 0, i = 0;
// 	while(data->map[i])
// 	{
// 		while(data->map[i][j])
// 		{
// 			printf("%c", data->map[i][j]);
// 			j++;
// 		}
// 		printf("-\n");
// 		i++;
// 		j = 0;
// 	}
}

