/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:17:57 by sting             #+#    #+#             */
/*   Updated: 2024/10/22 15:29:24 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	printf(" %i has taken a fork\n", philo->id);
	pthread_mutex_lock(&philo->r_fork);
	printf("[timestamp] %i has taken a fork\n", philo->id);
	printf("[timestamp] %i is eating\n", philo->id);
	ft_usleep(philo->program->args.time_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void sleeping(t_philo *philo)
{
	printf("[timestamp] %i is sleeping\n", philo->id);
	ft_usleep(philo->program->args.time_to_sleep);
}

void thinking(t_philo *philo)
{
	printf("[timestamp] %i is thinking\n", philo->id);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0) // even num delay
		ft_usleep(50);
	while (1) // todo: died condition
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}