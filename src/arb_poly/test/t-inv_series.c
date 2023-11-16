/*
    Copyright (C) 2012 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers.h"
#include "fmpq_poly.h"
#include "arb_poly.h"

TEST_FUNCTION_START(arb_poly_inv_series, state)
{
    slong iter;

    for (iter = 0; iter < 10000 * 0.1 * flint_test_multiplier(); iter++)
    {
        slong m, n, qbits, rbits1, rbits2;
        fmpq_poly_t A, B;
        arb_poly_t a, b;

        qbits = 2 + n_randint(state, 200);
        rbits1 = 2 + n_randint(state, 200);
        rbits2 = 2 + n_randint(state, 200);

        m = 1 + n_randint(state, 20);
        n = 1 + n_randint(state, 20);

        fmpq_poly_init(A);
        fmpq_poly_init(B);

        arb_poly_init(a);
        arb_poly_init(b);

        do {
            fmpq_poly_randtest_not_zero(A, state, m, qbits);
        } while (A->coeffs[0] == 0);

        arb_poly_randtest(b, state, 1 + n_randint(state, 20), rbits1, 5);

        fmpq_poly_inv_series(B, A, n);
        arb_poly_set_fmpq_poly(a, A, rbits1);
        arb_poly_inv_series(b, a, n, rbits2);

        if (!arb_poly_contains_fmpq_poly(b, B))
        {
            flint_printf("FAIL\n\n");
            flint_printf("bits2 = %wd\n", rbits2);

            flint_printf("A = "); fmpq_poly_print(A); flint_printf("\n\n");
            flint_printf("B = "); fmpq_poly_print(B); flint_printf("\n\n");

            flint_printf("a = "); arb_poly_printd(a, 15); flint_printf("\n\n");
            flint_printf("b = "); arb_poly_printd(b, 15); flint_printf("\n\n");

            flint_abort();
        }

        arb_poly_inv_series(a, a, n, rbits2);
        if (!arb_poly_equal(a, b))
        {
            flint_printf("FAIL (aliasing)\n\n");
            flint_abort();
        }

        fmpq_poly_clear(A);
        fmpq_poly_clear(B);

        arb_poly_clear(a);
        arb_poly_clear(b);
    }

    TEST_FUNCTION_END(state);
}
