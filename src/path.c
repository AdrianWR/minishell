/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:41:28 by aroque            #+#    #+#             */
/*   Updated: 2021/03/09 03:25:04 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		pathslen(char c, const char *path)
{
	int len;

	len = 0;
	if (*path)
		len++;
	while (*path)
		if (*path++ == ':')
			len++;
	if (c == '/' || c == '~' || c == '.')
		len = 1;
	return (len);
}

/*
** Returns a pointer to absolute
** path of a program
*/

char	*abspath(const char *argv)
{
	char	*abspath;
	char	cwd[4096 + 1];
	int		i;

	abspath = NULL;
	if (*argv == '.')
	{
		if (getcwd(cwd, 4096) == NULL)
			return (NULL);
		abspath = malloc((ft_strlen(cwd) + ft_strlen(argv) + 1) * sizeof(char));
		if (!abspath)
			return (NULL);
		i = -1;
		while (cwd[++i])
			abspath[i] = cwd[i];
		while (*argv)
			abspath[i++] = *argv++;
		return (abspath);
	}
	return (ft_strdup(argv));
}

/*
** Makes an absolute path by concatenating
** an item i of environment path with argv and
** returns a pointer of it.
*/

char	*setpath(const char *path, const char *argv, int i)
{
	char	*fpath;
	int		start;
	int		end;

	if (*argv == '/' || *argv == '~' || *argv == '.')
		return (abspath(argv));
	end = 0;
	start = 0;
	while (path[end])
		if (path[end++] == ':')
		{
			if (!i-- && end--)
				break ;
			else
				start = end;
		}
	if (!(fpath = malloc((end - start + 2 + ft_strlen(argv)) * sizeof(char))))
		return (NULL);
	i = 0;
	while (start < end)
		fpath[i++] = path[start++];
	fpath[i++] = '/';
	while (*argv)
		fpath[i++] = *argv++;
	return (fpath);
}
