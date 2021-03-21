/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:27:24 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 20:39:00 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include "hash.h"
#include "minishell.h"
#include "minunit.h"
#include "libft.h"
#include "token.h"
#include "process.h"
#include "job.h"
#include "environment.h"

t_session		*g_session;
t_session		*session;
t_hashtable	*htenv;

void			setup(void)
{
	//htenv = ht_create(128);
	//ht_set(htenv, "USER", ft_strdup("gariadno"));
	//ht_set(htenv, "SHELL", ft_strdup("minisession"));
	//ht_set(htenv, "CAKE", ft_strdup("strawberry"));
	char *envp[128] = {
		"USER=gariadno",
		"SHELL=minisession",
		"CAKE=strawberry"
	};
	htenv = load_env(envp);
	session = ft_calloc(1, sizeof(*session));
}

void	teardown(void)
{
	ht_free(htenv, free);
	free(session);
}

MU_TEST(test_ft_strspn)
{
	mu_assert_int_eq(ft_strspn("abcabcd", "abc"), strspn("abcabcd", "abc"));
	mu_assert_int_eq(ft_strspn("token 1", " "), strspn("token 1", " "));
	mu_assert_int_eq(ft_strspn("token", " "), strspn("token", " "));
	mu_assert_int_eq(ft_strspn("token", ""), strspn("token", ""));
	mu_assert_int_eq(ft_strspn("token", "y"), strspn("token", "y"));
	mu_assert_int_eq(ft_strspn("", ""), strspn("", ""));
}

MU_TEST(test_ft_strcspn)
{
	mu_assert_int_eq(strcspn("abcabcd", "abc"), ft_strcspn("abcabcd", "abc"));
	mu_assert_int_eq(strcspn("token 1", " "), ft_strcspn("token 1", " "));
	mu_assert_int_eq(strcspn("token", " "), ft_strcspn("token", " "));
	mu_assert_int_eq(strcspn("token", ""), ft_strcspn("token", ""));
	mu_assert_int_eq(strcspn("token", "y"), ft_strcspn("token", "y"));
	mu_assert_int_eq(strcspn("", ""), ft_strcspn("", ""));
}

MU_TEST(test_ft_strtok)
{
	char str[] = "This is just  a   string";

	mu_assert_string_eq(ft_strtok(str, " "), "This");
	mu_assert_string_eq(ft_strtok(NULL, " "), "is");
	mu_assert_string_eq(ft_strtok(NULL, " "), "just");
	mu_assert_string_eq(ft_strtok(NULL, " "), "a");
	mu_assert_string_eq(ft_strtok(NULL, " "), "string");
	mu_assert(ft_strtok(NULL, " ") == NULL, "Bad return value on ft_strtok");
	mu_assert_string_eq(ft_strtok(str, " "), "This");
}

MU_TEST(test_ft_strreplace)
{
	char	*str;

	str = ft_strdup("replace this with something");
	ft_strreplace(&str, "this", "that");
	mu_assert_string_eq("replace that with something", str);
	free(str);

	str = ft_strdup("replace this with this something");
	ft_strreplace(&str, "this", "that");
	mu_assert_string_eq("replace that with that something", str);
	free(str);

	str = ft_strdup("replace lilstring");
	ft_strreplace(&str, "lilstring", "bigbigbigstring");
	mu_assert_string_eq("replace bigbigbigstring", str);
	free(str);
}

MU_TEST(test_tokenizer)
{
	t_token		*tokens;
	t_token		*head;
	char		str[] = " echo>>    here    we    go; 'single quotes <<<";

	tokens = tokenizer(str, NULL);
	head = tokens;
	mu_assert_string_eq("echo", tokens->value);
	tokens = tokens->next;
	mu_assert_string_eq(">>", tokens->value);
	tokens = tokens->next;
	mu_assert_string_eq("here", tokens->value);
	tokens = tokens->next;
	mu_assert_string_eq("we", tokens->value);
	tokens = tokens->next;
	mu_assert_string_eq("go", tokens->value);
	tokens = tokens->next;
	mu_assert_string_eq(";", tokens->value);
	tokens = tokens->next;
	mu_assert_string_eq("'single quotes <<<", tokens->value);
	//ft_lstclear(&head, (void *)free_token);
}

