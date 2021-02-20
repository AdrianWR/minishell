/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:27:24 by aroque            #+#    #+#             */
/*   Updated: 2021/02/13 15:24:49 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "hash.h"
#include "minishell.h"
#include "minunit.h"
#include "libft.h"
#include "tokenizer.h"
#include "ast.h"

t_shell		*shell;
t_hashtable	*htenv;
t_shell		*g_shell;

void			setup(void)
{
	htenv = ht_create(128);
	ht_set(htenv, "USER", ft_strdup("gariadno"));
	ht_set(htenv, "SHELL", ft_strdup("minishell"));
	ht_set(htenv, "CAKE", ft_strdup("strawberry"));
	shell = ft_calloc(1, sizeof(*shell));
}

void	teardown(void)
{
	ht_free(htenv, free);
	free(shell);
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
	t_list		*tokens;
	t_list		*head;
	char		str[] = " echo>>    here    we    go; 'single quotes <<<";

	shell->input = str;
	tokenizer(shell);
	tokens = shell->tokens;
	head = tokens;
	mu_assert_string_eq("echo", ((t_token *)tokens->content)->value);
	tokens = tokens->next;
	mu_assert_string_eq(">>", ((t_token *)tokens->content)->value);
	tokens = tokens->next;
	mu_assert_string_eq("here", ((t_token *)tokens->content)->value);
	tokens = tokens->next;
	mu_assert_string_eq("we", ((t_token *)tokens->content)->value);
	tokens = tokens->next;
	mu_assert_string_eq("go", ((t_token *)tokens->content)->value);
	tokens = tokens->next;
	mu_assert_string_eq(";", ((t_token *)tokens->content)->value);
	tokens = tokens->next;
	mu_assert_string_eq("'single quotes <<<", ((t_token *)tokens->content)->value);
	ft_lstclear(&head, (void *)free_token);
}

MU_TEST(test_lexer)
{
	t_token	tk;

	tk.value = ">>";
	lexer(&tk, htenv);
	mu_assert_int_eq(T_APPEND_OUTPUT, tk.type);

	tk.value = ">";
	lexer(&tk, htenv);
	mu_assert_int_eq(T_REDIRECT_OUTPUT, tk.type);

	tk.value = "<";
	lexer(&tk, htenv);
	mu_assert_int_eq(T_REDIRECT_INPUT, tk.type);

	tk.value = ft_strdup("$CAKE");
	lexer(&tk, htenv);
	mu_assert_int_eq(T_WORD, tk.type);
	mu_assert_string_eq("strawberry", tk.value);
	free(tk.value);

	tk.value = ft_strdup("\"$USER, this cake has $CAKE flavor.\"");
	lexer(&tk, htenv);
	mu_assert_int_eq(T_WORD, tk.type);
	mu_assert_string_eq("gariadno, this cake has strawberry flavor.", tk.value);
	free(tk.value);

	tk.value = ft_strdup("\"This cake has $NOTHING flavor.\"");
	lexer(&tk, htenv);
	mu_assert_int_eq(T_WORD, tk.type);
	mu_assert_string_eq("This cake has  flavor.", tk.value);
	free(tk.value);
}

//MU_TEST(test_ast)
//{
//	t_astnode	*tree;
//	t_list		*tokens;
//	char		str[] = " echo>>    here    we    go; 'single quotes <<<";
//
//	shell->input = str;
//	tokenizer(shell);
//	tokens = shell->tokens;
//	tree = ast_parser(tokens);
//}

MU_TEST(test_execute)
{
	t_astnode	*ast;
	t_astnode	*root;
	int std[2];

	std[0] = 0;
	std[1] = 1;
	ast = ft_nodenew(0x0);
	root = ast;
	ast->type = PIPE_SEQUENCE;

	ast->left = ft_nodenew(0x0);
	ast->left->type = COMMAND;

	ast->left->left = ft_nodenew(ft_strdup("echo hello teste"));
	ast->left->left->type = CMD_NAME;
	//ast->left->right = ft_nodenew(ft_strdup("hello teste"));
	//ast->left->left->type = CMD_SUFFIX;

	//ast->right = ft_nodenew(0x0);
	//ast->right->type = COMMAND;
	//ast->right->left = ft_nodenew("cat");
	//ast->right->left->type = CMD_NAME;

	pipe_execution(root, std);
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
	//MU_RUN_TEST(test_ast);
	MU_RUN_TEST(test_execute);
}

int	main(void)
{
	MU_RUN_SUITE(test_suite_tokens);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
