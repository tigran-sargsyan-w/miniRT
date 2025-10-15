/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:08:04 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/15 04:32:04 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "miniRT.h"
#include "types.h"

int main(int argc, char **argv)
{
    int fd;
    //t_scene scene;

    if (check_args(argc, argv) != 0)
        return (1);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    if (check_parse_file(fd) != 0)
    {
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}
