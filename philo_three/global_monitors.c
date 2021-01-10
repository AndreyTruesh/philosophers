/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_monitors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:49:59 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:51:14 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	kill_processes(t_mon *mon)
{
	int i;

	i = 0;
	while (i < mon->num)
	{
		kill(mon->pid_arr[i], 9);
		i++;
	}
}

static void	*mon_stop(void *ptr_mon)
{
	t_mon	*mon;
	int		i;

	i = 0;
	mon = (t_mon *)ptr_mon;
	sem_wait(mon->stop);
	if (!mon->meals_done)
	{
		mon->stop_done = 1;
		kill_processes(mon);
		while (i < mon->num)
		{
			sem_post(mon->meals);
			i++;
		}
	}
	return (0);
}

static void	*mon_meals(void *ptr_mon)
{
	int		i;
	t_mon	*mon;

	mon = (t_mon *)ptr_mon;
	i = 0;
	while (i < mon->num)
	{
		sem_wait(mon->meals);
		i++;
	}
	if (!mon->stop_done)
	{
		mon->meals_done = 1;
		kill_processes(mon);
		sem_post(mon->stop);
	}
	return (0);
}

void		mon_init(t_mon *mon, t_info info, int *pid_arr)
{
	mon->stop = info.sem_stop;
	mon->meals = info.sem_meals;
	mon->num = info.num;
	mon->pid_arr = pid_arr;
	mon->meals_done = 0;
	mon->stop_done = 0;
}

void		start_monitors(t_mon *mon)
{
	pthread_t	stop_mon;
	pthread_t	meals_mon;

	if (pthread_create(&meals_mon, NULL, mon_meals, mon) != 0)
	{
		ft_putendl_fd("Create thread error!", 2);
		kill_processes(mon);
		return ;
	}
	if (pthread_create(&stop_mon, NULL, mon_stop, mon) != 0)
	{
		ft_putendl_fd("Create thread error!", 2);
		kill_processes(mon);
		return ;
	}
	pthread_join(stop_mon, NULL);
	pthread_join(meals_mon, NULL);
}
