/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:13:20 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/19 10:49:03 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(bool *target, pthread_mutex_t *mutex)
{
	bool	value;

	mutex_handle(mutex, LOCK);
	value = *target;
	mutex_handle(mutex, UNLOCK);
	return (value);
}

long	get_long(long *target, pthread_mutex_t *mutex)
{
	long	value;

	mutex_handle(mutex, LOCK);
	value = *target;
	mutex_handle(mutex, UNLOCK);
	return (value);
}
