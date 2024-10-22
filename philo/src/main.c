/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/10/22 11:28:14 by sting            ###   ########.fr       */
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

void init_args(t_program *program, char **argv, int argc)
{
	program->args.philo_count = ft_atoi(argv[1]);
	program->args.time_to_die = ft_atoi(argv[2]);
	program->args.time_to_eat = ft_atoi(argv[3]);
	program->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->args.num_times_to_eat = ft_atoi(argv[5]);
	else 
		program->args.num_times_to_eat = -1; // ? necessary?	
}
// calloc array of forks(mutex)
// int	init_forks(t_program *program)
// {
// 	int i;

// 	program->forks = ft_calloc(program->philo_count + 1, sizeof(pthread_mutex_t));
// 	if (!program->forks)
// 	{
// 		printf("Error: ft_calloc");
// 		return (1);
// 	}
// 	i = -1;
// 	while (++i < program->philo_count)
// 		pthread_mutex_init(&program->forks[i], NULL);
// 	return (0);
// }

void	init_philo_struct(t_program	*program, int index)
{
	// memset(program->philos, 0, sizeof(t_philo));
	t_philo *philo;

	philo = &program->philos[index];
	philo->id = index + 1;
	philo->args = program->args;
	
	// todo: (REVIEW)init left_fork & right fork 
	// philo->l_fork = program->forks[index]; 
	// if (index + 1 == program->philo_count) // if last element
	// 	philo->r_fork = program->forks[0];
	// philo->r_fork = program->forks[index + 1];
}

// malloc philos array + init individual philo struct content
int init_philos(t_program *program)
{
	int i;

	program->philo_count = program->args.philo_count; // ! needed?
	program->philos = ft_calloc(program->philo_count, sizeof(t_philo));
	if (!program->philos)
	{
		printf("Error: ft_calloc");
		return (1);
	}
	i = -1;
	while (++i < program->args.philo_count)
		init_philo_struct(program, i);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0) // even num delay
		ft_usleep(50);
	while (1) // todo: died condition
	{
		// todo: take left fork
		// todo: take right fork
		// pthread_mutex_lock(&philo->l_fork);
		// pthread_mutex_lock(&philo->r_fork);
		printf("[timestamp] %i is eating\n", philo->id);
		ft_usleep(philo->args.time_to_eat);
		// pthread_mutex_unlock(&philo->l_fork);
		// pthread_mutex_unlock(&philo->r_fork); // ! STOPPED HERE
	
		printf("[timestamp] %i is sleeping\n", philo->id);
		ft_usleep(philo->args.time_to_sleep);
		printf("[timestamp] %i is thinking\n", philo->id);
	}
	return (NULL);
}

void create_threads(t_program *program)
{
	int i;

	i = -1;
	while (++i < program->philo_count)
		pthread_create(&(program->philos[i].thread), NULL, philo_routine,
			(void *)&program->philos[i]);
}

void join_threads(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->philo_count) 
		pthread_join(program->philos[i].thread, NULL);
}
/*
void destroy_forks(t_program *program)
{
	int i;

	i = -1;
	while (++i < program->philo_count)
		pthread_mutex_destroy(&program->forks[i]);
}
*/

// NEW
int	main(int argc, char **argv)
{
	t_program	program;

	if (check_arg(argc))
		return (1);

	// todo: init_args
	init_args(&program, argv, argc);
	
	// if (init_forks(&program))
	// 	return (1);
	if (init_philos(&program))
		return (1);

	create_threads(&program);	
	join_threads(&program);

	// destroy_forks(&program);
	
	// // TODO: FREE
	free(program.philos);
	// free(program.forks);
}






// int	main(int argc, char **argv)
// {
// 	t_philo			*philos;
// 	int				i;
// 	int				philo_count;

// 	if (check_arg(argc) == INVALID_ARG)
// 		return (INVALID_ARG);

// 	philo_count = ft_atoi(argv[1]);
// 	philos = ft_calloc(philo_count + 1, sizeof(t_philo));
// 	if (!philos)
// 	{
// 		printf("Error: ft_calloc");
// 		return (1);
// 	}

// 	// todo: init elements in each t_philo struct
// 	i = -1;
// 	while (++i < philo_count)
// 		init_philo_struct(&philos[i], i, argv, argc);

// 	// todo: init mutex/forks	

// 	i = -1;
// 	while (++i < philo_count)
// 		pthread_create(&(philos[i].thread), NULL, philo_routine,
// 			(void *)&philos[i]);
// 	i = -1;
// 	while (++i < philo_count)
// 		pthread_join(philos[i].thread, NULL);
// 	// pthread_mutex_destroy(&mutex);
// 	// TODO: FREE
// 	free(philos);
// }
