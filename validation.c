/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:03:51 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:33:29 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_valid_data(char *input)
{
	int			fd;
	t_config	*data;

	check_name(input);
	data = (t_config *)malloc(sizeof(t_config));
	init_data(data);
	fd = opened_file(input, data);
	if (textures(fd, data) == EXIT_FAILURE)
	{
		close(fd);
		free_data(data);
		error_msg_exit("INVALID MAP\n", 1);
	}
	map(data, fd);
	// printf("no_tex is ------ %s", data->no_tex);
	// printf("so_tex is ------ %s", data->so_tex);
	// printf("we_tex is ------ %s", data->we_tex);
	// printf("ea_tex is ------ %s", data->ea_tex);
	// printf("floor_color is ------ %d\n", data->floor_color);
	// printf("c_color is ------ %d\n", data->ceiling_color);
}

void	check_name(char *input)
{
	int	len;

	len = ft_strlen(input);
	if (ft_strcmp(input + (len - 4), ".cub") != 0)
		error_msg_exit("Invalid argument\n", 1);
}

void init_data(t_config *data)
{
	data->no_tex = NULL;
	data->so_tex = NULL;
	data->we_tex = NULL;
	data->ea_tex = NULL;
	data->map = NULL;
}

int opened_file(char *file, t_config *data)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free_set_null(data);
		error_msg_exit("Can't open file\n", 1);
	}
	return (fd);
}

