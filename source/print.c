/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:08:55 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/08 17:07:14 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, t_msg msg)
{
	static t_cstr	messages[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	pthread_mutex_lock (&philo->data->print_mutex);
	pthread_mutex_lock (&philo->data->death_mutex);
	if (!philo->data->dead || msg == MSG_DIED)
		printf ("%lu %i %s\n", get_time (philo->data),
			philo->id, messages[msg]);
	pthread_mutex_unlock (&philo->data->death_mutex);
	pthread_mutex_unlock (&philo->data->print_mutex);
}
