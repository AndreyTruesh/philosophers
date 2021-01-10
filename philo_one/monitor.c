/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:07:00 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:27:08 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	philos_done_eating(t_philo *philos)
{
	int i;

	i = 0;
	while (i < (*philos).info->num)
	{
		if (philos[i].eat_count < philos->info->eat_times)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_stop(t_philo *philos)
{
	int i;

	if (philos->info->eat_times > -1 && philos_done_eating(philos))
	{
		philos->info->stop = 1;
		return (0);
	}
	i = 0;
	while (i < (*philos).info->num)
	{
		if ((int)(get_timestamp() - philos[i].last_time_eat) >
				(*philos).info->time_to_die)
		{
			report_status(&philos[i], (*philos).info, 4);
			return (0);
		}
		i++;
	}
	return (1);
}

void		*monitor(void *ptr_philos)
{
	int		res;
	t_philo	*philos;

	philos = (t_philo *)ptr_philos;
	while (1 == 1)
	{
		pthread_mutex_lock(&philos->info->mutex_stop);
		res = check_stop(philos);
		if (!res)
		{
			pthread_mutex_unlock(&philos->info->mutex_stop);
			return (0);
		}
		pthread_mutex_unlock(&philos->info->mutex_stop);
		usleep(25);
	}
}
