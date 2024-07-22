/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:16:29 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/22 14:31:55 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_handle(pthread_mutex_t *mutex, t_code code)
{
	bool	error;

	error = false;
	if (code == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			error = true;
	}
	else if (code == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			error = true;
	}
	else if (code == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			error = true;
	}
	else if (code == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			error = true;
	}
	if (error)
		write(2, BRED"[mutex_handle() error]\n"RSET, 34);
}

bool	thread_handle(pthread_t *thread, void *(*func)(void *),
	void *data, t_code code)
{
	bool	error;

	error = false;
	if (code == CREAT)
	{
		if (pthread_create(thread, NULL, func, data) != 0)
			error = true;
	}
	else if (code == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			error = true;
	}
	else if (code == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			error = true;
	}
	if (error)
	{
		write (2, BRED"[thread_handle() error]\n"RSET, 35);
		return (true);
	}
	return (false);
}
