/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 02:45:18 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:47:05 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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