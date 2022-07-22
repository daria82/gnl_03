/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:41:55 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/23 01:22:41 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test1.txt", O_RDONLY);
	if (fd < 0)
	{
 		printf("Error. Wrong file descriptor!");
		return(0);
	}
	printf("\tfd: (%d)", fd);
	line = (char *)malloc(sizeof(char));
	printf("\033[1;36m >>>>>go to get next line function:\n\033[0m");

//line = get_next_line(fd);
//line = get_next_line(fd);

		// line = get_next_line(fd);
		// printf("\033[1;35m(%s)\033[0m", line);
		// line = get_next_line(fd);
		// printf("\033[1;35m(%s)\033[0m", line);
		// line = get_next_line(fd);
		// printf("\033[1;35m(%s)\033[0m", line);
		// line = get_next_line(fd);
		// printf("\033[1;35m(%s)\033[0m", line);
	
	int i = 1;
	while (line != NULL && i < 16)
	{
		line = get_next_line(fd);
		//printf("\nline %d: \033[1;35m[%s]\033[0m", i, line);
		printf("\033[1;35m%s\033[0m", line);
		i++;
	}
		
	free(line);
	close(fd);
	return(0);
}
