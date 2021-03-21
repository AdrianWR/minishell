/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:33:31 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 15:26:01 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "free.h"
#include "errcode.h"
#include "libft.h"
#include "minishell.h"
#include "environment.h"
#include "get_next_line.h"

static char	*get_current_pwd(void)
{
	char	cwd[4096 + 1];
	char	*pwd;

	pwd = NULL;
	if (getcwd(cwd, 4096) == NULL)
		return (NULL);
	pwd = ft_strdup(ft_strrchr(cwd, '/') + 1);
	return (pwd);
}

void		prompt(t_hashtable *env)
{
	char *pwd;
	char *user;
	char *host;

	pwd = get_current_pwd();
	user = get_value(env, "USERNAME");
	if (!user)
		user = get_value(env, "USER");
	host = get_value(env, "HOSTNAME");
	if (!host)
		host = get_value(env, "HOST");
	if (!host)
		host = "msh";
	ft_putchar_fd('[', STDOUT_FILENO);
	ft_putstr_fd(user, STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(host, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("]$ ", STDOUT_FILENO);
	free(pwd);
}

void		eof_exit(char *input, t_session *session)
{
	ht_destroy(session->env, free_variable);
	free(input);
	free(session);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

int			token_error(t_token *tokens, t_session *session)
{
	int		status;
	char	*note;

	status = 0;
	if ((status = validate_tokens(tokens, &note)))
	{
		free_tokens(&tokens);
		status = error_message(status, note);
		free(note);
		set_exit_status(session->env, status);
	}
	return (status);
}

/*
** Main shell execution loop. REPL stands
** for Read-Eval-Print-Loop. All the process
** may be forked from REPL, and it runs until
** an 'exit' command or a SIGINT.
*/

void		repl(t_session *session)
{
	char	*input;
	t_token	*tokens;

	while (true)
	{
		signal(SIGINT, sighandler_prompt);
		signal(SIGQUIT, sighandler_prompt);
		prompt(session->env);
		if (!(get_next_line(STDIN_FILENO, &input)))
			eof_exit(input, session);
		tokens = tokenizer(input, session->env);
		free(input);
		if (!(token_error(tokens, session)))
		{
			session->jobs = parser(tokens);
			free_tokens(&tokens);
			execute_all(session);
			free_jobs(&(session->jobs));
		}
	}
}
