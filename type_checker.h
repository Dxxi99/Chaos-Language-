#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H
#include "parser.h"
#include "type.h"

// Main entry
void check_types(AstNode* root);

// Internal helpers
ChaosType infer_type(AstNode* node);
ChaosType unify_types(ChaosType a, ChaosType b);
#endif
