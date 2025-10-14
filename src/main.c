/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:08:04 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/14 05:47:42 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "miniRT.h"

int main(int argc, char **argv)
{
    int fd;

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
