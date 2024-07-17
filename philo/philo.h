/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:00 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/17 18:58:34 by adbouras         ###   ########.fr       */
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

typedef struct s_data t_data;

typedef struct	s_mtx
{
	int 			id;
	pthread_mutex_t	forks;
}					t_mtx;

typedef struct	s_philo
{
	int				id;
	int				meals;
	bool			full;
	size_t			last_meal;
	pthread_t		thread;
	t_mtx			*r_fork;
	t_mtx			*l_fork;
	pthread_mutex_t	if_full;
	pthread_mutex_t	state;
	t_data			*data;
	pthread_mutex_t	time;
}					t_philo;

struct s_data
{
	int				num_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_init;
	int				num_to_eat;
	bool			death;
	bool			sync;
	t_philo			*philo_id;
	pthread_t		monitor;
	t_mtx			*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	meals;
	pthread_mutex_t	write;
	pthread_mutex_t	sync_mutex;
	pthread_mutex_t	death_mutex;
};

/***	ROUTINES		***********************************/
void    *ft_monitor(t_data *data);
void	*ft_dinning(void *param);
void	*ft_one_philo(void *param);

/***	THREAD & MUTEX	***********************************/
bool    mutex_handle(pthread_mutex_t *mutex, t_code code);
bool    tread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_code code);

/***	SYNC			******************************************/
void    ft_wait_threads(t_data *data);

/***	ACTIONS			*****************************************/
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

/***	SET&GET			*****************************************/
void	set_bool(bool *target, pthread_mutex_t *mutex, bool value);
void	set_long(size_t *target, pthread_mutex_t *mutex, size_t value);
bool	get_bool(bool *target, pthread_mutex_t *mutex);
size_t	get_value(size_t *target, pthread_mutex_t *mutex);

/***	FREE			*****************************************/
void	ft_clean(t_data *data);

/***	UTILS			*****************************************/
size_t	get_time(void);
void	ft_usleep(size_t ms);
int		ft_atoi(char *s);
void    ft_print(t_philo *philo, char *s, char *color);
bool	ft_parsing(char **arg, t_data *prog);
void	ft_philos_init(t_data *data);
bool    if_philo_died(t_philo *philo);
bool	all_philos_full(t_data *data);

#endif