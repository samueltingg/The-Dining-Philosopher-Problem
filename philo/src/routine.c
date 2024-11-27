/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:17:57 by sting             #+#    #+#             */
/*   Updated: 2024/11/27 16:29:53 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void eating(t_philo *philo)
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
	philo->last_meal = get_current_time(); // ! added
	philo->meal_count++;	
	pthread_mutex_unlock(&philo->program->meal_mutex);
	ft_usleep(philo->program->args.time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
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
	pthread_mutex_lock(&philo->program->start_mutex); // * start_lock
	pthread_mutex_unlock(&philo->program->start_mutex); // * start_lock

	if (philo->id % 2 == 0) // even num delay
		ft_usleep(50); //! why 10?

    while (1) // Loop until do_flag is NO
    {
        pthread_mutex_lock(&philo->program->do_flag_mutex); // Lock the mutex
        if (philo->program->do_flag == NO) // Check the do_flag
        {
            pthread_mutex_unlock(&philo->program->do_flag_mutex); // Unlock before breaking
            break; // Exit the loop if do_flag is NO
        }
        pthread_mutex_unlock(&philo->program->do_flag_mutex); // Unlock the mutex
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
	return (NULL);
}
