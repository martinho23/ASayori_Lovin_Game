/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASayori_Lovin_Game.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarinha <jfarinha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 21:31:02 by jfarinha          #+#    #+#             */
/*   Updated: 2017/12/26 22:49:32 by jfarinha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASAYORI_LOVIN_GAME_H
# define ASAYORI_LOVIN_GAME_H

#include <stdio.h>
#include <stdlib.h>

	int		main(void);
	int		start(char *word, char *usedChars);
	int		update(char *word);

	#ifdef _WIN32
		#define clear() system("cls")
	#else
		#ifdef __unix
			#define clear() system("clear")
		#else
			#ifndef NBLIGCLS
				#define NBLIGCLS 30
			#endif
			void	clear()
			{
				int		i;
				for(i = 0; i < NBLIGCLS; i++)
					printf("\n");
			}
		#endif
	#endif
#endif
