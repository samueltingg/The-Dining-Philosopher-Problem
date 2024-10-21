/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/10/21 10:53:22 by sting            ###   ########.fr       */
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

void	init_philo_struct(t_philo *philo, int index, char **argv, int argc)
{
	memset(philo, 0, sizeof(t_philo));
	philo->id = index + 1;
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else 
		philo->num_times_to_eat = -1; // ? necessary?

}

// malloc philos array + init individual philo struct content
void init_philos(t_program *program, char **argv, int argc)
{
	int i;
	program->philo_count = ft_atoi(argv[1]);
	program->philos = ft_calloc(program->philo_count + 1, sizeof(t_philo));
	if (!program->philos)
	{
		printf("Error: ft_calloc");
		return (1);
	}
	// todo: init elements in each t_philo struct
	i = -1;
	while (++i < program->philo_count)
		init_philo_struct(&program->philos[i], i, argv, argc);
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
		printf("[timestamp] %i is eating\n", philo->id);
		ft_usleep(philo->time_to_eat);
		printf("[timestamp] %i is sleeping\n", philo->id);
		ft_usleep(philo->time_to_sleep);
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


// NEW
int	main(int argc, char **argv)
{
	int				i;
	t_program		program;

	if (check_arg(argc) == INVALID_ARG)
		return (INVALID_ARG);

	init_philos(&program, argv, argc);

	// todo: init mutex/forks	

	create_threads(&program);	
	join_threads(&program);

	// pthread_mutex_destroy(&mutex);

	// TODO: FREE
	free(program.philos);
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
