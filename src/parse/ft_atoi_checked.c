#include "libft.h"
#include <limits.h>

static const char	*skip_spaces_and_sign(const char *nptr, int *sign)
{
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			*sign *= -1;
		nptr++;
	}
	while (*nptr == '0' && *(nptr + 1) != '\0')
		nptr++;
	return (nptr);
}

int	ft_atoi_checked(const char *nptr, int *num)
{
	long	res;
	int		sign;
	int		digit_found;

	res = 0;
	sign = 1;
	digit_found = 0;
	nptr = skip_spaces_and_sign(nptr, &sign);
	if (ft_strlen(nptr) > 11)
		return (1);
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit_found = 1;
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	if (!digit_found || *nptr != '\0')
		return (1);
	res *= sign;
	if (res > INT_MAX || res < INT_MIN)
		return (1);
	*num = (int)res;
	return (0);
}