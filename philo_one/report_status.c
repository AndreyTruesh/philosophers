/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:07:38 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:29:52 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	str_action_cpy(char *s, int id)
{
	if (id == 0)
		ft_strlcpy(s, "has taken a fork", ft_strlen("has taken a fork") + 1);
	if (id == 1)
		ft_strlcpy(s, "is eating", ft_strlen("is eating") + 1);
	if (id == 2)
		ft_strlcpy(s, "is sleeping", ft_strlen("is sleeping") + 1);
	if (id == 3)
		ft_strlcpy(s, "is thinking", ft_strlen("is thinking") + 1);
	if (id == 4)
		ft_strlcpy(s, "died", ft_strlen("died") + 1);
}

void		report_status(t_philo *philo, t_info *info, int id)
{
	char			str[100];
	char			*rem;
	char			*buf;
	unsigned long	dts;

	if (id == 4)
		philo->info->stop = 1;
	pthread_mutex_lock(&info->write);
	memset(str, 0, 100);
	dts = get_timestamp() - info->ts;
	buf = ft_itoa((int)dts);
	ft_strlcpy(str, buf, ft_strlen(buf) + 1);
	str[ft_strlen(buf)] = ' ';
	rem = &str[0] + (int)ft_strlen(buf) + 1;
	free(buf);
	buf = ft_itoa(philo->num + 1);
	ft_strlcpy(rem, buf, ft_strlen(buf) + 1);
	rem[ft_strlen(buf)] = ' ';
	rem += (int)ft_strlen(buf) + 1;
	free(buf);
	str_action_cpy(rem, id);
	ft_putendl_fd(str, 1);
	pthread_mutex_unlock(&info->write);
}
