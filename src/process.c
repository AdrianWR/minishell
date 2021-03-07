/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 22:59:11 by aroque            #+#    #+#             */
/*   Updated: 2021/03/07 01:27:47 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "process.h"
#include "errcode.h"
#include <fcntl.h>

void		push_process(t_process **lst, t_process *new)
{
	t_process		*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void		add_to_args(char **argv, char *word)
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

int			parse_output_redirect(t_process *cmd, t_token **tokens, bool append)
{
	static unsigned	i;
	static void		*tmp;
	t_token			*token;

	if (!tmp || tmp != cmd)
	{
		tmp = cmd;
		i = 0;
	}
	*tokens = (*tokens)->next;
	token = *tokens;
	if ((token)->type != T_WORD)
		return (EPARSE);
	cmd->output_file[i].path = (token)->value;
	cmd->output_file[i].flags = O_CREAT | (append * O_APPEND);
	i++;
	return (0);
}

int			parse_input_redirect(t_process *command, t_token **tokens)
{
	t_token	*token;

	*tokens = (*tokens)->next;
	token = *tokens;
	if ((*tokens)->type != T_WORD)
		return (EPARSE);
	command->input_file.path = (*tokens)->value;
	return (0);
}

t_process	*parse_command(t_token **tokens)
{
	t_process	*command;
	bool		exit;
	unsigned	i;

	i = 0;
	exit = false;
	if (!(command = ft_calloc(1, sizeof(*command))))
		return (NULL);
	while (*tokens && !exit)
	{
		if ((*tokens)->type == T_SEPARATOR || (*tokens)->type == T_PIPE)
			exit = true;
		else if ((*tokens)->type == T_WORD)
			command->argv[i++] = (*tokens)->value;
		else if ((*tokens)->type == T_IREDIRECT)
			parse_input_redirect(command, tokens);
		else if ((*tokens)->type == T_OREDIRECT)
			parse_output_redirect(command, tokens, false);
		else if ((*tokens)->type == T_OAPPEND)
			parse_output_redirect(command, tokens, true);
		if (!exit)
			*tokens = (*tokens)->next;
	}
	return (command);
}
