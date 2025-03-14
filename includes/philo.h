/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:58:56 by ematon            #+#    #+#             */
/*   Updated: 2025/03/14 11:30:48 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define NB_ARG_ERROR "philo: Incorrect number of arguments (4, optionally 5)\n"
# define INT_ARG_ERROR "philo: Arguments must be positive integers\n"
# define NB_PHILO_ERROR "philo: There must be at least 1 philosopher\n"

typedef struct s_data
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_must_eat;
}	t_data;

//Utils
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);
int		ft_isspace(char c);
int		ft_isdigit(int c);

//Parsing
t_data	parse(char **argv);

#endif