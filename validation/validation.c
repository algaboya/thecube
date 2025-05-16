/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 02:33:15 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:48:32 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

bool	is_valid(char *str)
{
	if (ft_strcmp(str + (ft_strlen(str) - 4), ".xpm") == 0)
	{
		return (true);
	}
	return (false);
}

void	check_walls(t_config *data, int i, int j)
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
				check_walls(data, i, j);
			j++;
		}
		i++;
	}
}
