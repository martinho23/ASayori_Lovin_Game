/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASayori_Lovin_Game.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarinha <jfarinha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 21:31:02 by jfarinha          #+#    #+#             */
/*   Updated: 2017/12/27 11:07:10 by jfarinha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASAYORI_LOVIN_GAME_H
# define ASAYORI_LOVIN_GAME_H

#include <stdio.h>
#include <stdlib.h>

	int		main(void);
	int		start(char *word, char *usedChars);
	int		getinput(char *buff, char *msg, size_t buffsize);
	char	**ft_strsplit(const char *str, char c, int *words);
	void	update(char *word, char *usedChars, char display[8][50]);
	void	putstr(char *str);
	void	msg_pause(char *msg);
	void	init_display(char display[8][50]);
	void	error(char *msg, int bool);
	void	draw(char disp[8][50],char *word,char *used, int *found, int life);

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
