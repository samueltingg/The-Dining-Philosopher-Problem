/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:11:46 by sting             #+#    #+#             */
/*   Updated: 2024/11/04 10:42:22by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool check_philo_death(t_program *program, int philo_index)
{
    bool is_dead = false;
	size_t time_since_last_meal;

    pthread_mutex_lock(&program->meal_mutex);
	time_since_last_meal = get_current_time() - program->philos[philo_index].last_meal;
    if (time_since_last_meal >= program->args.time_to_die)
        is_dead = true;
    pthread_mutex_unlock(&program->meal_mutex);
    return (is_dead);
}

void handle_philo_death(t_program *program, int philo_index)
{
    print_message(&program->philos[philo_index], "died");
    pthread_mutex_lock(&program->do_flag_mutex);
    program->do_flag = NO;
    pthread_mutex_unlock(&program->do_flag_mutex);
}

bool is_all_eat(t_program *program)
{
    int i;
    t_philo *philo = program->philos;

    while (1)
    {
		i = -1;
		while (++i < program->args.philo_count)
            if (philo[i].meal_count != program->args.num_times_to_eat)
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
				handle_philo_death(program, i);
				return (NULL);
			}
		}
        // TODO: is_all_eat();
        if (is_all_eat(program))
        {
            pthread_mutex_lock(&program->do_flag_mutex);
            program->do_flag = NO;
            pthread_mutex_unlock(&program->do_flag_mutex);
        }
    }
    return NULL;
}
