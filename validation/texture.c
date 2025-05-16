/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 02:32:57 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:46:21 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
		if (is_valid(splitted[1]))
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


