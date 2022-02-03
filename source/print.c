/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:08:55 by soumanso          #+#    #+#             */
/*   Updated: 2022/01/07 16:08:55 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, t_u64 time, t_msg msg)
{
	static t_cstr	messages[] = {
		" has taken a fork",
		" is eating",
		" is sleeping",
		" is thinking",
		" died"
	};
	t_bool			dead;

	dead = FALSE;
	pthread_mutex_lock (&philo->data->death_mutex);
	if (philo->data->dead)
		dead = TRUE;
	if (msg == MSG_DIED)
		philo->data->dead = TRUE;
	pthread_mutex_unlock (&philo->data->death_mutex);
	if (dead)
		return ;
	pthread_mutex_lock (&philo->data->print_mutex);
	printf ("%lu %i %s\n", time, philo->id, messages[msg]);
	pthread_mutex_unlock (&philo->data->print_mutex);
}
