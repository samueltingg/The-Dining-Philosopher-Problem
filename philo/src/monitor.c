/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:11:46 by sting             #+#    #+#             */
/*   Updated: 2024/12/02 10:56:30 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool check_philo_death(t_program *program, int philo_index)
{
	size_t time_since_last_meal;

    pthread_mutex_lock(&program->meal_mutex);
	time_since_last_meal = get_current_time() - program->philos[philo_index].last_meal;
    pthread_mutex_unlock(&program->meal_mutex);
    return (time_since_last_meal >= program->args.time_to_die);
}

void stop_routine(t_program *program)
{
    pthread_mutex_lock(&program->do_flag_mutex);
    program->do_flag = NO;
    pthread_mutex_unlock(&program->do_flag_mutex);
}

bool is_all_eat(t_program *program)
{
    int i;
    t_philo *philo = program->philos;
    bool eaten;

    i = -1;
    while (++i < program->args.philo_count)
    {
        pthread_mutex_lock(&program->meal_mutex);
        eaten = philo[i].meal_count >= program->args.num_times_to_eat;
        pthread_mutex_unlock(&program->meal_mutex);
        if (!eaten)
            return (false);
    }
    return (true);
}

void *monitor_philos(void *ptr)
{
    t_program *program = (t_program *)ptr;
	int	i;

    while (1)
    {
		i = -1;
		while (++i < program->args.philo_count)
		{
			if (check_philo_death(program, i))
			{
                print_message(&program->philos[i], "died");
				stop_routine(program);
				return (NULL);
			}
		}
        if (is_all_eat(program))
        {
            stop_routine(program);
            return (NULL);
        }
    }
    return (NULL);
}
