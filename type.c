#include "type.h"
ChaosType unify_types(ChaosType a, ChaosType b) {
    if (a == TYPE_UNKNOWN) return b;
    if (b == TYPE_UNKNOWN) return a;
    if (a == b) return a;
    if (a == TYPE_I64 && b == TYPE_F64) return TYPE_F64;
    if (a == TYPE_F64 && b == TYPE_I64) return TYPE_F64;
    return TYPE_UNKNOWN;
}
