/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 22:59:11 by aroque            #+#    #+#             */
/*   Updated: 2021/03/13 18:48:22 by aroque           ###   ########.fr       */
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
		new->prev = last;
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
	t_file			*output;

	if (!tmp || tmp != cmd)
	{
		tmp = cmd;
		i = 0;
	}
	*tokens = (*tokens)->next;
	token = *tokens;
	if ((token)->type != T_WORD)
		return (EPARSE);
	if (!(output = malloc(sizeof(*output))))
		return (ERRSYS);
	output->path = token->value;
	output->flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	cmd->output_file[i++] = output;
	return (0);
}

int			parse_input_redirect(t_process *cmd, t_token **tokens)
{
	static unsigned	i;
	static void		*tmp;
	t_token			*token;
	t_file			*input;

	if (!tmp || tmp != cmd)
	{
		tmp = cmd;
		i = 0;
	}
	*tokens = (*tokens)->next;
	token = *tokens;
	if ((*tokens)->type != T_WORD)
		return (EPARSE);
	if (!(input = malloc(sizeof(*input))))
		return (ERRSYS);
	input->path = (*tokens)->value;
	input->flags = O_RDONLY;
	cmd->input_file[i++] = input;
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
