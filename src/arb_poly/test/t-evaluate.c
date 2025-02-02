/*
    Copyright (C) 2012 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers.h"
#include "fmpq.h"
#include "fmpq_poly.h"
#include "arb_poly.h"

TEST_FUNCTION_START(arb_poly_evaluate, state)
{
    slong iter;

    for (iter = 0; iter < 10000 * 0.1 * flint_test_multiplier(); iter++)
    {
        slong qbits1, qbits2, rbits1, rbits2, rbits3;
        fmpq_poly_t F;
        fmpq_t X, Y;
        arb_poly_t f;
        arb_t x, y;

        qbits1 = 2 + n_randint(state, 200);
        qbits2 = 2 + n_randint(state, 200);
        rbits1 = 2 + n_randint(state, 200);
        rbits2 = 2 + n_randint(state, 200);
        rbits3 = 2 + n_randint(state, 200);

        fmpq_poly_init(F);
        fmpq_init(X);
        fmpq_init(Y);

        arb_poly_init(f);
        arb_init(x);
        arb_init(y);

        fmpq_poly_randtest(F, state, 1 + n_randint(state, 20), qbits1);
        fmpq_randtest(X, state, qbits2);
        fmpq_poly_evaluate_fmpq(Y, F, X);

        arb_poly_set_fmpq_poly(f, F, rbits1);
        arb_set_fmpq(x, X, rbits2);
        arb_poly_evaluate(y, f, x, rbits3);

        if (!arb_contains_fmpq(y, Y))
        {
            flint_printf("FAIL\n\n");

            flint_printf("F = "); fmpq_poly_print(F); flint_printf("\n\n");
            flint_printf("X = "); fmpq_print(X); flint_printf("\n\n");
            flint_printf("Y = "); fmpq_print(Y); flint_printf("\n\n");

            flint_printf("f = "); arb_poly_printd(f, 15); flint_printf("\n\n");
            flint_printf("x = "); arb_printd(x, 15); flint_printf("\n\n");
            flint_printf("y = "); arb_printd(y, 15); flint_printf("\n\n");

            flint_abort();
        }

        /* aliasing */
        arb_poly_evaluate(x, f, x, rbits3);
        if (!arb_contains_fmpq(x, Y))
        {
            flint_printf("FAIL (aliasing)\n\n");
            flint_abort();
        }

        fmpq_poly_clear(F);
        fmpq_clear(X);
        fmpq_clear(Y);

        arb_poly_clear(f);
        arb_clear(x);
        arb_clear(y);
    }

    TEST_FUNCTION_END(state);
}
