/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 19:13:01 by aahri             #+#    #+#             */
/*   Updated: 2021/08/26 16:02:39 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_collective
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					state;
	int					nbr_well_fed_ph;
	long int			start_time;
	pthread_mutex_t		die;
}						t_collective;

typedef struct s_philo
{
	pthread_t			thread;
	t_collective		*philo;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	int					index_phil;
	long int			delta_time;
	int					count;
	pthread_mutex_t		*saving_fork;
}						t_philo;

int			ft_atoi(const char *str);
int			is_nbr(char *argv);
int			parse(t_collective *obj, char **argv);
int			check_args(int argc, char **argv);
int			making_arrays(t_philo **philo, t_collective *obj);
void		thinking(t_philo *philo);
void		waiting(t_philo *phil_chars);
void		ft_usleep(int time);
void		sleeping(t_philo *philo);
long int	get_time(void);

#endif