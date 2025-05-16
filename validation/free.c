/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orinakkk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:03:51 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/17 02:49:47 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void error_msg_exit(char *msg, int status)
{
    write(2, msg, ft_strlen(msg));
    if (status == 1)
        exit(status);
}

void free_set_null(void *ptr)
{
    free(ptr);
    ptr = NULL;
}

bool is_empty(char *str)
{
    if ((ft_strchr(str, '\n') || ft_strchr(str, '\t')
        || ft_strchr(str, '\v')) && ft_strlen(str) == 1)
        return (true);
    return (false);
}






	
	





