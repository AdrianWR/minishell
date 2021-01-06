/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:11:31 by aroque            #+#    #+#             */
/*   Updated: 2021/01/05 21:27:05 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

const char	**tokenizer(char *input)
{
	size_t	i;
	char	*token;

	i = 0;
	token = strtok(input, " ");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
	return (0x0);
}
