/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 02:43:55 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:45:43 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void init_data(t_config *data)
{
	data->no_tex = NULL;
	data->so_tex = NULL;
	data->we_tex = NULL;
	data->ea_tex = NULL;
	data->map = NULL;
}

int check_malloc(void *ptr)
{
	if (!ptr)
		return (MALLOC_ERROR);
	return (EXIT_SUCCESS);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	clean_and_exit(char *error_msg, void *ptr, t_config *data)
{
	free_data(data);
	if (ptr)
		free_set_null(ptr);
	error_msg_exit(error_msg, 1);
}

void	check_name(char *input)
{
	int	len;

	len = ft_strlen(input);
	if (ft_strcmp(input + (len - 4), ".cub") != 0)
		error_msg_exit("Invalid argument\n", 1);
}