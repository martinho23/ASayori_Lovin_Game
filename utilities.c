/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarinha <jfarinha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 05:46:00 by jfarinha          #+#    #+#             */
/*   Updated: 2017/12/27 15:05:47 by jfarinha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char		*ft_strsub(const char *src, int pos, int len) 
{
  char *dest=NULL;
  if (len>0) 
  {
    dest = (char *) malloc(len);
    strncat(dest,src+pos,len - 1);
  }
  return dest;
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

