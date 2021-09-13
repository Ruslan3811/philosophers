/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 19:02:32 by aahri             #+#    #+#             */
/*   Updated: 2021/08/25 20:17:28 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_philo *phil_chars)
{
	while (phil_chars->philo->state == 0)
	{
	}
}

void	ft_usleep(int time)
{
	unsigned long	time_to_sleep;
	unsigned long	start;
	unsigned long	end;

	time_to_sleep = (unsigned long)time;
	end = get_time();
	start = end;
	while (time_to_sleep > end - start)
	{
		end = get_time();
		usleep(100);
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->philo->state == 2)
		printf("%ld %d is sleeping\n",
			get_time() - philo->philo->start_time, philo->index_phil);
	ft_usleep(philo->philo->time_to_sleep);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	thinking(t_philo *philo)
{
	if (philo->philo->state == 2)
		printf("%ld %d  is thinking\n",
			get_time() - philo->philo->start_time, philo->index_phil);
}
