/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:09:46 by soumanso          #+#    #+#             */
/*   Updated: 2022/01/07 16:09:46 by soumanso         ###   ########lyon.fr   */
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
