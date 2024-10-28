/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:11:46 by sting             #+#    #+#             */
/*   Updated: 2024/10/28 15:43:01 by sting            ###   ########.fr       */
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
		if (get_current_time() - program->philos[0].last_meal >= program->args.time_to_die && program->philos[0].eat_flag == NO)
		{
			pthread_mutex_lock(&program->do_flag_mutex);
			// todo: add mutex to access 'do_flag' ?
			program->do_flag = NO;
			pthread_mutex_unlock(&program->do_flag_mutex);
			print_message(&program->philos[0], "died");
			break ;
		}
	}
	return (NULL);
}