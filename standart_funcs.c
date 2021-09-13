/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standart_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:55:43 by aahri             #+#    #+#             */
/*   Updated: 2021/08/25 20:17:38 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long int	b;
	int					sign;

	b = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		b = b * 10 + (str[i] - 48);
		i++;
	}
	if (sign == 1 && b > 9223372036854775807)
		b = (int) -1;
	if (sign == -1 && b > 9223372036854775807)
		b = (int)0;
	return (sign * b);
}

int	is_nbr(char *argv)
{
	int		ind;

	ind = 0;
	while (argv[ind] <= '9' && argv[ind] >= '0')
		ind++;
	if (!argv[ind])
		return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		if (is_nbr(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse(t_collective *obj, char **argv)
{
	obj->state = 0;
	obj->number_of_philosophers = ft_atoi(argv[1]);
	obj->time_to_die = ft_atoi(argv[2]);
	obj->time_to_eat = ft_atoi(argv[3]);
	obj->time_to_sleep = ft_atoi(argv[4]);
	obj->number_of_times_each_philosopher_must_eat = -1;
	if (argv[5] != NULL)
		obj->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (!obj->number_of_philosophers || !obj->time_to_die || !obj->time_to_eat
		|| !obj->time_to_sleep
		|| !obj->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

int	making_arrays(t_philo **philo, t_collective *obj)
{
	pthread_mutex_t	*fork;
	int				ind;

	ind = 0;
	*philo = (t_philo *)malloc(sizeof(t_philo) * obj->number_of_philosophers);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* obj->number_of_philosophers);
	if (!fork || !(*philo))
		return (1);
	(*philo)->saving_fork = fork;
	pthread_mutex_init(&obj->die, NULL);
	while (ind < obj->number_of_philosophers)
	{
		(*philo)[ind].philo = obj;
		(*philo)[ind].count = 0;
		(*philo)[ind].delta_time = 0;
		(*philo)[ind].index_phil = ind + 1;
		pthread_mutex_init(&fork[ind], NULL);
		(*philo)[ind].right = &fork[ind];
		(*philo)[ind].left = &fork[0];
		if (ind + 1 != obj->number_of_philosophers)
			(*philo)[ind].left = &fork[ind + 1];
		ind++;
	}
	return (0);
}
