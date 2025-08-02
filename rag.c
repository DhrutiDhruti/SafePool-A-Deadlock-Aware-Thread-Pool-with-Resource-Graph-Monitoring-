#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rag.h"

#define MAX_NODES 100

static int adjacency[MAX_NODES][MAX_NODES] = {0};
static char* node_names[MAX_NODES] = {0};
static int node_count = 0;

// Helper to get node index or add if not exists
static int get_node_index(const char* name) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(node_names[i], name) == 0) {
            return i;
        }
    }
    if (node_count >= MAX_NODES) {
        fprintf(stderr, "RAG Error: Exceeded max nodes\n");
        return -1;
    }

    node_names[node_count] = strdup(name);
    if (!node_names[node_count]) {
        fprintf(stderr, "Error: strdup failed for name %s\n", name);
        return -1;
    }

    return node_count++;
}

void rag_add_edge(const char* from, const char* to) {
    int i = get_node_index(from);
    int j = get_node_index(to);
    if (i >= 0 && j >= 0) {
        adjacency[i][j] = 1;
    }
}

void rag_remove_edge(const char* from, const char* to) {
    int i = get_node_index(from);
    int j = get_node_index(to);
    if (i >= 0 && j >= 0) {
        adjacency[i][j] = 0;
    }
}

static bool dfs(int node, bool* visited, bool* stack) {
    if (!visited[node]) {
        visited[node] = true;
        stack[node] = true;
        for (int j = 0; j < node_count; j++) {
            if (adjacency[node][j]) {
                if (!visited[j] && dfs(j, visited, stack)) return true;
                if (stack[j]) return true;
            }
        }
    }
    stack[node] = false;
    return false;
}

bool rag_has_cycle() {
    bool visited[MAX_NODES] = { false };
    bool stack[MAX_NODES] = { false };

    for (int i = 0; i < node_count; i++) {
        if (dfs(i, visited, stack)) return true;
    }
    return false;
}

void rag_export_dot(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to open dot file");
        return;
    }

    fprintf(fp, "digraph RAG {\n");
    for (int i = 0; i < node_count; i++) {
        fprintf(fp, "    \"%s\";\n", node_names[i]);
    }

    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            if (adjacency[i][j]) {
                fprintf(fp, "    \"%s\" -> \"%s\";\n", node_names[i], node_names[j]);
            }
        }
    }

    fprintf(fp, "}\n");
    fclose(fp);
}
