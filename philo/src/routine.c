/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:17:57 by sting             #+#    #+#             */
/*   Updated: 2024/10/24 16:45:20 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void print_message(t_philo *philo, char *message)
{
	int timestamp;

	pthread_mutex_lock(&philo->program->print_lock);
	timestamp = get_current_time() - philo->program->start_time;
	printf("%i %i %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->program->print_lock);
}

void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	// printf("current time: %zu\n", get_current_time());
	print_message(philo, "has taken a fork");
	if (philo->program->args.philo_count == 1)
	{
		pthread_mutex_unlock(&philo->l_fork);
		return ;
	}
	pthread_mutex_lock(&philo->r_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	ft_usleep(philo->program->args.time_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->program->args.time_to_sleep);
}

void thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;

	printf("current_time[%i]: %zu\n", philo->id, get_current_time());

	if (philo->id % 2 == 0) // even num delay
		ft_usleep(50); //! why 50?

	// philo->start_time = get_current_time(); // ! storing start_time - method #2
	// printf("start_time  : %zu\n", philo->start_time); // ! wrong -> storing start_time when philo is created
	
	while (1) // todo: died condition
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}