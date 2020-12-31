/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 15:28:51 by aroque            #+#    #+#             */
/*   Updated: 2020/12/31 02:49:16 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "minunit.h"

#define HT_SIZE 128

t_hashtable	*ht;

void	setup(void)
{
	ht = ht_create(HT_SIZE);
}

void	teardown(void)
{
	ht_free(ht, 0x0);
}

MU_TEST(test_ht_set_get) {
	mu_assert(ht_set(ht, "cake", "banana") == 0, "Couldn't set key-value pair.");
	mu_assert(ht_set(ht, "juice", "orange") == 0, "Couldn't set key-value pair.");
	mu_assert(ht_set(ht, "soda", "lemon") == 0, "Couldn't set key-value pair.");
	mu_assert(!strcmp(ht_get(ht, "cake"), "banana"), "Error on getting value.");
	mu_assert(!strcmp(ht_get(ht, "juice"), "orange"), "Error on getting value.");
	mu_assert(!strcmp(ht_get(ht, "soda"), "lemon"), "Error on getting value.");
}

MU_TEST(test_ht_get_null)
{
	mu_assert(ht_get(ht, "sandwich") == NULL, "Error on getting value return.");
	mu_assert(ht_get(ht, "") == NULL, "Error on getting value return.");
}

MU_TEST(test_ht_remove)
{
	ht_remove(ht, "soda", 0x0);
	mu_assert(ht_get(ht, "soda") == NULL, "Error on deleting key-value pair.");
	ht_remove(ht, "cake", 0x0);
	mu_assert(ht_get(ht, "cake") == NULL, "Error on deleting key-value pair.");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&setup, &teardown);
	MU_RUN_TEST(test_ht_set_get);
	MU_RUN_TEST(test_ht_get_null);
	MU_RUN_TEST(test_ht_remove);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
