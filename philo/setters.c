/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:10:20 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/22 14:32:51 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(bool *target, pthread_mutex_t *mutex, bool value)
{
	mutex_handle(mutex, LOCK);
	*target = value;
	mutex_handle(mutex, UNLOCK);
}

void	set_long(long *target, pthread_mutex_t *mutex, long value)
{
	mutex_handle(mutex, LOCK);
	*target = value;
	mutex_handle(mutex, UNLOCK);
}
