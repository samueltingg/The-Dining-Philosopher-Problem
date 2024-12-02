/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/12/02 12:03:02 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	create_threads(t_program *program)
{
	int	i;

	program->do_flag = YES;
	program->start_time = get_current_time();
	pthread_mutex_lock(&program->start_mutex);
	i = -1;
	while (++i < program->args.philo_count)
		pthread_create(&(program->philos[i].thread), NULL, philo_routine,
			(void *)&program->philos[i]);
	pthread_create(&program->monitor_thread, NULL, monitor_philos,
		(void *)program);
	pthread_mutex_unlock(&program->start_mutex);
}

void	join_threads(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->args.philo_count)
		pthread_join(program->philos[i].thread, NULL);
	pthread_join(program->monitor_thread, NULL);
}

void	destroy_mutexes(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->args.philo_count)
		pthread_mutex_destroy(&program->forks[i]);
	pthread_mutex_destroy(&program->print_mutex);
	pthread_mutex_destroy(&program->do_flag_mutex);
	pthread_mutex_destroy(&program->meal_mutex);
	pthread_mutex_destroy(&program->start_mutex);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (check_arg_count(argc) || check_valid_args(argv))
		return (1);
	init_args(&program, argv, argc);
	if (init_mutexes(&program))
		return (1);
	if (init_philos(&program))
		return (1);
	create_threads(&program);
	join_threads(&program);
	destroy_mutexes(&program);
	free(program.philos);
	free(program.forks);
}
