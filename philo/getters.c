/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:13:20 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/18 15:44:27 by adbouras         ###   ########.fr       */
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

size_t	get_value(size_t *target, pthread_mutex_t *mutex)
{
	size_t	value;

	mutex_handle(mutex, LOCK);
	value = *target;
	mutex_handle(mutex, UNLOCK);
	return (value);
}
