/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:35:14 by algaboya          #+#    #+#             */
/*   Updated: 2025/05/06 17:45:45 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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