MU_TEST(test_lexer)
{
	t_token	tk;

	tk.value = ">>";
	tk.type = T_UNDEFINED;
	lexer(&tk, htenv);
	mu_assert_int_eq(T_OAPPEND, tk.type);

	tk.value = ">";
	tk.type = T_UNDEFINED;
	lexer(&tk, htenv);
	mu_assert_int_eq(T_OREDIRECT, tk.type);

	tk.value = "<";
	tk.type = T_UNDEFINED;
	lexer(&tk, htenv);
	mu_assert_int_eq(T_IREDIRECT, tk.type);

	tk.value = ft_strdup("$CAKE");
	tk.type = T_UNDEFINED;
	lexer(&tk, htenv);
	mu_assert_int_eq(T_WORD, tk.type);
	mu_assert_string_eq("strawberry", tk.value);
	free(tk.value);

	tk.value = ft_strdup("\"$USER, this cake has $CAKE flavor.\"");
	tk.type = T_UNDEFINED;
	lexer(&tk, htenv);
	mu_assert_int_eq(T_WORD, tk.type);
	mu_assert_string_eq("gariadno, this cake has strawberry flavor.", tk.value);
	free(tk.value);

	tk.value = ft_strdup("\"\\$USER\"");
	tk.type = T_UNDEFINED;
	lexer(&tk, htenv);
	mu_assert_int_eq(T_WORD, tk.type);
	mu_assert_string_eq("$USER", tk.value);
	free(tk.value);

	tk.value = ft_strdup("\"This cake has $NOTHING flavor.\"");
	tk.type = T_UNDEFINED;
	lexer(&tk, htenv);
	mu_assert_int_eq(T_WORD, tk.type);
	mu_assert_string_eq("This cake has  flavor.", tk.value);
	free(tk.value);
}

MU_TEST(test_parser)
{
	t_job		*jobs;
	t_token		*tokens;
	t_process	*parsed;
	char		str[] = "echo >alimento 'my command' is >>appendplease  cool  < fruta < abobora | cat something > here ; VARIABLE=something a new job";
	int trunc_flags = O_WRONLY | O_CREAT | O_TRUNC;
	int append_flags = O_WRONLY | O_CREAT | O_APPEND;

	tokens = tokenizer(str, NULL);
	jobs = parser(tokens);
	parsed = jobs->process_list;
	mu_assert_string_eq("echo", parsed->command);
	mu_assert_string_eq("echo", parsed->argv[0]);
	mu_assert_string_eq("my command", parsed->argv[1]);
	mu_assert_string_eq("is", parsed->argv[2]);
	mu_assert_string_eq("cool", parsed->argv[3]);
	mu_assert_string_eq("fruta", parsed->input_file[0]->path);
	mu_assert_string_eq("abobora", parsed->input_file[1]->path);
	mu_assert_string_eq("alimento", parsed->output_file[0]->path);
	mu_assert_int_eq(trunc_flags, parsed->output_file[0]->flags);
	mu_assert_string_eq("appendplease", parsed->output_file[1]->path);
	mu_assert_int_eq(append_flags, parsed->output_file[1]->flags);
	parsed = parsed->next;
	mu_assert_string_eq("cat", parsed->argv[0]);
	mu_assert_string_eq("something", parsed->argv[1]);
	mu_assert_string_eq("here", parsed->output_file[0]->path);
	mu_assert_int_eq(trunc_flags, parsed->output_file[0]->flags);
	jobs = jobs->next;
	parsed = jobs->process_list;
	mu_assert_string_eq("a", parsed->argv[0]);
	mu_assert_string_eq("new", parsed->argv[1]);
	mu_assert_string_eq("job", parsed->argv[2]);
	mu_assert_string_eq("VARIABLE=something", parsed->local_env[0]);
}

MU_TEST(test_unload_env)
{
	char **envp;

	envp = unload_env(htenv, NULL);
	mu_assert_string_eq("CAKE=strawberry", envp[0]);
	mu_assert_string_eq("SHELL=minisession", envp[1]);
	mu_assert_string_eq("USER=gariadno", envp[2]);
	mu_assert(envp[3] == NULL, "Error: Last env not null.");
}

MU_TEST_SUITE(test_suite_tokens)
{
	MU_SUITE_CONFIGURE(&setup, &teardown);
	MU_RUN_TEST(test_ft_strspn);
	MU_RUN_TEST(test_ft_strcspn);
	MU_RUN_TEST(test_ft_strtok);
	MU_RUN_TEST(test_ft_strreplace);
	MU_RUN_TEST(test_tokenizer);
	MU_RUN_TEST(test_lexer);
	MU_RUN_TEST(test_parser);
	MU_RUN_TEST(test_unload_env);
}

int	main(void)
{
	MU_RUN_SUITE(test_suite_tokens);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
