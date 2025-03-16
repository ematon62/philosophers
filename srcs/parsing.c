/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:55:50 by ematon            #+#    #+#             */
/*   Updated: 2025/03/16 19:20:13 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_overflow(char *str, int i, int n)
{
	if (!str[i])
		return (0);
	else if ((n > 0 && n * 10 + str[i] - '0' < n)
		|| (n < 0 && n * 10 + str[i] - '0' > n))
		return (1);
	return (is_overflow(str, i + 1, n * 10 + str[i] - '0'));
}

static int	is_integer(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i])
	{
		if (!i && (str[i] == '-' || str[i] == '+'))
		{
			if (str[0] == '-')
				sign *= -1;
			if (!ft_isdigit(str[i + 1]))
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (!is_overflow(str, 0, 0));
}

static int	add_to_data(char *arg, int *ptr)
{
	int	atoi;

	atoi = ft_atoi(arg);
	if (!is_integer(arg) || atoi < 0)
		return (ft_putstr_fd(INT_ARG_ERROR, STDERR_FILENO), 1);
	*ptr = atoi;
	return (0);
}

t_data	parse(char **argv)
{
	int		i;
	t_data	data;
	int		*ptr;

	i = 1;
	data.nb_must_eat = -1;
	while (argv[i])
	{
		if (i == 1)
			ptr = &data.nb_philo;
		if (i == 2)
			ptr = &data.time_die;
		if (i == 3)
			ptr = &data.time_eat;
		if (i == 4)
			ptr = &data.time_sleep;
		if (i == 5)
			ptr = &data.nb_must_eat;
		if (add_to_data(argv[i], ptr))
			exit(EXIT_FAILURE);
		i++;
	}
	if (data.nb_philo < 1)
		return (ft_putstr_fd(NB_PHILO_ERROR, STDERR_FILENO), exit(1), data);
	return (data);
}
