#ifndef CHAOS_CODEGEN_H
#define CHAOS_CODEGEN_H
#include "parser.h"
void codegen_init(const char* filename);
void codegen_program(AstNode* program);
void codegen_finish();
#endif
