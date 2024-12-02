/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:17:57 by sting             #+#    #+#             */
/*   Updated: 2024/12/02 11:51:16 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	if (philo->program->args.philo_count == 1)
	{
		ft_usleep(philo->program->args.time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->program->meal_mutex);
	print_message(philo, "is eating");
	philo->last_meal = get_current_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->program->meal_mutex);
	ft_usleep(philo->program->args.time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->program->args.time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->program->start_mutex);
	pthread_mutex_unlock(&philo->program->start_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		pthread_mutex_lock(&philo->program->do_flag_mutex);
		if (philo->program->do_flag == NO)
		{
			pthread_mutex_unlock(&philo->program->do_flag_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->program->do_flag_mutex);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
