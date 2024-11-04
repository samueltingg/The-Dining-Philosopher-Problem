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

    pthread_mutex_lock(&program->eat_flag_mutex);
    if (program->philos[philo_index].eat_flag == NO &&
        (get_current_time() - program->philos[philo_index].last_meal >= program->args.time_to_die))
    {
        is_dead = true;
    }
    pthread_mutex_unlock(&program->eat_flag_mutex);
    return (is_dead);
}

void handle_philo_death(t_program *program, int philo_index)
{
    print_message(&program->philos[philo_index], "died");
    pthread_mutex_lock(&program->do_flag_mutex);
    program->do_flag = NO;
    pthread_mutex_unlock(&program->do_flag_mutex);
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
    }
    return NULL;
}
