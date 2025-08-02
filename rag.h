#ifndef RAG_H
#define RAG_H

#include <stdbool.h>

void rag_add_edge(const char* from, const char* to);
void rag_remove_edge(const char* from, const char* to);
bool rag_has_cycle();
void rag_export_dot(const char* filename);

#endif
