/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhambouras <adhambouras@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:00 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/06 18:50:56 by adhambouras      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum	s_code
{
	CREAT,
	JOIN,
	DETACH,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
}				t_code;

typedef struct	s_philo
{
	int				id;
	int				meals;
	bool			full;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_to_eat;
	size_t			time_init;
	bool			death;
	t_philo			*philo_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}					t_data;

/***	THREAD & MUTEX	***********************************/
bool    mutex_handle(pthread_mutex_t *mutex, t_code code);
bool    tread_handle(pthread_t *thread, void *(*func), void *data, t_code code);


bool	ft_parsing(char **arg, t_data *prog);
int		ft_atoi(char *s);
size_t	get_time(void);
void	ft_philos_init(t_data *data);

#endif