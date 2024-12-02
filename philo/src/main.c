/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/12/02 11:51:33 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_arg_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Arguments should follow this format:\nnumber_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (INVALID_ARG);
	}
	return (0);
}

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

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
