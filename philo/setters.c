/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:10:20 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/16 10:12:35 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(bool *target, pthread_mutex_t *mutex, bool value)
{
	mutex_handle(mutex, LOCK);
	*target = value;
	mutex_handle(mutex, UNLOCK);
}
