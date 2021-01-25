/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:27:24 by aroque            #+#    #+#             */
/*   Updated: 2021/01/25 09:15:44 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "minishell.h"
#include "minunit.h"
#include "libft.h"
#include "tokenizer.h"

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

//static void lst_compare(t_list *lst, char **split)
//{
//	static unsigned i;
//	mu_assert_string_eq(split[i], value);
//	i++;
//
//}

//MU_TEST(test_ft_tokenizer)
//{
//	t_list		*tmp;
//	t_list		*token_lst;
//	char		*token_split[] = { "echo", "here we go" };
//	unsigned	i;
//	char		*value;
//	char str[] = "echo 'here we go'";
//
//	token_lst = tokenizer(str);
//	tmp = token_lst;
//	i = 0;
//	while (token_split[i])
//	{
//		if (token_lst->content == NULL)
//			mu_fail("Incorrect parsing length.");
//		value = ((t_token *)(token_lst->content))->value;
//		if (value == NULL)
//			mu_fail("Incorrect parsing length.");
//		mu_assert_string_eq(token_split[i], value);
//		token_lst = token_lst->next;
//		i++;
//	}
//	if (token_lst->content)
//		mu_fail("Incorrect parsing length.");
//	ft_lstclear(&tmp, free);
//}

MU_TEST(test_ft_tokenizer)
{
	t_list		*tokens;
	t_list		*head;
	char		str[] = "echo>>    here    we    go; 'single quotes <<<";

	tokens = tokenizer(str);
	head = tokens;
	mu_assert_string_eq("echo", tokens->content);
	tokens = tokens->next;
	mu_assert_string_eq(">>", tokens->content);
	tokens = tokens->next;
	mu_assert_string_eq("here", tokens->content);
	tokens = tokens->next;
	mu_assert_string_eq("we", tokens->content);
	tokens = tokens->next;
	mu_assert_string_eq("go", tokens->content);
	tokens = tokens->next;
	mu_assert_string_eq(";", tokens->content);
	tokens = tokens->next;
	mu_assert_string_eq("'single quotes <<<", tokens->content);
	ft_lstclear(&head, free);
}

MU_TEST_SUITE(test_suite_tokens)
{
	MU_RUN_TEST(test_ft_strspn);
	MU_RUN_TEST(test_ft_strcspn);
	MU_RUN_TEST(test_ft_strtok);
	MU_RUN_TEST(test_ft_tokenizer);
}


int	main(void)
{
	MU_RUN_SUITE(test_suite_tokens);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
