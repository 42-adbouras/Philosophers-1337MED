/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:16:29 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/09 16:56:30 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    mutex_handle(pthread_mutex_t *mutex, t_code code)
{
    if (code == INIT)
    {
        if (pthread_mutex_init(mutex, NULL) != 0)
            return (false);
    }
    else if (code == LOCK)
    {
        if (pthread_mutex_lock(mutex) != 0)
            return (false);
    }
    else if (code == UNLOCK)
    {
        if (pthread_mutex_unlock(mutex) != 0)
            return (false);
    }
    else if (code == DESTROY)
    {
        if (pthread_mutex_destroy(mutex) != 0)
            return (false);
    }
    return (true);
}

bool    tread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_code code)
{
    if (code == CREAT)
    {
        if (pthread_create(thread, NULL, func, data) != 0)
            return (false);
    }
    else if (code == JOIN)
    {
        if (pthread_join(*thread, NULL) != 0)
            return (false);
    }
    else if (code == DETACH)
    {
        if (pthread_detach(*thread) != 0)
            return (false);
    }
    return (true);
}
