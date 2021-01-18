/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:33:59 by abibi             #+#    #+#             */
/*   Updated: 2021/01/18 20:08:22 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	philos_done_eating(t_philo *philos)
{
	int i;

	i = 0;
	while (i < (*philos).info->num)
	{
		if (philos[i].eat_count < philos->info->eat_times)
			return (0);
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
			philos->info->stop = 1;
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
		sem_wait(philos->info->sem_stop);
		res = check_stop(philos);
		if (!res)
		{
			sem_post(philos->info->sem_stop);
			return (0);
		}
		sem_post(philos->info->sem_stop);
		usleep(5);
	}
}

void		close_sems(t_info info, pthread_t *threads)
{
	sem_close(info.forks);
	sem_close(info.sem_stop);
	sem_close(info.write);
	sem_close(info.turn);
	sem_unlink("/turn");
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/stop");
	free(threads);
}
