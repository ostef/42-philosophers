/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:09:46 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/08 18:48:17 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_u64	get_time(t_data *data)
{
	struct timeval	time;
	t_u64			val;

	gettimeofday (&time, NULL);
	val = (t_u64)time.tv_sec * 1000 + (t_u64)time.tv_usec / 1000;
	val -= data->start_time;
	return (val);
}

void	sleep_ms(t_data *data, int time)
{
	t_u64	start;

	start = get_time (data);
	while (get_time (data) - start < (t_u64)time)
	{
		usleep (100);
	}
}
