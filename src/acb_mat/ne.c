/*
    Copyright (C) 2015 Tommy Hofmann

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "acb_mat.h"

int
acb_mat_ne(const acb_mat_t mat1, const acb_mat_t mat2)
{
    slong i, j;

    if ((acb_mat_nrows(mat1) != acb_mat_nrows(mat2)) ||
        (acb_mat_ncols(mat1) != acb_mat_ncols(mat2)))
        return 1;

    for (i = 0; i < acb_mat_nrows(mat1); i++)
        for (j = 0; j < acb_mat_ncols(mat1); j++)
            if (acb_ne(acb_mat_entry(mat1, i, j),
                acb_mat_entry(mat2, i, j)))
                return 1;

    return 0;
}
