/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:54:09 by aahri             #+#    #+#             */
/*   Updated: 2021/08/25 20:17:33 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checking_life_philo(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (philo->philo->state == 2)
	{
		if (get_time() - philo->delta_time > philo->philo->time_to_die)
		{
			pthread_mutex_lock(&philo->philo->die);
			if (philo->philo->state == 2)
				printf("%ld %d died\n",
					get_time() - philo->philo->start_time, philo->index_phil);
			philo->philo->state = 1;
			pthread_mutex_unlock(&philo->philo->die);
			break ;
		}
		if (philo->philo->nbr_well_fed_ph
			== philo->philo->number_of_philosophers)
			philo->philo->state = 1;
		usleep(100);
	}
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (NULL);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	if (philo->philo->state == 2)
		printf("%ld %d has taken a fork\n",
			get_time() - philo->philo->start_time, philo->index_phil);
	pthread_mutex_lock(philo->left);
	if (philo->philo->state == 2)
		printf("%ld %d has taken a fork\n",
			get_time() - philo->philo->start_time, philo->index_phil);
	philo->delta_time = get_time();
	if (philo->philo->state == 2)
		printf("%ld %d is eating\n",
			get_time() - philo->philo->start_time, philo->index_phil);
	philo->count++;
	if (philo->count == philo->philo->number_of_times_each_philosopher_must_eat)
		philo->philo->nbr_well_fed_ph++;
	ft_usleep(philo->philo->time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	*name_of_func(void *args)
{
	t_philo			*phil_char;
	pthread_t		thread;

	phil_char = (t_philo *)args;
	waiting(phil_char);
	phil_char->philo->start_time = get_time();
	phil_char->delta_time = phil_char->philo->start_time;
	if (phil_char->philo->state == 2
		&& pthread_create(&thread, NULL, checking_life_philo, phil_char))
		phil_char->philo->state = 1;
	if (phil_char->index_phil % 2 == 0)
		ft_usleep(phil_char->philo->time_to_eat);
	else if (phil_char->index_phil == phil_char->philo->number_of_philosophers
		&& phil_char->index_phil != 1)
		ft_usleep(phil_char->philo->time_to_eat
			+ phil_char->philo->time_to_sleep / 2);
	while (phil_char->philo->state == 2)
	{
		eating(phil_char);
		sleeping(phil_char);
		thinking(phil_char);
	}
	pthread_join(thread, NULL);
	return (NULL);
}

int	run_pthread(t_philo *phil_chars)
{
	int			ind;

	ind = 0;
	while (ind < phil_chars->philo->number_of_philosophers)
	{
		if (pthread_create(&phil_chars[ind].thread,
				NULL, name_of_func, &phil_chars[ind]))
			break ;
		ind++;
	}
	if (ind != phil_chars->philo->number_of_philosophers)
		phil_chars->philo->state = 1;
	else
		phil_chars->philo->state = 2;
	while (ind > 0)
	{
		pthread_join(phil_chars[--ind].thread, NULL);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_collective	obj;
	t_philo			*phil_chars;

	obj.nbr_well_fed_ph = 0;
	if (check_args(argc, argv) || parse(&obj, argv))
	{
		printf("Error\n");
		return (1);
	}
	if (!making_arrays(&phil_chars, &obj))
		run_pthread(phil_chars);
	if (phil_chars)
		free(phil_chars);
	if (phil_chars->saving_fork)
		free(phil_chars->saving_fork);
	return (0);
}
