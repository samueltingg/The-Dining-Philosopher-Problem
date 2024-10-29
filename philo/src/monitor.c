/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:11:46 by sting             #+#    #+#             */
/*   Updated: 2024/10/29 11:08:15 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// void *monitor_philos(void *ptr)
// {
// 	(void)ptr;
// 	printf("hello from monitor thread!\n");
// 	return (NULL);
// }

void *monitor_philos(void *ptr)
{
	t_program *program;

	program = (t_program *)ptr;

	// todo: (for 1 philo only) create check condition + change flag status
	while (1)
	{
		pthread_mutex_lock(&program->eat_flag_mutex);
		if (program->philos[0].eat_flag == NO && (get_current_time() - program->philos[0].last_meal >= program->args.time_to_die))
		{
			pthread_mutex_unlock(&program->eat_flag_mutex);
			pthread_mutex_lock(&program->do_flag_mutex);
			program->do_flag = NO;
			pthread_mutex_unlock(&program->do_flag_mutex);
			print_message(&program->philos[0], "died");
			break ;
		}
		pthread_mutex_unlock(&program->eat_flag_mutex);
	}
	return (NULL);
}
