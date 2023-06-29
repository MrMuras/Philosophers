/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:43:59 by snocita           #+#    #+#             */
/*   Updated: 2023/06/29 20:21:31 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_gen	*gen)
{
	long long	i;

	i = get_timestamp();
	while (!(gen->table->died))
	{
		if (time_diff(i, get_timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	my_free(t_gen *gen)
{
	free(gen->phil);
	free(gen->table);
	free(gen);
}