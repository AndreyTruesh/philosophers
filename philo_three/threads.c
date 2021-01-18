/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:55:22 by abibi             #+#    #+#             */
/*   Updated: 2021/01/18 20:33:59 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	mem_free(t_philo *philos, t_info info, int *pid_arr)
{
	int i;

	i = 0;
	free(pid_arr);
	sem_close(info.forks);
	sem_close(info.sem_stop);
	sem_close(info.write);
	sem_close(info.sem_meals);
	sem_close(info.turn);
	sem_unlink("/turn");
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/stop");
	sem_unlink("/meals");
	while (i < info.num)
	{
		sem_close(philos[i].eat);
		sem_unlink(info.sem_name_arr[i]);
		free(info.sem_name_arr[i]);
		i++;
	}
	free(info.sem_name_arr);
}

int		start_threads(t_info info, t_philo *philos)
{
	int		i;
	int		*pid_arr;
	t_mon	mon;

	if (!(pid_arr = malloc(info.num * sizeof(int))))
		return (-1);
	i = 0;
	while (i < info.num)
	{
		pid_arr[i] = fork();
		if (pid_arr[i] == 0)
			start_philo(&philos[i]);
		if (pid_arr[i] < 0)
			return (-2);
		usleep(50);
		i++;
	}
	mon_init(&mon, info, pid_arr);
	start_monitors(&mon);
	mem_free(philos, info, pid_arr);
	return (1);
}
