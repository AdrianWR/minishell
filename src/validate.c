/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:35:17 by aroque            #+#    #+#             */
/*   Updated: 2021/03/19 08:24:57 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errcode.h"
#include "token.h"

int	validate_tokens(t_token *tk, char **note)
{
	unsigned	i;
	int			status;

	i = 0;
	status = 0;
	while (tk)
	{
		if ((tk->type != T_WORD && tk->next && tk->next->type != T_WORD) ||
			(tk->type != T_WORD && !tk->next))
		{
			if (tk->next || tk->type != T_SEPARATOR || !i)
			{
				status = ESYNTAX;
				*note = ft_strjoin("syntax error near token ", tk->value);
			}
		}
		tk = tk->next;
		i++;
	}
	return (status);
}
