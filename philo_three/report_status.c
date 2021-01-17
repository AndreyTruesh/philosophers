/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:07:38 by abibi             #+#    #+#             */
/*   Updated: 2021/01/17 19:01:43 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		report_status(t_philo *philo, t_info *info, int id)
{
	sem_wait(info->write);
	if (id == 0)
		printf("%d %d has taken a fork\n",
				(int)(get_timestamp() - info->ts), philo->num + 1);
	if (id == 1)
		printf("%d %d is eating\n",
				(int)(get_timestamp() - info->ts), philo->num + 1);
	if (id == 2)
		printf("%d %d is sleeping\n",
				(int)(get_timestamp() - info->ts), philo->num + 1);
	if (id == 3)
		printf("%d %d is thinking\n",
				(int)(get_timestamp() - info->ts), philo->num + 1);
	if (id == 4)
		printf("%d %d died\n",
				(int)(get_timestamp() - info->ts), philo->num + 1);
	sem_post(info->write);
}
