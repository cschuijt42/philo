/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 14:32:04 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/04 14:32:04 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(char *str)
{
	long			i;
	unsigned int	minuses;

	i = 0;
	minuses = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			minuses++;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		i = i * 10;
		i = i + (*str - 48);
		str++;
	}
	if (minuses)
		i = i * -1;
	return ((int) i);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*result;

	result = malloc(num * size);
	if (result)
		memset(result, 0, num * size);
	return (result);
}
