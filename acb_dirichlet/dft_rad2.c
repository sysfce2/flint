/*
    Copyright (C) 2016 Pascal Molin

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_dirichlet.h"

/* swap each element with one with bit-reversed index */
void
acb_dirichlet_dft_rad2_reorder(acb_ptr v, slong n)
{
    slong i, j, k, l;

    for (i = 0, l = n>>1; i < l; i++)
    {
        /* j = bit reversal of i */
        for (k = 1, j = 0; k < n; k <<= 1)
        {
            j <<= 1;
            if (i & k)
                j |= 1;
        }
        if (i < j)
            acb_swap(v + i, v + j);
        else if (i > j)
            acb_swap(v + n - 1 - i, v + n - 1 - j);
        i++, j |= l;
        acb_swap(v + i, v + j);
    }

}

/* remark: can use same rad2 with smaller power of 2 */
void
acb_dirichlet_dft_rad2_precomp(acb_ptr v, acb_dirichlet_dft_rad2_t rad2, slong prec)
{
    slong j, k, l;
    slong n = rad2->n, nz = rad2->nz;
    acb_ptr p, vend = v + n, w = rad2->z;
    acb_t tmp;
    acb_init(tmp);

    for (k = 1, l = nz; k < n; k <<= 1, l >>= 1)
        for (p = v; p < vend; p += k)
            for (j = 0; j < nz; j += l, p++)
            {
                acb_mul(tmp, p + k, w + j, prec);
                acb_sub(p + k, p + 0, tmp, prec);
                acb_add(p + 0, p + 0, tmp, prec);
            }

    acb_clear(tmp);
}

void
acb_dirichlet_dft_inverse_rad2_precomp(acb_ptr v, acb_dirichlet_dft_rad2_t rad2, slong prec)
{
    slong k, n = rad2->n;
    acb_dirichlet_dft_rad2_precomp(v, rad2, prec);
    _acb_vec_scalar_mul_2exp_si(v, v, n, - rad2->e);
    for (k = 1; k < n / 2; k++)
        acb_swap(v + k, v + n - k);
}

void
acb_dirichlet_dft_rad2(acb_ptr v, int e, slong prec)
{
    acb_dirichlet_dft_rad2_t rad2;
    acb_dirichlet_dft_rad2_init(rad2, e, prec);
    acb_dirichlet_dft_rad2_precomp(v, rad2, prec);
    acb_dirichlet_dft_rad2_clear(rad2);
}
