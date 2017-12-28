/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarinha <jfarinha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 05:46:00 by jfarinha          #+#    #+#             */
/*   Updated: 2017/12/28 21:08:24 by jfarinha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "ASayori_Lovin_Game.h"

void			putstr(char *str)
{
	write(1, str, strlen(str));
}

static void			cleanBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}
 
int				getinput(char *buff, char *msg, size_t buffsize)
{
	char *start = NULL;

	putstr(msg);
	if (fgets(buff, buffsize, stdin) != NULL)
	{
		start = strchr(buff, '\n');
		if (start  != NULL)
			*start  = '\0';
		else
			cleanBuffer();
		return 1;
	}
	else
	{
		cleanBuffer();
		return 0;
	}
}

int 		strislower(const char *str)
{
	unsigned int i;
	for (i = 0; i < strlen(str); i++)
		if (!islower(str[i]))
			return (0);
	return (1);
}

void			msg_pause(char *msg)
{
	putstr(msg);
	getchar();
}

void			error(char *msg, int bool)
{
	if(bool)
	{
		msg_pause(msg);
		exit(0);
	}
}

static char	*ft_strsub(const char *str, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if(!(tmp = (char *)malloc(sizeof(*tmp) * len + 1)))
		return (NULL);
	if (!str || !tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = str[i + start];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}


static int		countwords(const char *str, char c)
{
	int		words;
	int		i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static	void	split(char **tmp, const char *str, int words, char c)
{
	int		s;
	int		e;
	int		i;

	s = 0;
	e = 0;
	i = 0;
	while (i < words)
	{
		while (str[s] == c && str[s])
			s++;
		e = s + 1;
		while (str[e] != c && str[e])
			e++;
		tmp[i] = ft_strsub(str, s, (e - s));
		s = e;
		e = 0;
		i++;
	}
}

char			**ft_strsplit(const char *str, char c, int *words)
{
	char	**tmp;

	if (!str)
		return (NULL);
	*words = countwords(str, c);
	if (!(tmp = (char **)malloc(sizeof(*tmp) * (*words + 1))))
		return (NULL);
	split(tmp, str, *words, c);
	tmp[*words] = NULL;
	return (tmp);
}

void			ft_bzero(void *p, size_t len)
{
	while (len)
	{
		len--;
		((char *)p)[len] = '\0';
	}
}
