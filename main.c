/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:26:56 by algaboya          #+#    #+#             */
/*   Updated: 2025/04/30 18:40:27 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 2)
        return (error_msg_exit("Invalid input\n", 1), 1);
    // printf("ola\n");
    get_valid_data(argv[1]);
    //cube();
    return (0);
}