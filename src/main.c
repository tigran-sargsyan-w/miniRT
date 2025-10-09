#include "miniRT.h"
#include <fcntl.h>
#include "libft.h"

int check_input(int argc, char **argv)
{
    int len;
    if (argc != 2)
    {
        printf("Usage: %s <scene_file>\n", argv[0]);
        return (1);
    }
    if (argv[1][0] == '\0')
    {
        printf("Error: Empty filename\n");
        return (1);
    }
    len = ft_strlen(argv[1]);
    if (len < 4 || argv[1][len - 3] != '.' || argv[1][len - 2] != 'r' || argv[1][len - 1] != 't')
    {
        printf("Error: Filename must end with .rt\n");
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    if (check_input(argc, argv) != 0)
        return (1);
    if (open(argv[1], O_RDONLY) == -1)
    {
        perror("Error opening file");
        return (1);
    }
    printf("Hello, miniRT!\n");
    return (0);
}
