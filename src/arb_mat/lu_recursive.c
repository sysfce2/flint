/*
    Copyright (C) 2018 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "arb_mat.h"

static void
_apply_permutation(slong * AP, arb_mat_t A, slong * P,
    slong n, slong offset)
{
    if (n != 0)
    {
        arb_ptr * Atmp;
        slong * APtmp;
        slong i;

        Atmp = flint_malloc(sizeof(arb_ptr) * n);
        APtmp = flint_malloc(sizeof(slong) * n);

        for (i = 0; i < n; i++) Atmp[i] = A->rows[P[i] + offset];
        for (i = 0; i < n; i++) A->rows[i + offset] = Atmp[i];

        for (i = 0; i < n; i++) APtmp[i] = AP[P[i] + offset];
        for (i = 0; i < n; i++) AP[i + offset] = APtmp[i];

        flint_free(Atmp);
        flint_free(APtmp);
    }
}

int
arb_mat_lu_recursive(slong * P, arb_mat_t LU, const arb_mat_t A, slong prec)
{
    slong i, m, n, r1, r2, n1;
    arb_mat_t A0, A1, A00, A01, A10, A11;
    slong * P1;

    m = A->r;
    n = A->c;

    if (m <= 1 || n <= 1)
    {
        return arb_mat_lu_classical(P, LU, A, prec);
    }

    if (LU != A)
        arb_mat_set(LU, A);

    n1 = n / 2;

    for (i = 0; i < m; i++)
        P[i] = i;

    P1 = flint_malloc(sizeof(slong) * m);
    arb_mat_window_init(A0, LU, 0, 0, m, n1);
    arb_mat_window_init(A1, LU, 0, n1, m, n);

    r1 = arb_mat_lu(P1, A0, A0, prec);

    if (!r1)
    {
        flint_free(P1);
        arb_mat_window_clear(A0);
        arb_mat_window_clear(A1);
        return 0;
    }

    /* r1 = rank of A0 */
    r1 = FLINT_MIN(m, n1);

    _apply_permutation(P, LU, P1, m, 0);

    arb_mat_window_init(A00, LU, 0, 0, r1, r1);
    arb_mat_window_init(A10, LU, r1, 0, m, r1);
    arb_mat_window_init(A01, LU, 0, n1, r1, n);
    arb_mat_window_init(A11, LU, r1, n1, m, n);

    arb_mat_solve_tril(A01, A00, A01, 1, prec);

    {
        /* arb_mat_submul(A11, A11, A10, A01, prec); */
        arb_mat_t T;
        arb_mat_init(T, A10->r, A01->c);
        arb_mat_mul(T, A10, A01, prec);
        arb_mat_sub(A11, A11, T, prec);
        arb_mat_clear(T);
    }

    r2 = arb_mat_lu(P1, A11, A11, prec);

    if (!r2)
        r1 = r2 = 0;
    else
        _apply_permutation(P, LU, P1, m - r1, r1);

    flint_free(P1);
    arb_mat_window_clear(A00);
    arb_mat_window_clear(A01);
    arb_mat_window_clear(A10);
    arb_mat_window_clear(A11);
    arb_mat_window_clear(A0);
    arb_mat_window_clear(A1);

    return r1 && r2;
}

