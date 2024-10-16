/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/10/16 10:35:03 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
void	eat(size_t millisecond, t_philo *philo) {
	// printf("")
	ft_usleep(millisecond);
}

void	sleep(void) {

}

void	think(void) {

}

*/

void	*philo_routine(void *ptr) {
	t_philo *philo;

	philo = (t_philo *)ptr;
	usleep(philo->time_to_eat * 1000); // * convert to micro
	ft_usleep(philo->time_to_eat);
	return (NULL);
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
}

int	main(int argc, char **argv)
{
	t_philo	*philo_arr;
	int	i;
	int num_of_philos;
	// pthread_mutex_t mutex;

	// todo: Argv Error checking
	if (argc < 5)
	{
		printf("Error: Arguments should follow this format:\nnumber_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	num_of_philos = ft_atoi(argv[1]);

	// todo: malloc array of t_philo
	philo_arr = ft_calloc(num_of_philos + 1, sizeof(t_philo));
	if (!philo_arr) 
	{
		printf("Error: ft_calloc");
		return (1);
	}
	
	// todo: init elemnts in each t_philo struct
	i = -1;
	while (++i < num_of_philos)
		init_philo_struct(&philo_arr[i], i, argv, argc);

	// pthread_mutex_init(&mutex, NULL);



	// i = -1;
	// while (++i < philo.num_of_philos)
	// 	pthread_create(&thread[i], NULL, philo_routine, (void *)&philo);
	// i = -1; 
	// while (++i < philo.num_of_philos)
	// 	pthread_join(thread[i], NULL);

	// pthread_mutex_destroy(&mutex);

	// TODO: FREE
	free(philo_arr);
}
