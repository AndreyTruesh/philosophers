/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:34:32 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:39:02 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct	s_info
{
	int				num;
	unsigned long	ts;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*sem_stop;
	int				stop;
}				t_info;

typedef struct	s_philo
{
	int				num;
	unsigned long	last_time_eat;
	int				eat_count;
	t_info			*info;
}				t_philo;

void			ft_putendl_fd(char *s, int fd);
char			*ft_itoa(int n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
unsigned long	get_timestamp(void);
void			report_status(t_philo *philo, t_info *info, int id);
void			*monitor(void *ptr_philos);
int				start_threads(t_info info, t_philo *philos);
int				init_table(t_philo **philos, t_info *info);
void			close_sems(t_info info, pthread_t *threads);

#endif
