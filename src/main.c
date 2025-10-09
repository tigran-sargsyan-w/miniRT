#include "miniRT.h"
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

int check_args(int argc, char **argv)
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
char *get_token(char **str, const char *delim)
{
    char *start;
    char *end;
    char *token;
    size_t len;

    if (!str || !*str)
        return (NULL);
    while (**str && ft_strchr(delim, **str))
        (*str)++;
    if (**str == '\0')
        return (NULL);
    start = *str;
    end = start;
    while (*end && !ft_strchr(delim, *end))
        end++;
    len = end - start;
    token = (char *)malloc(len + 1);
    if (!token)
        return (NULL);
    ft_strlcpy(token, start, len + 1);
    *str = end;
    return (token);
}

int check_parse_file(int fd)
{
    char *line;
    char *trimmed_line;

    while ((line = get_next_line(fd)))
    {
        trimmed_line = ft_strtrim(line, " \t\r\n");
        free(line);
        printf("Read line: %s", trimmed_line);
        free(trimmed_line);
    }
    return (0);
}

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