int textures(int fd, t_config *data)
{
	int		i;
	char	*buff;
	int 	ret_val;

	i = 0;
	ret_val = 0;
	while (i < 6)
	{
		buff = get_next_line(fd);
		if (!buff)
			break;
		if (is_empty(buff))
		{
			free_set_null(buff);
			continue;
		}
		ret_val = set_data(buff, data);
		if (ret_val == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if  (ret_val == MALLOC_ERROR)
			return (error_msg_exit("MALLOC ERROR\n", 0), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int set_data(char *buff, t_config *data)
{
	(void)data;
	char	**splitted;

	splitted = ft_split(buff, ' ');
	if (!splitted)
		return (MALLOC_ERROR);
	if (array_len(splitted) == 2)
	{
		if (true)
		{
			if (set_texture(data, splitted) == MALLOC_ERROR
				|| set_texture(data, splitted) == EXIT_FAILURE)
			{
				free_array(splitted);
				free_data(data);
				error_msg_exit("MALLOC ERROR!\n", 1);
			} 
		}
	}
	else
		error_msg_exit("Invalid number of arguments\n", 0);
	free_array(splitted);
	return (EXIT_SUCCESS);
}

int	set_texture(t_config *data, char **splitted)
{
	if (ft_strcmp(splitted[0], "NO") == 0)
	{
		data->no_tex = ft_strdup(splitted[1]);
		return (check_malloc(data->no_tex));
	}
	else if (ft_strcmp(splitted[0], "SO") == 0)
	{
		data->so_tex = ft_strdup(splitted[1]);
		return (check_malloc(data->so_tex));
	}
	else if (ft_strcmp(splitted[0], "WE") == 0)
	{
		data->we_tex = ft_strdup(splitted[1]);
		return (check_malloc(data->we_tex));
	}
	else if (ft_strcmp(splitted[0], "EA") == 0)
	{
		data->ea_tex = ft_strdup(splitted[1]);
		return(check_malloc(data->ea_tex));
	}
	return (set_color(data, splitted));
}

int	set_color(t_config *data, char **splitted)
{
	if (ft_strcmp(splitted[0], "F") == 0)
	{
		if (get_color(splitted[1]) != EXIT_FAILURE)
		{
			data->floor_color = get_color(splitted[1]);
			return (EXIT_SUCCESS);
		}
	}
	else if (ft_strcmp(splitted[0], "C") == 0)
	{
		if (get_color(splitted[1]) != EXIT_FAILURE)
		{
			data->ceiling_color = get_color(splitted[1]);	
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

int	get_color(char *color)
{
	char	**splitted;
	int		len;

	if ((color[0] && color[0] == ',') || (color[ft_strlen(color) - 1]
			&& color[ft_strlen(color) - 1] == ','))
		return (error_msg_exit("Invalid type for color\n", 0), EXIT_FAILURE);
	// if (ft_strstr(color, ",,"))
	// 	return (error_msg_exit("Double comma\n", 0), EXIT_FAILURE);
	splitted = ft_split(color, ',');
	if (!splitted)
		return (error_msg_exit("Malloc Error\n", 0), EXIT_FAILURE);	
	len = array_len(splitted);
	if (len != 3)
	{
		free_array(splitted);
		return (error_msg_exit("Invalid number of arguments\n", 0), EXIT_FAILURE);
	}
	return(valid_color(splitted));
}

int valid_color(char **splitted)
{
	int red;
	int green;
	int blue;
	
	red = ft_atoi(splitted[0]);
	green = ft_atoi(splitted[1]);
	blue = ft_atoi(splitted[2]);
	if ((red > 255 || red < 0) || (green > 255 || green < 0)
	|| (blue > 255 || blue < 0))
	{
		free_array(splitted);
		return (error_msg_exit("Invalid range for color\n", 0), EXIT_FAILURE);
	}
	return (red * 256 * 256 + green * 256 + blue);
}

int check_malloc(void *ptr)
{
	if (!ptr)
		return (MALLOC_ERROR);
	return (EXIT_SUCCESS);
}

bool	is_valid(char *str)
{
	if (ft_strcmp(str + (ft_strlen(str) - 4), ".xpm") == 0)
	{
		return (true);
	}
	return (false);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free_set_null(arr[i]);
		i++;
	}
	free_set_null(arr[i]);
	free(arr);
	arr = NULL;
	return ;
}

void	free_data(t_config *data)
{
	free_array(data->map);
	data->map = NULL;
	free_set_null(data->no_tex);
	free_set_null(data->so_tex);
	free_set_null(data->we_tex);
	free_set_null(data->ea_tex);
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

void	clean_and_exit(char *error_msg, void *ptr, t_config *data)
{
	free_data(data);
	if (ptr)
		free_set_null(ptr);
	error_msg_exit(error_msg, 1);
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
	
	
char	*my_join(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s2)
	return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (s == NULL)
	return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	if (i != 0)
		s[i++] = '\n';
	while (s2[j] != '\0')
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

void	map_to_matrix(char *map, t_config *data)
{
	// printf("THE MAP IS \n%s\n", map);
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

void	check_walls_helper(t_config *data, int i, int j)
{
	if (!data->map[i][j + 1] || (data->map[i][j + 1] && (data->map[i][j
				+ 1] == ' ' || data->map[i][j + 1] == '\n')))
	{
		clean_and_exit("Must be surrounded by walls (1)\n", NULL, data);
	}
	if (j == 0 || !data->map[i][j - 1] || (data->map[i][j - 1]
			&& (data->map[i][j - 1] == ' ' || data->map[i][j - 1] == '\n')))
	{
		clean_and_exit("Must be surrounded by walls (1)\n", NULL, data);
	}
	if (!data->map[i - 1] || !data->map[i + 1])
	{
		clean_and_exit("Must be surrounded by walls (1)\n", NULL, data);
	}
	if (i == 0 || !data->map[i - 1][j] || (data->map[i - 1][j] && (data->map[i
				- 1][j] == ' ' || data->map[i - 1][j] == '\n')) || !data->map[i
		+ 1][j] || (data->map[i + 1][j] && (data->map[i + 1][j] == ' '
				|| data->map[i + 1][j] == '\n')))
	{
		clean_and_exit("Must be surrounded by walls (1)\n", NULL, data);
	}
}

void	valid_walls(t_config *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
				check_walls_helper(data, i, j);
			j++;
		}
		i++;
	}
}

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