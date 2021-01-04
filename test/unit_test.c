/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:54:33 by aroque            #+#    #+#             */
/*   Updated: 2021/01/04 08:59:50 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include "minunit.h"
#include "minishell.h"

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
	char str[] = "This is just  one   string";

	mu_assert_int_eq(strcmp(ft_strtok(str, " "), "This"), 0);
	mu_assert_int_eq(strcmp(ft_strtok(NULL, " "), "is"), 0);
	mu_assert_int_eq(strcmp(ft_strtok(NULL, " "), "just"), 0);
	mu_assert_int_eq(strcmp(ft_strtok(NULL, " "), "one"), 0);
	mu_assert_int_eq(strcmp(ft_strtok(NULL, " "), "string"), 0);
	mu_assert(ft_strtok(NULL, " ") == NULL, "Bad return value on ft_strtok");
	mu_assert_int_eq(strcmp(ft_strtok(str, " "), "This"), 0);
}

MU_TEST_SUITE(test_suite_tokens)
{
	MU_RUN_TEST(test_ft_strspn);
	MU_RUN_TEST(test_ft_strcspn);
	MU_RUN_TEST(test_ft_strtok);
}

int	main(void)
{
	MU_RUN_SUITE(test_suite_tokens);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
