/*
    Copyright (C) 2012 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "arb_poly.h"

int
_arb_poly_overlaps(arb_srcptr poly1, slong len1,
        arb_srcptr poly2, slong len2)
{
    slong i;

    for (i = 0; i < len2; i++)
        if (!arb_overlaps(poly1 + i, poly2 + i))
            return 0;

    for (i = len2; i < len1; i++)
        if (!arb_contains_zero(poly1 + i))
            return 0;

    return 1;
}

int
arb_poly_overlaps(const arb_poly_t poly1, const arb_poly_t poly2)
{
    slong len1 = poly1->length;
    slong len2 = poly2->length;

    if (len1 >= len2)
        return _arb_poly_overlaps(poly1->coeffs, len1, poly2->coeffs, len2);
    else
        return _arb_poly_overlaps(poly2->coeffs, len2, poly1->coeffs, len1);
}

