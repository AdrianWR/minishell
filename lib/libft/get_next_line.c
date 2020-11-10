/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:50:29 by aroque            #+#    #+#             */
/*   Updated: 2020/05/11 10:02:06 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static void	ft_strdel(char **str)
{
	if (*str && str)
	{
		free(*str);
		*str = NULL;
	}
}

static int	return_line(int rd, char **heap, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (rd < 0)
		return (GNL_FAILURE);
	else if (rd == 0 && *heap[0] == '\0')
	{
		*line = ft_strdup(STR_EMPTY);
		ft_strdel(heap);
		return (GNL_EOF);
	}
	while ((*heap)[i] != LBREAK && (*heap)[i] != '\0')
		i++;
	*line = ft_substr(*heap, 0, i);
	if ((*heap)[i] == LBREAK)
	{
		tmp = ft_strdup(*heap + i + 1);
		free(*heap);
		*heap = tmp;
		return (GNL_SUCCESS);
	}
	ft_strdel(heap);
	return (GNL_EOF);
}

/*
**	The get_next_line function receives a file descriptor
**  as argument and returns a char * to the **line parameter,
**	allocating the required space and returning 1 at a success,
**	-1 at failure and 0 if EOF is reached. Subsequent calls to
**	get_next_line returns subsequent lines of the file descriptor,
**	until EOF is reached. The function attempts to read no more than
**	BUFFER_SIZE bytes each time it's called.
*/

int			get_next_line(int fd, char **line)
{
	int			rd;
	char		*tmp;
	char		*buffer;
	static char	*heap[OPEN_MAX];

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (GNL_FAILURE);
	if (!(heap[fd]))
	{
		if (!(heap[fd] = ft_strdup(STR_EMPTY)))
			return (GNL_FAILURE);
	}
	if (!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer))))
		return (GNL_FAILURE);
	while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rd] = '\0';
		tmp = ft_strjoin(heap[fd], buffer);
		ft_strdel(&heap[fd]);
		heap[fd] = tmp;
		if (ft_strchr(buffer, LBREAK))
			break ;
	}
	free(buffer);
	return (return_line(rd, &(heap[fd]), line));
}
