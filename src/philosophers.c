/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:43:36 by snocita           #+#    #+#             */
/*   Updated: 2023/06/29 20:24:09 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_status(t_gen *gen)
{
	printf("\tThere are %d philosophers at the table\n", gen->table->members);
	printf("\tLife for them will last about %d milliseconds\n",
		gen->t_death);
	printf("\tThey take %d milliseconds to eat\n", gen->table->t_eat);
	printf("\tSleep lasts %d milliseconds\n", gen->table->t_sleep);
	if (gen->table->repas != 0)
		printf("\tThey must eat at least %d times\n", gen->table->repas);
	return ;
}

int	main(int ac, char **av)
{
	int		i;
	int		ret;
	t_gen	*gen;

	i = 1;
	gen = (t_gen *)malloc(sizeof(t_gen));
	gen->phil = (t_phil *)malloc(sizeof(t_phil));
	gen->table = (t_table *)malloc(sizeof(t_table));
	if (ac != 5 && ac != 6)
		msg_err("Faulty amount of arguments.\n\tMinimum accepted: 5");
	ret = catalysis(gen, av);
	if (ret)
	{
		my_free(gen);
		return (error_manager(ret));
	}
	if (starter(gen))
	{
		my_free(gen);
		msg_err("Error generated while creating threads");
	}
	my_free(gen);
	return (0);
}
