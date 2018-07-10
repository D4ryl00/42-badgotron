/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:49:56 by amordret          #+#    #+#             */
/*   Updated: 2018/07/10 13:44:36 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		jour	localti->tm_mday
		mois	localti->tm_mon + 1
		année	localti->tm_year - 100
		heure	localti->tm_hour
		minutes	localti->tm_min
		sec		localti->tm_sec
*/
#include "raspi.h"

void	get_temps(t_temps *now)
{
	time_t		epoch;
	struct tm	*localti;

	if ((time(&epoch)) == -1)
		error_and_exit("error calling time()");
	if ((localti = (localtime(&epoch))) == NULL)
		error_and_exit("error calling localtime()");
	now->jour = localti->tm_mday;
	now->joursem = localti->tm_wday;
	now->mois = localti->tm_mon + 1;
	now->annee = localti->tm_year - 100;
	now->heure = localti->tm_hour;
	now->minute = localti->tm_min;
	now->seconde = localti->tm_sec;
	now->epoch = epoch;
	now->isdst = localti->tm_isdst;
}
