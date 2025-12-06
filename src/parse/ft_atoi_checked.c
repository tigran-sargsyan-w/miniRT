/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_checked.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:46:52 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 00:41:54 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

/**
 * @brief Skips leading whitespace and processes optional sign
 * Advances nptr to first non-space, non-sign character
 * @param nptr - input string pointer
 * @param sign - out sign multiplier (+1 or -1)
 * @return const char* - advanced string pointer
 */
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

/**
 * @brief Converts string to int with overflow and format checks
 * Validates entire string is numeric and within int range
 * @param nptr - input numeric string
 * @param num - out converted integer
 * @return int - 0 on success, 1 on error (invalid format or overflow)
 */
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
