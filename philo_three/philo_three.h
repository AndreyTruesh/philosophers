/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:54:41 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:59:08 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct	s_info
{
	int				num;
	unsigned long	ts;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	char			**sem_name_arr;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*sem_stop;
	sem_t			*sem_meals;
}				t_info;

typedef struct	s_philo
{
	int				num;
	unsigned long	last_time_eat;
	int				eat_count;
	int				stop;
	sem_t			*eat;
	t_info			*info;
}				t_philo;

typedef struct	s_mon
{
	int		*pid_arr;
	int		num;
	int		meals_done;
	int		stop_done;
	sem_t	*meals;
	sem_t	*stop;
}				t_mon;

void			ft_putendl_fd(char *s, int fd);
char			*ft_itoa(int n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
unsigned long	get_timestamp(void);
void			report_status(t_philo *philo, t_info *info, int id);
int				init_table(t_philo **philos, t_info *info);
void			mon_init(t_mon *mon, t_info info, int *pid_arr);
void			start_monitors(t_mon *mon);
int				start_threads(t_info info, t_philo *philos);
void			start_philo(t_philo *philo);

#endif
