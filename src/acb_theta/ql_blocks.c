/*
    Copyright (C) 2023 Jean Kieffer

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_theta.h"

void acb_theta_ql_get_blocks(acb_mat_t tau0, acb_mat_t x, acb_mat_t tau1, slong d)
{
    slong g = acb_mat_nrows(tau);
    slong j, k;

    for (j = 0; j < d; j++)
    {
        for (k = 0; k < d; k++)
        {
            acb_set(acb_mat_entry(tau0, j, k), acb_mat_entry(tau, j, k));
        }
    }

    for (j = 0; j < d; j++)
    {
        for (k = 0; k < (g - d); k++)
        {
            acb_set(acb_mat_entry(x, j, k), acb_mat_entry(tau, j, k + d));
        }
    }

    for (j = 0; j < (g - d); j++)
    {
        for (k = 0; k < (g - d); k++)
        {
            acb_set(acb_mat_entry(tau1, j, k), acb_mat_entry(tau, j + d, k + d));
        }
    }
}
