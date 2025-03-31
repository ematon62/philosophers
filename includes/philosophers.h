/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:58:56 by ematon            #+#    #+#             */
/*   Updated: 2025/03/31 19:43:32 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

//Error messages
# define NUMBER_OF_ARGS "philo: Incorrect number of arguments (4, optionally 5): \
\n./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n"

# define INTEGER_ARGUMENTS "philo: Arguments must be positive integers\n"
# define NB_PHILO "philo: There must be at least 1 philosopher\n"
# define GETTIMEOFDAY "philo: gettimeofday: error ocurred\n"
# define MALLOC "philo: malloc: Out of memory\n"
# define MUTEX_INIT "philo: pthread_mutex_init: Error\n"

//State change messages
# define TAKE "%ld %d has taken a fork\n"
# define EAT "%ld %d is eating\n"
# define SLEEP "%ld %d is sleeping\n"
# define THINK "%ld %d is thinking\n"
# define DIE "%ld %d has died\n"

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_state
{
	pthread_mutex_t	*forks_ptr;
	pthread_mutex_t	*last_time_eaten;
	pthread_mutex_t	write_perm;
	pthread_mutex_t	end_mutex;
	t_philo			**philos;
	t_data			*data;
	bool			finished;
	time_t			current;
	bool			initialized;
}	t_state;

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	struct timeval	start;
	bool			initialized;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_index;
	int				right_index;
	int				nb_times_eaten;
	t_data			*data;
	time_t			time_since_last;
	t_state			*state;
}	t_philo;

//Lib
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);
int			ft_isspace(char c);
int			ft_isdigit(int c);
void		ft_free_toodee(void **ptr);

//Parsing
t_data		parse(char **argv);

//Simulation
t_state		init_simulation(t_data data);
int			destroy_simulation(t_state *state, t_data data);
t_philo		**init_philo(t_data *data, t_state *simstate);

int			simulation(t_data data);
void		*routine(void *input);
bool		check_if_continue(t_state *state);
int			eat(t_philo *philo);
int			sleepers(t_philo *philo);
int			think(t_philo *philo);

//Monitoring
void		*monitor_routine(void *input);
int			event(char *s, t_state *state, int id);

//Utils
int			left(int index);
int			right(int index, int nb_philo);
time_t		get_time_since_start(t_data *data);
time_t		get_time_since_last_meal(t_philo *data);

#endif