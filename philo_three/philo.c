/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:52:41 by abibi             #+#    #+#             */
/*   Updated: 2021/01/18 20:33:34 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	take_forks(t_philo *philo)
{
	sem_wait(philo->info->turn);
	sem_wait(philo->info->forks);
	if (philo->stop)
	{
		sem_post(philo->info->forks);
		sem_post(philo->eat);
		sem_post(philo->info->turn);
		return (0);
	}
	report_status(philo, philo->info, 0);
	sem_wait(philo->info->forks);
	sem_post(philo->info->turn);
	return (1);
}

static int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	sem_wait(philo->eat);
	if (philo->stop)
	{
		sem_post(philo->eat);
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		return (0);
	}
	report_status(philo, philo->info, 0);
	report_status(philo, philo->info, 1);
	philo->last_time_eat = get_timestamp();
	if (philo->info->eat_times >= 0)
		philo->eat_count++;
	if (philo->eat_count == philo->info->eat_times)
		sem_post(philo->info->sem_meals);
	sem_post(philo->eat);
	usleep(1000 * philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	return (1);
}

static void	*philo_process(void *ptr_philo)
{
	t_philo *philo;
	int		res;

	philo = (t_philo *)(ptr_philo);
	while (1 == 1)
	{
		res = eat(philo);
		if (!res)
			return (0);
		if (philo->stop)
			return (0);
		report_status(philo, philo->info, 2);
		usleep(1000 * philo->info->time_to_sleep);
		if (philo->stop)
		{
			sem_post(philo->eat);
			return (0);
		}
		report_status(philo, philo->info, 3);
	}
}

static void	*monitor(void *ptr_philo)
{
	t_philo *philo;

	philo = (t_philo *)(ptr_philo);
	while (1 == 1)
	{
		sem_wait(philo->eat);
		if ((int)(get_timestamp() - philo->last_time_eat) >
			philo->info->time_to_die)
		{
			report_status(philo, philo->info, 4);
			philo->stop = 1;
			sem_post(philo->eat);
			sem_post(philo->info->sem_stop);
			return (0);
		}
		sem_post(philo->eat);
		usleep(10);
	}
}

void		start_philo(t_philo *philo)
{
	pthread_t mon;

	if (pthread_create(&mon, NULL, monitor, philo) != 0)
	{
		ft_putendl_fd("Create thread error!", 2);
		sem_post(philo->info->sem_stop);
	}
	philo_process(philo);
}
