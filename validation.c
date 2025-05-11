/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:03:51 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/11 15:04:28 by algaboya         ###   ########.fr       */
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
		free_data(data);
		error_msg_exit("INVALID MAP\n", 1);
	}
	printf("no_tex is ------ %s", data->no_tex);
	printf("so_tex is ------ %s", data->so_tex);
	printf("we_tex is ------ %s", data->we_tex);
	printf("ea_tex is ------ %s", data->ea_tex);
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
	while (i < 4)
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
			// printf("so_tex is ------ %s\n", data->so_tex);
			if (set_texture(data, splitted) == MALLOC_ERROR)
			{
				free_array(splitted);
				free_data(data);
				error_msg_exit("MALLOC ERROR!\n", 1);
			}
		}
	}
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
	// return (EXIT_SUCCESS);
}

int	set_color(t_config *data, char **splitted)
{
	if (ft_strcmp(splitted[0], "F") == 0)
	{
		data->no_tex = ft_strdup(splitted[1]);
		return (check_malloc(data->no_tex));
	}
	else if (ft_strcmp(splitted[0], "C") == 0)
	{
		data->so_tex = ft_strdup(splitted[1]);
		return (check_malloc(data->so_tex));
	}
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
	free_set_null(data->no_tex);
	free_set_null(data->so_tex);
	free_set_null(data->we_tex);
	free_set_null(data->ea_tex);
	free_array(data->map);
}
