/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASayori_Lovin_Game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarinha <jfarinha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 21:20:35 by jfarinha          #+#    #+#             */
/*   Updated: 2017/12/27 19:31:44 by jfarinha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ASayori_Lovin_Game.h"

int		main(void)
{
	char	word[46];
	char	usedChars[27];
	char	display[8][50];

	init_display(display);
	while (1)
	{
		if(start(word, usedChars) == 0)
			return (0);
		update(word, usedChars, display);
	}
	return(0);
}

void	init_display(char display[8][50])
{
	strcpy(display[7], "\n |-----\n |\n |\n |\n----");
	strcpy(display[6], "\n |-----|\n |\n |\n |\n----");
	strcpy(display[5], "\n |-----|\n |     o\n |\n |\n----");
	strcpy(display[4], "\n |-----|\n |     o\n |     |\n |\n----");
	strcpy(display[3], "\n |-----|\n |     o\n |    /|\n |\n----");
	strcpy(display[2], "\n |-----|\n |     o\n |    /|\\\n |\n----");
	strcpy(display[1], "\n |-----|\n |     o\n |    /|\\\n |    /\n----");
	strcpy(display[0], "\n |-----|\n |     o\n |    /|\\\n |    / \\\n----");
}

int		start(char *word, char *usedChars)
{
	int		type;
	int			fd;
	int			i;
	int			word_index;
	static int			word_count;
	static char	**words = NULL;
	struct stat	stbuf;

	ft_bzero(usedChars, 26);
	getinput(word, "Enter 1 to single player, 2 for 2 players or anything else\
 to quit: ", 46);
	type = atoi(word);
	if (type == 1)
	{
		if (words == NULL)
		{
			char		*buffer;

			fd = open("dictionary.txt", O_RDONLY);
			error("Couldn't open dictionary.txt press Enter to exit!\n", fd == -1);
			error("dictionary.txt is not a valid file, press Enter to exit\n", \
			(fstat(fd, &stbuf) != 0) || (!S_ISREG(stbuf.st_mode)));
			error("Couldn't load the file, press Enter to exit\n", \
			!(buffer = (char *)malloc(sizeof(char) * stbuf.st_size + 1)));
			error("Couldn't read the file, press Enter to exit!", \
			!read(fd, buffer, stbuf.st_size));
			buffer[stbuf.st_size] = '\0';
			close(fd);
			error("Couln't split the words, Press Enter to exit!", \
			!(words = ft_strsplit(buffer, '\n', &word_count)));
			srand(time(NULL));
			free(buffer);
		}
		word_index = rand() % word_count;
		strcpy(word, words[word_index]);
	}
	else if (type == 2)
	{
		getinput(word, "Player 1 enter a word with out player 2 seeing it:", 46);
		while (!strislower(word))
			getinput(word, "Not a valid word, pls enter a lower case word!: ", 46);
	}
	else
	{
		for (i = 0; i < word_count; i++)
			free(words[i]);
		free(words);
		return (0);
	}
	return (1);
}

void	draw(char disp[8][50], char *word, char *used, int *found, int life)
{
	unsigned int	i;

	i = 0;
	clear();
	putstr(disp[life]);
	putstr("\t\tWord: ");
	while (i < strlen(word))
	{
		if (found[i])
			putchar(word[i]);
		else
			putchar('_');
		i++;
	}
	putchar('\n');
	putstr("\t\tUsed Chars: [");
	putstr(used);
	putstr("]\n");
}

void	update(char *word, char *usedChars, char display[8][50])
{
	int		i;
	int		run;
	int		life;
	int		valide;
	int		char_count;
	int		word_size = strlen(word);
	int		found[word_size];
	char	c[2];

	run = 1;
	life = 7;
	char_count = 0;
	ft_bzero(found, (sizeof(int) * word_size));
	do
	{
		draw(display, word, usedChars, found, life);
		getinput(c, "Enter your choice: ", 2);
		while (!islower(c[0]) || (strchr(usedChars, c[0]) != NULL))
			getinput(c, "Your choice is not valide, enter another: ", 2);
		usedChars[char_count] = c[0];
		char_count++;
		valide = 0;
		for (i = 0; i < word_size; i++)
		{
			if (word[i] == c[0])
			{
				valide = 1;
				found[i] = 1;
			}
		}
		if (valide == 0)
			life--;
		if (life <= 0)
		{
			draw(display, word, usedChars, found, life);
			putstr("Why did you tell her you loved her! --'\n");
			run = 0;
		}
		for (i = 0; i < word_size && found[i] != 0; i++);
		if (i == word_size)
		{
			draw(display, word, usedChars, found, life);
			putstr("You see all she needed was a friend!\n");
			run = 0;
		}
	}
	while (run);
}
