/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/10/28 15:40:36 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// todo: Argv Error checking
int	check_arg(int argc)
{
	if (argc < 5)
	{
		printf("Error: Arguments should follow this format:\nnumber_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (INVALID_ARG);
	}
	return (0);
}

void create_threads(t_program *program)
{
	int i;

	program->start_time = get_current_time(); // ! storing start_time - method #1
	program->do_flag = YES;
	i = -1;
	while (++i < program->args.philo_count)
		pthread_create(&(program->philos[i].thread), NULL, philo_routine,
			(void *)&program->philos[i]);
	pthread_create(&program->monitor_thread, NULL, monitor_philos, (void *)program);
}

void join_threads(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->args.philo_count) 
		pthread_join(program->philos[i].thread, NULL);
	pthread_join(program->monitor_thread, NULL);
}

void destroy_forks(t_program *program)
{
	int i;

	i = -1;
	while (++i < program->args.philo_count)
		pthread_mutex_destroy(&program->forks[i]);
}

// NEW
int	main(int argc, char **argv)
{
	t_program	program;

	if (check_arg(argc))
		return (1);

	init_args(&program, argv, argc);
	
	if (init_mutexes(&program))
		return (1);
	pthread_mutex_init(&program.print_lock, NULL);
	if (init_philos(&program))
		return (1);
	create_threads(&program);	
	join_threads(&program);

	destroy_forks(&program);

	// TODO: create separate func for 'non-fork' mutexes
	pthread_mutex_destroy(&program.print_lock);
	pthread_mutex_destroy(&program.do_flag_mutex);

	// TODO: FREE
	free(program.philos);
	free(program.forks);
}
