/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:35 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/23 01:44:44 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

NEW VERSION :( 


Function name 	get_next_line
Prototype		char *get_next_line(int fd);
Turn in files	get_next_line.c, get_next_line_utils.c, get_next_line.h
Parameters fd:	The file descriptor to read from
Return value	Read line:		correct behavior
				NULL: there is nothing else to read, or an error occurred
External functs.read, malloc, free
Description		Write a function that returns a line read from a file descriptor

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line.h get_next_line_utils.c main.c
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line.h get_next_line_utils.c main.c
//("");

gcc -g -Og -std=gnu99 -Wall -Wextra -Werror -D BUFFER_SIZE=5 get_next_line.c get_next_line.h get_next_line_utils.c main.c
valgrind --leak-check=full ./a.out 

*/


#include "get_next_line.h"
# include <stdio.h> // temp! delete before finishing

/*
int ft_remtobuf(char *rem, char *buf)
{
	int x;

	ft_full_copy(buf, rem);
	//rem = ft_full_free(rem);
	x = ft_strlen(buf);
	return(x);
}
*/

char *ft_create(int i)
{
	char	*result;

	result = (char *)malloc(i * sizeof(char));
	if (result == NULL)
		return(NULL);
	*(result + (i - 1)) = '\0';
	return (result);
}

char *ft_full_free(char *tofree)
{
	free(tofree);
	return(NULL);
}

char *ft_unite(char *box, char *buf)
{
	if (box == NULL)
		return(ft_strdup(buf));
	else
		box = ft_strjoin(box, buf);
	if (box == NULL)
		return(NULL);
	return(box);
}

char *ft_formline(char *box, int n_found)
{
	char *line;
	int		i;
	
	if (!box || *box == '\0')
		return(NULL);

	line = (char *) malloc(sizeof(char) * (n_found + 2));
	if(line==NULL)
		return(NULL);

	i = 0;
	while (*(box + i) != '\n' && *(box + i) != '\0')
	{
		*(line + i) = *(box + i);
		i++;
	}
	*(line + i) = *(box + i);
	i++;
	*(line + i) = '\0';
	return(line);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < (len) && s[start + i] != '\0')
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char *ft_formbox(char *box)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*(box + i) != '\n' && *(box + i) != '\0')
		i++;
	if (*(box + i) == '\n')
		i++;
	tmp = ft_substr(box, i, (ft_strlen(box) - i));
	box = ft_full_free(box);
	box = ft_strdup(tmp);
	tmp = ft_full_free(tmp);
	return(box);
}

char *ft_load_buf(char *box, int fd)
{
	char	*buf;
	int		byte_read;

	byte_read = 1;
	while (search_n(box) == -1 && byte_read > 0)
	{
		buf = ft_create((BUFFER_SIZE + 1) * sizeof(char));
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
		{
			buf = ft_full_free(buf);
			box = ft_full_free(box);
			return(NULL);
		}
		if(byte_read == 0)
		{
			if (box)
				return(box);
			return(NULL);
		}
		*(buf + BUFFER_SIZE) = '\0';
		box = ft_unite(box, buf); 
		if (!box)
			return(NULL);
		buf = ft_full_free(buf);
	}
	return(box);
}

char *get_next_line(int fd)
{
	static char	*box;
	char		*line;
	int			n_found;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	box = ft_load_buf(box, fd);
	if (!box)
		return(NULL);
	n_found = search_n(box);
	line = ft_formline(box, n_found);
	box = ft_formbox(box);
	//printf("FINAL gnl'line=(%s), %ld\n,    gnl'box=(%s), %ld\n", line, ft_strlen(line), box, ft_strlen(box));
	return(line);
}
