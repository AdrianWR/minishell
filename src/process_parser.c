/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 22:59:11 by aroque            #+#    #+#             */
/*   Updated: 2021/03/03 23:22:01 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "errcode.h"
#include <fcntl.h>

void	push_process(t_process **lst, t_process *new)
{
	t_process		*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	add_to_args(char **argv, char *word)
{
	static unsigned	i;
	static char		**s;

	if (!s || s != argv)
	{
		s = argv;
		i = 0;
	}
	argv[i] = word;
	i++;
}

int		parse_output_redirect(t_process *cmd, t_list **tk, bool append)
{
	static unsigned	i;
	static void		*tmp;

	if (!tmp || tmp != cmd)
	{
		tmp = cmd;
		i = 0;
	}
	*tk = (*tk)->next;
	if (((t_token *)(*tk)->content)->type != T_WORD)
		return (EPARSE);
	cmd->output_file[i].path = ((t_token *)(*tk)->content)->value;
	cmd->output_file[i].flags = O_CREAT | (append * O_APPEND);
	i++;
	return (0);
}

int		parse_input_redirect(t_process *command, t_list **tk)
{
	*tk = (*tk)->next;
	if (((t_token *)(*tk)->content)->type != T_WORD)
		return (EPARSE);
	free(command->input_file.path);
	command->input_file.path = ((t_token *)(*tk)->content)->value;
	return (0);
}
