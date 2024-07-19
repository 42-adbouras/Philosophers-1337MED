/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:00 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/19 21:53:30 by adbouras         ###   ########.fr       */
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

# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define RSET "\e[0m"
# define CLRS 0
# define INT_MAX 2147483647

typedef enum s_code
{
	CREAT,
	JOIN,
	DETACH,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
}				t_code;

typedef struct s_data	t_data;

typedef struct s_mtx
{
	int				id;
	pthread_mutex_t	forks;
}					t_mtx;

typedef struct s_philo
{
	int				id;
	int				meals;
	bool			full;
	long			last_meal;
	pthread_t		thread;
	t_mtx			*r_fork;
	t_mtx			*l_fork;
	pthread_mutex_t	if_full;
	pthread_mutex_t	time;
	t_data			*data;
}					t_philo;

struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_init;
	int				num_to_eat;
	bool			death;
	bool			sync;
	t_philo			*philo_id;
	t_mtx			*forks;
	pthread_t		monitor;
	pthread_mutex_t	meals;
	pthread_mutex_t	write;
	pthread_mutex_t	sync_mutex;
	pthread_mutex_t	death_mutex;
};

/***	ROUTINES		***********************************/
void	*ft_one_philo(void *param);
bool	ft_start_sim(t_data *data);
void	ft_monitor(t_data *data);
void	*ft_dinning(void *param);

/***	THREAD & MUTEX	***********************************/
void	mutex_handle(pthread_mutex_t *mutex, t_code code);
bool	thread_handle(pthread_t *thread, void *(*func)(void *),
			void *data, t_code code);

/***	ACTIONS			*****************************************/
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_eating(t_philo *philo);

/***	SET & GET			*****************************************/
void	set_bool(bool *target, pthread_mutex_t *mutex, bool value);
void	set_long(long *target, pthread_mutex_t *mutex, long value);
bool	get_bool(bool *target, pthread_mutex_t *mutex);
long	get_long(long *target, pthread_mutex_t *mutex);

/***	CHECKERS			*****************************************/
bool	all_philos_full(t_data *data);
bool	if_philo_died(t_data *data);

/***	FREE			*****************************************/
void	ft_clean(t_data *data);

/***	UTILS			*****************************************/
void	ft_print(t_philo *philo, char *s, char *color);
bool	ft_parsing(char **arg, t_data *prog);
bool	all_philos_full(t_data *data);
void	ft_wait_threads(t_data *data);
bool	ft_philos_init(t_data *data);
void	ft_usleep(long ms);
long	ft_atoi(char *s);
long	get_time(void);

#endif