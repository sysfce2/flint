/*
    Copyright (C) 2013 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers.h"
#include "arb.h"

#define ASSERT(cond) if (!(cond)) { flint_printf("FAIL: %d\n", __LINE__); flint_abort(); }

TEST_FUNCTION_START(arb_special, state)
{
    arb_t zero, pos, neg, pos_inf, neg_inf, pos_inf_err, neg_inf_err,
      zero_pm_inf, pos_pm_inf, neg_pm_inf,
      indet_exact, indet_pos_rad, indet_inf_rad;

    arb_init(zero);
    arb_init(pos);
    arb_init(neg);
    arb_init(pos_inf);
    arb_init(neg_inf);
    arb_init(pos_inf_err);
    arb_init(neg_inf_err);
    arb_init(zero_pm_inf);
    arb_init(pos_pm_inf);
    arb_init(neg_pm_inf);
    arb_init(indet_exact);
    arb_init(indet_pos_rad);
    arb_init(indet_inf_rad);

    arb_set_si(pos, 3); arb_div_ui(pos, pos, 5, 53);
    arb_neg(neg, pos);
    arb_pos_inf(pos_inf);
    arb_neg_inf(neg_inf);
    arb_pos_inf(pos_inf_err); arf_get_mag(arb_radref(pos_inf_err), arb_midref(pos));
    arb_neg(neg_inf_err, pos_inf_err);
    arb_zero_pm_inf(zero_pm_inf);
    arf_set_si(arb_midref(pos_pm_inf), 3); mag_inf(arb_radref(pos_pm_inf));
    arf_set_si(arb_midref(neg_pm_inf), -3); mag_inf(arb_radref(neg_pm_inf));
    arf_nan(arb_midref(indet_exact)); mag_zero(arb_radref(indet_exact));
    arf_nan(arb_midref(indet_pos_rad)); arf_get_mag(arb_radref(indet_pos_rad), arb_midref(pos));
    arf_nan(arb_midref(indet_inf_rad)); arf_get_mag(arb_radref(indet_inf_rad), arb_midref(pos));

    ASSERT(arb_is_zero(zero));
    ASSERT(!arb_is_zero(pos));
    ASSERT(!arb_is_zero(neg));
    ASSERT(!arb_is_zero(pos_inf));
    ASSERT(!arb_is_zero(neg_inf));
    ASSERT(!arb_is_zero(pos_inf_err));
    ASSERT(!arb_is_zero(neg_inf_err));
    ASSERT(!arb_is_zero(zero_pm_inf));
    ASSERT(!arb_is_zero(pos_pm_inf));
    ASSERT(!arb_is_zero(neg_pm_inf));
    ASSERT(!arb_is_zero(indet_exact));
    ASSERT(!arb_is_zero(indet_pos_rad));
    ASSERT(!arb_is_zero(indet_inf_rad));

    ASSERT(!arb_is_nonzero(zero));
    ASSERT(arb_is_nonzero(pos));
    ASSERT(arb_is_nonzero(neg));
    ASSERT(arb_is_nonzero(pos_inf));
    ASSERT(arb_is_nonzero(neg_inf));
    ASSERT(arb_is_nonzero(pos_inf_err));
    ASSERT(arb_is_nonzero(neg_inf_err));
    ASSERT(!arb_is_nonzero(zero_pm_inf));
    ASSERT(!arb_is_nonzero(pos_pm_inf));
    ASSERT(!arb_is_nonzero(neg_pm_inf));
    ASSERT(!arb_is_nonzero(indet_exact));
    ASSERT(!arb_is_nonzero(indet_pos_rad));
    ASSERT(!arb_is_nonzero(indet_inf_rad));

    ASSERT(!arb_is_positive(zero));
    ASSERT(arb_is_positive(pos));
    ASSERT(!arb_is_positive(neg));
    ASSERT(arb_is_positive(pos_inf));
    ASSERT(!arb_is_positive(neg_inf));
    ASSERT(arb_is_positive(pos_inf_err));
    ASSERT(!arb_is_positive(neg_inf_err));
    ASSERT(!arb_is_positive(zero_pm_inf));
    ASSERT(!arb_is_positive(pos_pm_inf));
    ASSERT(!arb_is_positive(neg_pm_inf));
    ASSERT(!arb_is_positive(indet_exact));
    ASSERT(!arb_is_positive(indet_pos_rad));
    ASSERT(!arb_is_positive(indet_inf_rad));

    ASSERT(!arb_is_negative(zero));
    ASSERT(!arb_is_negative(pos));
    ASSERT(arb_is_negative(neg));
    ASSERT(!arb_is_negative(pos_inf));
    ASSERT(arb_is_negative(neg_inf));
    ASSERT(!arb_is_negative(pos_inf_err));
    ASSERT(arb_is_negative(neg_inf_err));
    ASSERT(!arb_is_negative(zero_pm_inf));
    ASSERT(!arb_is_negative(pos_pm_inf));
    ASSERT(!arb_is_negative(neg_pm_inf));
    ASSERT(!arb_is_negative(indet_exact));
    ASSERT(!arb_is_negative(indet_pos_rad));
    ASSERT(!arb_is_negative(indet_inf_rad));

    ASSERT(arb_is_nonnegative(zero));
    ASSERT(arb_is_nonnegative(pos));
    ASSERT(!arb_is_nonnegative(neg));
    ASSERT(arb_is_nonnegative(pos_inf));
    ASSERT(!arb_is_nonnegative(neg_inf));
    ASSERT(arb_is_nonnegative(pos_inf_err));
    ASSERT(!arb_is_nonnegative(neg_inf_err));
    ASSERT(!arb_is_nonnegative(zero_pm_inf));
    ASSERT(!arb_is_nonnegative(pos_pm_inf));
    ASSERT(!arb_is_nonnegative(neg_pm_inf));
    ASSERT(!arb_is_nonnegative(indet_exact));
    ASSERT(!arb_is_nonnegative(indet_pos_rad));
    ASSERT(!arb_is_nonnegative(indet_inf_rad));

    ASSERT(arb_is_nonpositive(zero));
    ASSERT(!arb_is_nonpositive(pos));
    ASSERT(arb_is_nonpositive(neg));
    ASSERT(!arb_is_nonpositive(pos_inf));
    ASSERT(arb_is_nonpositive(neg_inf));
    ASSERT(!arb_is_nonpositive(pos_inf_err));
    ASSERT(arb_is_nonpositive(neg_inf_err));
    ASSERT(!arb_is_nonpositive(zero_pm_inf));
    ASSERT(!arb_is_nonpositive(pos_pm_inf));
    ASSERT(!arb_is_nonpositive(neg_pm_inf));
    ASSERT(!arb_is_nonpositive(indet_exact));
    ASSERT(!arb_is_nonpositive(indet_pos_rad));
    ASSERT(!arb_is_nonpositive(indet_inf_rad));

    ASSERT(!arb_contains_negative(zero));
    ASSERT(!arb_contains_negative(pos));
    ASSERT(arb_contains_negative(neg));
    ASSERT(!arb_contains_negative(pos_inf));
    ASSERT(arb_contains_negative(neg_inf));
    ASSERT(!arb_contains_negative(pos_inf_err));
    ASSERT(arb_contains_negative(neg_inf_err));
    ASSERT(arb_contains_negative(zero_pm_inf));
    ASSERT(arb_contains_negative(pos_pm_inf));
    ASSERT(arb_contains_negative(neg_pm_inf));
    ASSERT(arb_contains_negative(indet_exact));
    ASSERT(arb_contains_negative(indet_pos_rad));
    ASSERT(arb_contains_negative(indet_inf_rad));

    ASSERT(arb_contains_nonpositive(zero));
    ASSERT(!arb_contains_nonpositive(pos));
    ASSERT(arb_contains_nonpositive(neg));
    ASSERT(!arb_contains_nonpositive(pos_inf));
    ASSERT(arb_contains_nonpositive(neg_inf));
    ASSERT(!arb_contains_nonpositive(pos_inf_err));
    ASSERT(arb_contains_nonpositive(neg_inf_err));
    ASSERT(arb_contains_nonpositive(zero_pm_inf));
    ASSERT(arb_contains_nonpositive(pos_pm_inf));
    ASSERT(arb_contains_nonpositive(neg_pm_inf));
    ASSERT(arb_contains_nonpositive(indet_exact));
    ASSERT(arb_contains_nonpositive(indet_pos_rad));
    ASSERT(arb_contains_nonpositive(indet_inf_rad));

    ASSERT(!arb_contains_positive(zero));
    ASSERT(arb_contains_positive(pos));
    ASSERT(!arb_contains_positive(neg));
    ASSERT(arb_contains_positive(pos_inf));
    ASSERT(!arb_contains_positive(neg_inf));
    ASSERT(arb_contains_positive(pos_inf_err));
    ASSERT(!arb_contains_positive(neg_inf_err));
    ASSERT(arb_contains_positive(zero_pm_inf));
    ASSERT(arb_contains_positive(pos_pm_inf));
    ASSERT(arb_contains_positive(neg_pm_inf));
    ASSERT(arb_contains_positive(indet_exact));
    ASSERT(arb_contains_positive(indet_pos_rad));
    ASSERT(arb_contains_positive(indet_inf_rad));

    ASSERT(arb_contains_nonnegative(zero));
    ASSERT(arb_contains_nonnegative(pos));
    ASSERT(!arb_contains_nonnegative(neg));
    ASSERT(arb_contains_nonnegative(pos_inf));
    ASSERT(!arb_contains_nonnegative(neg_inf));
    ASSERT(arb_contains_nonnegative(pos_inf_err));
    ASSERT(!arb_contains_nonnegative(neg_inf_err));
    ASSERT(arb_contains_nonnegative(zero_pm_inf));
    ASSERT(arb_contains_nonnegative(pos_pm_inf));
    ASSERT(arb_contains_nonnegative(neg_pm_inf));
    ASSERT(arb_contains_nonnegative(indet_exact));
    ASSERT(arb_contains_nonnegative(indet_pos_rad));
    ASSERT(arb_contains_nonnegative(indet_inf_rad));

    ASSERT(arb_is_finite(zero));
    ASSERT(arb_is_finite(pos));
    ASSERT(arb_is_finite(neg));
    ASSERT(!arb_is_finite(pos_inf));
    ASSERT(!arb_is_finite(neg_inf));
    ASSERT(!arb_is_finite(pos_inf_err));
    ASSERT(!arb_is_finite(neg_inf_err));
    ASSERT(!arb_is_finite(zero_pm_inf));
    ASSERT(!arb_is_finite(pos_pm_inf));
    ASSERT(!arb_is_finite(neg_pm_inf));
    ASSERT(!arb_is_finite(indet_exact));
    ASSERT(!arb_is_finite(indet_pos_rad));
    ASSERT(!arb_is_finite(indet_inf_rad));

    ASSERT(arb_contains(zero, zero));
    ASSERT(!arb_contains(zero, pos));
    ASSERT(!arb_contains(zero, neg));
    ASSERT(!arb_contains(zero, pos_inf));
    ASSERT(!arb_contains(zero, neg_inf));
    ASSERT(!arb_contains(zero, pos_inf_err));
    ASSERT(!arb_contains(zero, neg_inf_err));
    ASSERT(!arb_contains(zero, zero_pm_inf));
    ASSERT(!arb_contains(zero, pos_pm_inf));
    ASSERT(!arb_contains(zero, neg_pm_inf));
    ASSERT(!arb_contains(zero, indet_exact));
    ASSERT(!arb_contains(zero, indet_pos_rad));
    ASSERT(!arb_contains(zero, indet_inf_rad));
    ASSERT(!arb_contains(pos, zero));
    ASSERT(arb_contains(pos, pos));
    ASSERT(!arb_contains(pos, neg));
    ASSERT(!arb_contains(pos, pos_inf));
    ASSERT(!arb_contains(pos, neg_inf));
    ASSERT(!arb_contains(pos, pos_inf_err));
    ASSERT(!arb_contains(pos, neg_inf_err));
    ASSERT(!arb_contains(pos, zero_pm_inf));
    ASSERT(!arb_contains(pos, pos_pm_inf));
    ASSERT(!arb_contains(pos, neg_pm_inf));
    ASSERT(!arb_contains(pos, indet_exact));
    ASSERT(!arb_contains(pos, indet_pos_rad));
    ASSERT(!arb_contains(pos, indet_inf_rad));
    ASSERT(!arb_contains(neg, zero));
    ASSERT(!arb_contains(neg, pos));
    ASSERT(arb_contains(neg, neg));
    ASSERT(!arb_contains(neg, pos_inf));
    ASSERT(!arb_contains(neg, neg_inf));
    ASSERT(!arb_contains(neg, pos_inf_err));
    ASSERT(!arb_contains(neg, neg_inf_err));
    ASSERT(!arb_contains(neg, zero_pm_inf));
    ASSERT(!arb_contains(neg, pos_pm_inf));
    ASSERT(!arb_contains(neg, neg_pm_inf));
    ASSERT(!arb_contains(neg, indet_exact));
    ASSERT(!arb_contains(neg, indet_pos_rad));
    ASSERT(!arb_contains(neg, indet_inf_rad));
    ASSERT(!arb_contains(pos_inf, zero));
    ASSERT(!arb_contains(pos_inf, pos));
    ASSERT(!arb_contains(pos_inf, neg));
    ASSERT(arb_contains(pos_inf, pos_inf));
    ASSERT(!arb_contains(pos_inf, neg_inf));
    ASSERT(arb_contains(pos_inf, pos_inf_err));
    ASSERT(!arb_contains(pos_inf, neg_inf_err));
    ASSERT(!arb_contains(pos_inf, zero_pm_inf));
    ASSERT(!arb_contains(pos_inf, pos_pm_inf));
    ASSERT(!arb_contains(pos_inf, neg_pm_inf));
    ASSERT(!arb_contains(pos_inf, indet_exact));
    ASSERT(!arb_contains(pos_inf, indet_pos_rad));
    ASSERT(!arb_contains(pos_inf, indet_inf_rad));
    ASSERT(!arb_contains(neg_inf, zero));
    ASSERT(!arb_contains(neg_inf, pos));
    ASSERT(!arb_contains(neg_inf, neg));
    ASSERT(!arb_contains(neg_inf, pos_inf));
    ASSERT(arb_contains(neg_inf, neg_inf));
    ASSERT(!arb_contains(neg_inf, pos_inf_err));
    ASSERT(arb_contains(neg_inf, neg_inf_err));
    ASSERT(!arb_contains(neg_inf, zero_pm_inf));
    ASSERT(!arb_contains(neg_inf, pos_pm_inf));
    ASSERT(!arb_contains(neg_inf, neg_pm_inf));
    ASSERT(!arb_contains(neg_inf, indet_exact));
    ASSERT(!arb_contains(neg_inf, indet_pos_rad));
    ASSERT(!arb_contains(neg_inf, indet_inf_rad));
    ASSERT(!arb_contains(pos_inf_err, zero));
    ASSERT(!arb_contains(pos_inf_err, pos));
    ASSERT(!arb_contains(pos_inf_err, neg));
    ASSERT(arb_contains(pos_inf_err, pos_inf));
    ASSERT(!arb_contains(pos_inf_err, neg_inf));
    ASSERT(arb_contains(pos_inf_err, pos_inf_err));
    ASSERT(!arb_contains(pos_inf_err, neg_inf_err));
    ASSERT(!arb_contains(pos_inf_err, zero_pm_inf));
    ASSERT(!arb_contains(pos_inf_err, pos_pm_inf));
    ASSERT(!arb_contains(pos_inf_err, neg_pm_inf));
    ASSERT(!arb_contains(pos_inf_err, indet_exact));
    ASSERT(!arb_contains(pos_inf_err, indet_pos_rad));
    ASSERT(!arb_contains(pos_inf_err, indet_inf_rad));
    ASSERT(!arb_contains(neg_inf_err, zero));
    ASSERT(!arb_contains(neg_inf_err, pos));
    ASSERT(!arb_contains(neg_inf_err, neg));
    ASSERT(!arb_contains(neg_inf_err, pos_inf));
    ASSERT(arb_contains(neg_inf_err, neg_inf));
    ASSERT(!arb_contains(neg_inf_err, pos_inf_err));
    ASSERT(arb_contains(neg_inf_err, neg_inf_err));
    ASSERT(!arb_contains(neg_inf_err, zero_pm_inf));
    ASSERT(!arb_contains(neg_inf_err, pos_pm_inf));
    ASSERT(!arb_contains(neg_inf_err, neg_pm_inf));
    ASSERT(!arb_contains(neg_inf_err, indet_exact));
    ASSERT(!arb_contains(neg_inf_err, indet_pos_rad));
    ASSERT(!arb_contains(neg_inf_err, indet_inf_rad));
    ASSERT(arb_contains(zero_pm_inf, zero));
    ASSERT(arb_contains(zero_pm_inf, pos));
    ASSERT(arb_contains(zero_pm_inf, neg));
    ASSERT(arb_contains(zero_pm_inf, pos_inf));
    ASSERT(arb_contains(zero_pm_inf, neg_inf));
    ASSERT(arb_contains(zero_pm_inf, pos_inf_err));
    ASSERT(arb_contains(zero_pm_inf, neg_inf_err));
    ASSERT(arb_contains(zero_pm_inf, zero_pm_inf));
    ASSERT(arb_contains(zero_pm_inf, pos_pm_inf));
    ASSERT(arb_contains(zero_pm_inf, neg_pm_inf));
    ASSERT(!arb_contains(zero_pm_inf, indet_exact));
    ASSERT(!arb_contains(zero_pm_inf, indet_pos_rad));
    ASSERT(!arb_contains(zero_pm_inf, indet_inf_rad));
    ASSERT(arb_contains(pos_pm_inf, zero));
    ASSERT(arb_contains(pos_pm_inf, pos));
    ASSERT(arb_contains(pos_pm_inf, neg));
    ASSERT(arb_contains(pos_pm_inf, pos_inf));
    ASSERT(arb_contains(pos_pm_inf, neg_inf));
    ASSERT(arb_contains(pos_pm_inf, pos_inf_err));
    ASSERT(arb_contains(pos_pm_inf, neg_inf_err));
    ASSERT(arb_contains(pos_pm_inf, zero_pm_inf));
    ASSERT(arb_contains(pos_pm_inf, pos_pm_inf));
    ASSERT(arb_contains(pos_pm_inf, neg_pm_inf));
    ASSERT(!arb_contains(pos_pm_inf, indet_exact));
    ASSERT(!arb_contains(pos_pm_inf, indet_pos_rad));
    ASSERT(!arb_contains(pos_pm_inf, indet_inf_rad));
    ASSERT(arb_contains(neg_pm_inf, zero));
    ASSERT(arb_contains(neg_pm_inf, pos));
    ASSERT(arb_contains(neg_pm_inf, neg));
    ASSERT(arb_contains(neg_pm_inf, pos_inf));
    ASSERT(arb_contains(neg_pm_inf, neg_inf));
    ASSERT(arb_contains(neg_pm_inf, pos_inf_err));
    ASSERT(arb_contains(neg_pm_inf, neg_inf_err));
    ASSERT(arb_contains(neg_pm_inf, zero_pm_inf));
    ASSERT(arb_contains(neg_pm_inf, pos_pm_inf));
    ASSERT(arb_contains(neg_pm_inf, neg_pm_inf));
    ASSERT(!arb_contains(neg_pm_inf, indet_exact));
    ASSERT(!arb_contains(neg_pm_inf, indet_pos_rad));
    ASSERT(!arb_contains(neg_pm_inf, indet_inf_rad));
    ASSERT(arb_contains(indet_exact, zero));
    ASSERT(arb_contains(indet_exact, pos));
    ASSERT(arb_contains(indet_exact, neg));
    ASSERT(arb_contains(indet_exact, pos_inf));
    ASSERT(arb_contains(indet_exact, neg_inf));
    ASSERT(arb_contains(indet_exact, pos_inf_err));
    ASSERT(arb_contains(indet_exact, neg_inf_err));
    ASSERT(arb_contains(indet_exact, zero_pm_inf));
    ASSERT(arb_contains(indet_exact, pos_pm_inf));
    ASSERT(arb_contains(indet_exact, neg_pm_inf));
    ASSERT(arb_contains(indet_exact, indet_exact));
    ASSERT(arb_contains(indet_exact, indet_pos_rad));
    ASSERT(arb_contains(indet_exact, indet_inf_rad));
    ASSERT(arb_contains(indet_pos_rad, zero));
    ASSERT(arb_contains(indet_pos_rad, pos));
    ASSERT(arb_contains(indet_pos_rad, neg));
    ASSERT(arb_contains(indet_pos_rad, pos_inf));
    ASSERT(arb_contains(indet_pos_rad, neg_inf));
    ASSERT(arb_contains(indet_pos_rad, pos_inf_err));
    ASSERT(arb_contains(indet_pos_rad, neg_inf_err));
    ASSERT(arb_contains(indet_pos_rad, zero_pm_inf));
    ASSERT(arb_contains(indet_pos_rad, pos_pm_inf));
    ASSERT(arb_contains(indet_pos_rad, neg_pm_inf));
    ASSERT(arb_contains(indet_pos_rad, indet_exact));
    ASSERT(arb_contains(indet_pos_rad, indet_pos_rad));
    ASSERT(arb_contains(indet_pos_rad, indet_inf_rad));
    ASSERT(arb_contains(indet_inf_rad, zero));
    ASSERT(arb_contains(indet_inf_rad, pos));
    ASSERT(arb_contains(indet_inf_rad, neg));
    ASSERT(arb_contains(indet_inf_rad, pos_inf));
    ASSERT(arb_contains(indet_inf_rad, neg_inf));
    ASSERT(arb_contains(indet_inf_rad, pos_inf_err));
    ASSERT(arb_contains(indet_inf_rad, neg_inf_err));
    ASSERT(arb_contains(indet_inf_rad, zero_pm_inf));
    ASSERT(arb_contains(indet_inf_rad, pos_pm_inf));
    ASSERT(arb_contains(indet_inf_rad, neg_pm_inf));
    ASSERT(arb_contains(indet_inf_rad, indet_exact));
    ASSERT(arb_contains(indet_inf_rad, indet_pos_rad));
    ASSERT(arb_contains(indet_inf_rad, indet_inf_rad));

    ASSERT(arb_overlaps(zero, zero));
    ASSERT(!arb_overlaps(zero, pos));
    ASSERT(!arb_overlaps(zero, neg));
    ASSERT(!arb_overlaps(zero, pos_inf));
    ASSERT(!arb_overlaps(zero, neg_inf));
    ASSERT(!arb_overlaps(zero, pos_inf_err));
    ASSERT(!arb_overlaps(zero, neg_inf_err));
    ASSERT(arb_overlaps(zero, zero_pm_inf));
    ASSERT(arb_overlaps(zero, pos_pm_inf));
    ASSERT(arb_overlaps(zero, neg_pm_inf));
    ASSERT(arb_overlaps(zero, indet_exact));
    ASSERT(arb_overlaps(zero, indet_pos_rad));
    ASSERT(arb_overlaps(zero, indet_inf_rad));
    ASSERT(!arb_overlaps(pos, zero));
    ASSERT(arb_overlaps(pos, pos));
    ASSERT(!arb_overlaps(pos, neg));
    ASSERT(!arb_overlaps(pos, pos_inf));
    ASSERT(!arb_overlaps(pos, neg_inf));
    ASSERT(!arb_overlaps(pos, pos_inf_err));
    ASSERT(!arb_overlaps(pos, neg_inf_err));
    ASSERT(arb_overlaps(pos, zero_pm_inf));
    ASSERT(arb_overlaps(pos, pos_pm_inf));
    ASSERT(arb_overlaps(pos, neg_pm_inf));
    ASSERT(arb_overlaps(pos, indet_exact));
    ASSERT(arb_overlaps(pos, indet_pos_rad));
    ASSERT(arb_overlaps(pos, indet_inf_rad));
    ASSERT(!arb_overlaps(neg, zero));
    ASSERT(!arb_overlaps(neg, pos));
    ASSERT(arb_overlaps(neg, neg));
    ASSERT(!arb_overlaps(neg, pos_inf));
    ASSERT(!arb_overlaps(neg, neg_inf));
    ASSERT(!arb_overlaps(neg, pos_inf_err));
    ASSERT(!arb_overlaps(neg, neg_inf_err));
    ASSERT(arb_overlaps(neg, zero_pm_inf));
    ASSERT(arb_overlaps(neg, pos_pm_inf));
    ASSERT(arb_overlaps(neg, neg_pm_inf));
    ASSERT(arb_overlaps(neg, indet_exact));
    ASSERT(arb_overlaps(neg, indet_pos_rad));
    ASSERT(arb_overlaps(neg, indet_inf_rad));
    ASSERT(!arb_overlaps(pos_inf, zero));
    ASSERT(!arb_overlaps(pos_inf, pos));
    ASSERT(!arb_overlaps(pos_inf, neg));
    ASSERT(arb_overlaps(pos_inf, pos_inf));
    ASSERT(!arb_overlaps(pos_inf, neg_inf));
    ASSERT(arb_overlaps(pos_inf, pos_inf_err));
    ASSERT(!arb_overlaps(pos_inf, neg_inf_err));
    ASSERT(arb_overlaps(pos_inf, zero_pm_inf));
    ASSERT(arb_overlaps(pos_inf, pos_pm_inf));
    ASSERT(arb_overlaps(pos_inf, neg_pm_inf));
    ASSERT(arb_overlaps(pos_inf, indet_exact));
    ASSERT(arb_overlaps(pos_inf, indet_pos_rad));
    ASSERT(arb_overlaps(pos_inf, indet_inf_rad));
    ASSERT(!arb_overlaps(neg_inf, zero));
    ASSERT(!arb_overlaps(neg_inf, pos));
    ASSERT(!arb_overlaps(neg_inf, neg));
    ASSERT(!arb_overlaps(neg_inf, pos_inf));
    ASSERT(arb_overlaps(neg_inf, neg_inf));
    ASSERT(!arb_overlaps(neg_inf, pos_inf_err));
    ASSERT(arb_overlaps(neg_inf, neg_inf_err));
    ASSERT(arb_overlaps(neg_inf, zero_pm_inf));
    ASSERT(arb_overlaps(neg_inf, pos_pm_inf));
    ASSERT(arb_overlaps(neg_inf, neg_pm_inf));
    ASSERT(arb_overlaps(neg_inf, indet_exact));
    ASSERT(arb_overlaps(neg_inf, indet_pos_rad));
    ASSERT(arb_overlaps(neg_inf, indet_inf_rad));
    ASSERT(!arb_overlaps(pos_inf_err, zero));
    ASSERT(!arb_overlaps(pos_inf_err, pos));
    ASSERT(!arb_overlaps(pos_inf_err, neg));
    ASSERT(arb_overlaps(pos_inf_err, pos_inf));
    ASSERT(!arb_overlaps(pos_inf_err, neg_inf));
    ASSERT(arb_overlaps(pos_inf_err, pos_inf_err));
    ASSERT(!arb_overlaps(pos_inf_err, neg_inf_err));
    ASSERT(arb_overlaps(pos_inf_err, zero_pm_inf));
    ASSERT(arb_overlaps(pos_inf_err, pos_pm_inf));
    ASSERT(arb_overlaps(pos_inf_err, neg_pm_inf));
    ASSERT(arb_overlaps(pos_inf_err, indet_exact));
    ASSERT(arb_overlaps(pos_inf_err, indet_pos_rad));
    ASSERT(arb_overlaps(pos_inf_err, indet_inf_rad));
    ASSERT(!arb_overlaps(neg_inf_err, zero));
    ASSERT(!arb_overlaps(neg_inf_err, pos));
    ASSERT(!arb_overlaps(neg_inf_err, neg));
    ASSERT(!arb_overlaps(neg_inf_err, pos_inf));
    ASSERT(arb_overlaps(neg_inf_err, neg_inf));
    ASSERT(!arb_overlaps(neg_inf_err, pos_inf_err));
    ASSERT(arb_overlaps(neg_inf_err, neg_inf_err));
    ASSERT(arb_overlaps(neg_inf_err, zero_pm_inf));
    ASSERT(arb_overlaps(neg_inf_err, pos_pm_inf));
    ASSERT(arb_overlaps(neg_inf_err, neg_pm_inf));
    ASSERT(arb_overlaps(neg_inf_err, indet_exact));
    ASSERT(arb_overlaps(neg_inf_err, indet_pos_rad));
    ASSERT(arb_overlaps(neg_inf_err, indet_inf_rad));
    ASSERT(arb_overlaps(zero_pm_inf, zero));
    ASSERT(arb_overlaps(zero_pm_inf, pos));
    ASSERT(arb_overlaps(zero_pm_inf, neg));
    ASSERT(arb_overlaps(zero_pm_inf, pos_inf));
    ASSERT(arb_overlaps(zero_pm_inf, neg_inf));
    ASSERT(arb_overlaps(zero_pm_inf, pos_inf_err));
    ASSERT(arb_overlaps(zero_pm_inf, neg_inf_err));
    ASSERT(arb_overlaps(zero_pm_inf, zero_pm_inf));
    ASSERT(arb_overlaps(zero_pm_inf, pos_pm_inf));
    ASSERT(arb_overlaps(zero_pm_inf, neg_pm_inf));
    ASSERT(arb_overlaps(zero_pm_inf, indet_exact));
    ASSERT(arb_overlaps(zero_pm_inf, indet_pos_rad));
    ASSERT(arb_overlaps(zero_pm_inf, indet_inf_rad));
    ASSERT(arb_overlaps(pos_pm_inf, zero));
    ASSERT(arb_overlaps(pos_pm_inf, pos));
    ASSERT(arb_overlaps(pos_pm_inf, neg));
    ASSERT(arb_overlaps(pos_pm_inf, pos_inf));
    ASSERT(arb_overlaps(pos_pm_inf, neg_inf));
    ASSERT(arb_overlaps(pos_pm_inf, pos_inf_err));
    ASSERT(arb_overlaps(pos_pm_inf, neg_inf_err));
    ASSERT(arb_overlaps(pos_pm_inf, zero_pm_inf));
    ASSERT(arb_overlaps(pos_pm_inf, pos_pm_inf));
    ASSERT(arb_overlaps(pos_pm_inf, neg_pm_inf));
    ASSERT(arb_overlaps(pos_pm_inf, indet_exact));
    ASSERT(arb_overlaps(pos_pm_inf, indet_pos_rad));
    ASSERT(arb_overlaps(pos_pm_inf, indet_inf_rad));
    ASSERT(arb_overlaps(neg_pm_inf, zero));
    ASSERT(arb_overlaps(neg_pm_inf, pos));
    ASSERT(arb_overlaps(neg_pm_inf, neg));
    ASSERT(arb_overlaps(neg_pm_inf, pos_inf));
    ASSERT(arb_overlaps(neg_pm_inf, neg_inf));
    ASSERT(arb_overlaps(neg_pm_inf, pos_inf_err));
    ASSERT(arb_overlaps(neg_pm_inf, neg_inf_err));
    ASSERT(arb_overlaps(neg_pm_inf, zero_pm_inf));
    ASSERT(arb_overlaps(neg_pm_inf, pos_pm_inf));
    ASSERT(arb_overlaps(neg_pm_inf, neg_pm_inf));
    ASSERT(arb_overlaps(neg_pm_inf, indet_exact));
    ASSERT(arb_overlaps(neg_pm_inf, indet_pos_rad));
    ASSERT(arb_overlaps(neg_pm_inf, indet_inf_rad));
    ASSERT(arb_overlaps(indet_exact, zero));
    ASSERT(arb_overlaps(indet_exact, pos));
    ASSERT(arb_overlaps(indet_exact, neg));
    ASSERT(arb_overlaps(indet_exact, pos_inf));
    ASSERT(arb_overlaps(indet_exact, neg_inf));
    ASSERT(arb_overlaps(indet_exact, pos_inf_err));
    ASSERT(arb_overlaps(indet_exact, neg_inf_err));
    ASSERT(arb_overlaps(indet_exact, zero_pm_inf));
    ASSERT(arb_overlaps(indet_exact, pos_pm_inf));
    ASSERT(arb_overlaps(indet_exact, neg_pm_inf));
    ASSERT(arb_overlaps(indet_exact, indet_exact));
    ASSERT(arb_overlaps(indet_exact, indet_pos_rad));
    ASSERT(arb_overlaps(indet_exact, indet_inf_rad));
    ASSERT(arb_overlaps(indet_pos_rad, zero));
    ASSERT(arb_overlaps(indet_pos_rad, pos));
    ASSERT(arb_overlaps(indet_pos_rad, neg));
    ASSERT(arb_overlaps(indet_pos_rad, pos_inf));
    ASSERT(arb_overlaps(indet_pos_rad, neg_inf));
    ASSERT(arb_overlaps(indet_pos_rad, pos_inf_err));
    ASSERT(arb_overlaps(indet_pos_rad, neg_inf_err));
    ASSERT(arb_overlaps(indet_pos_rad, zero_pm_inf));
    ASSERT(arb_overlaps(indet_pos_rad, pos_pm_inf));
    ASSERT(arb_overlaps(indet_pos_rad, neg_pm_inf));
    ASSERT(arb_overlaps(indet_pos_rad, indet_exact));
    ASSERT(arb_overlaps(indet_pos_rad, indet_pos_rad));
    ASSERT(arb_overlaps(indet_pos_rad, indet_inf_rad));
    ASSERT(arb_overlaps(indet_inf_rad, zero));
    ASSERT(arb_overlaps(indet_inf_rad, pos));
    ASSERT(arb_overlaps(indet_inf_rad, neg));
    ASSERT(arb_overlaps(indet_inf_rad, pos_inf));
    ASSERT(arb_overlaps(indet_inf_rad, neg_inf));
    ASSERT(arb_overlaps(indet_inf_rad, pos_inf_err));
    ASSERT(arb_overlaps(indet_inf_rad, neg_inf_err));
    ASSERT(arb_overlaps(indet_inf_rad, zero_pm_inf));
    ASSERT(arb_overlaps(indet_inf_rad, pos_pm_inf));
    ASSERT(arb_overlaps(indet_inf_rad, neg_pm_inf));
    ASSERT(arb_overlaps(indet_inf_rad, indet_exact));
    ASSERT(arb_overlaps(indet_inf_rad, indet_pos_rad));
    ASSERT(arb_overlaps(indet_inf_rad, indet_inf_rad));

    {
        fmpz_t t;
        fmpz_init(t);

        ASSERT(arb_get_unique_fmpz(t, zero));
        ASSERT(!arb_get_unique_fmpz(t, pos_inf));
        ASSERT(!arb_get_unique_fmpz(t, neg_inf));
        ASSERT(!arb_get_unique_fmpz(t, pos_inf_err));
        ASSERT(!arb_get_unique_fmpz(t, neg_inf_err));
        ASSERT(!arb_get_unique_fmpz(t, zero_pm_inf));
        ASSERT(!arb_get_unique_fmpz(t, pos_pm_inf));
        ASSERT(!arb_get_unique_fmpz(t, neg_pm_inf));
        ASSERT(!arb_get_unique_fmpz(t, indet_exact));
        ASSERT(!arb_get_unique_fmpz(t, indet_pos_rad));
        ASSERT(!arb_get_unique_fmpz(t, indet_inf_rad));

        fmpz_clear(t);
    }

    {
        arf_t b;
        slong wp = 30;

        arf_init(b);

        arb_get_abs_ubound_arf(b, zero, wp); ASSERT(arf_is_zero(b));
        arb_get_abs_ubound_arf(b, pos, wp); ASSERT(arf_sgn(b) > 0);
        arb_get_abs_ubound_arf(b, neg, wp); ASSERT(arf_sgn(b) > 0);
        arb_get_abs_ubound_arf(b, pos_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_ubound_arf(b, neg_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_ubound_arf(b, pos_inf_err, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_ubound_arf(b, neg_inf_err, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_ubound_arf(b, zero_pm_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_ubound_arf(b, indet_exact, wp); ASSERT(arf_is_nan(b));
        arb_get_abs_ubound_arf(b, indet_pos_rad, wp); ASSERT(arf_is_nan(b));
        arb_get_abs_ubound_arf(b, indet_inf_rad, wp); ASSERT(arf_is_nan(b));

        arb_get_abs_lbound_arf(b, zero, wp); ASSERT(arf_is_zero(b));
        arb_get_abs_lbound_arf(b, pos, wp); ASSERT(arf_sgn(b) > 0);
        arb_get_abs_lbound_arf(b, neg, wp); ASSERT(arf_sgn(b) > 0);
        arb_get_abs_lbound_arf(b, pos_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_lbound_arf(b, neg_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_lbound_arf(b, pos_inf_err, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_lbound_arf(b, neg_inf_err, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_abs_lbound_arf(b, zero_pm_inf, wp); ASSERT(arf_is_zero(b));
        arb_get_abs_lbound_arf(b, indet_exact, wp); ASSERT(arf_is_nan(b));
        arb_get_abs_lbound_arf(b, indet_pos_rad, wp); ASSERT(arf_is_nan(b));
        arb_get_abs_lbound_arf(b, indet_inf_rad, wp); ASSERT(arf_is_nan(b));

        arb_get_ubound_arf(b, zero, wp); ASSERT(arf_is_zero(b));
        arb_get_ubound_arf(b, pos, wp); ASSERT(arf_sgn(b) > 0);
        arb_get_ubound_arf(b, pos_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_ubound_arf(b, neg_inf, wp); ASSERT(arf_is_neg_inf(b));
        arb_get_ubound_arf(b, pos_inf_err, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_ubound_arf(b, neg_inf_err, wp); ASSERT(arf_is_neg_inf(b));
        arb_get_ubound_arf(b, zero_pm_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_ubound_arf(b, indet_exact, wp); ASSERT(arf_is_nan(b));
        arb_get_ubound_arf(b, indet_pos_rad, wp); ASSERT(arf_is_nan(b));
        arb_get_ubound_arf(b, indet_inf_rad, wp); ASSERT(arf_is_nan(b));

        arb_get_lbound_arf(b, zero, wp); ASSERT(arf_is_zero(b));
        arb_get_lbound_arf(b, neg, wp); ASSERT(arf_sgn(b) < 0);
        arb_get_lbound_arf(b, pos_inf, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_lbound_arf(b, neg_inf, wp); ASSERT(arf_is_neg_inf(b));
        arb_get_lbound_arf(b, pos_inf_err, wp); ASSERT(arf_is_pos_inf(b));
        arb_get_lbound_arf(b, neg_inf_err, wp); ASSERT(arf_is_neg_inf(b));
        arb_get_lbound_arf(b, zero_pm_inf, wp); ASSERT(arf_is_neg_inf(b));
        arb_get_lbound_arf(b, indet_exact, wp); ASSERT(arf_is_nan(b));
        arb_get_lbound_arf(b, indet_pos_rad, wp); ASSERT(arf_is_nan(b));
        arb_get_lbound_arf(b, indet_inf_rad, wp); ASSERT(arf_is_nan(b));

        arf_clear(b);
    }

    arb_clear(zero);
    arb_clear(pos);
    arb_clear(neg);
    arb_clear(pos_inf);
    arb_clear(neg_inf);
    arb_clear(pos_inf_err);
    arb_clear(neg_inf_err);
    arb_clear(zero_pm_inf);
    arb_clear(pos_pm_inf);
    arb_clear(neg_pm_inf);
    arb_clear(indet_exact);
    arb_clear(indet_pos_rad);
    arb_clear(indet_inf_rad);

    TEST_FUNCTION_END(state);
}
