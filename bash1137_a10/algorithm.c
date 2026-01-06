/*
--------------------------------------------------
Project: a10q3
File:    algorithm.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>    
#include "heap.h"
#include "algorithm.h"
#include "graph.h"
#include "edgelist.h"

static int select_min_index(int *key, int *inset, int n) {
    int i;
    int min = INT_MAX;
    int min_idx = -1;
    for (i = 0; i < n; i++) {
        if (!inset[i] && key[i] < min) {
            min = key[i];
            min_idx = i;
        }
    }
    return min_idx;
}

EDGELIST *mst_prim(GRAPH *g, int start) {

    if (g == NULL || start < 0 || start >= g->order) return NULL;

    int n = g->order;
    int i;

    int *inMST = malloc(n * sizeof(int));
    int *key = malloc(n * sizeof(int));
    int *parent = malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        inMST[i] = 0;
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[start] = 0;

    int count;
    for (count = 0; count < n; count++) {
        int u = select_min_index(key, inMST, n);
        if (u == -1) break;
        inMST[u] = 1;

        ADJNODE *p = g->nodes[u]->neighbor;
        while (p != NULL) {
            int v = p->nid;
            int w = p->weight;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
            p = p->next;
        }
    }

    EDGELIST *res = new_edgelist();
    for (i = 0; i < n; i++) {
        if (i == start) continue;
        if (parent[i] != -1) {
            int w = get_edge_weight(g, parent[i], i);
            insert_edge_end(res, parent[i], i, w);
        }
    }

    free(inMST);
    free(key);
    free(parent);

    return res;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {

    if (g == NULL || start < 0 || start >= g->order) return NULL;

    int n = g->order;
    int i;

    int *visited = malloc(n * sizeof(int));
    int *parent = malloc(n * sizeof(int));
    int *dist = malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = INT_MAX;
    }

    dist[start] = 0;

    for (i = 0; i < n; i++) {
        int u = -1;
        int best = INT_MAX;
        int j;
        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < best) {
                best = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        ADJNODE *p = g->nodes[u]->neighbor;
        while (p != NULL) {
            int v = p->nid;
            int w = p->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
            p = p->next;
        }
    }

    EDGELIST *res = new_edgelist();
    for (i = 0; i < n; i++) {
        if (i == start) continue;
        if (parent[i] != -1) {
            int w = get_edge_weight(g, parent[i], i);
            insert_edge_end(res, parent[i], i, w);
        }
    }

    free(visited);
    free(parent);
    free(dist);

    return res;
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {

    if (g == NULL || start < 0 || start >= g->order || end < 0 || end >= g->order) return NULL;

    int n = g->order;
    int i;

    int *visited = malloc(n * sizeof(int));
    int *parent = malloc(n * sizeof(int));
    int *dist = malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = INT_MAX;
    }

    dist[start] = 0;

    for (i = 0; i < n; i++) {
        int u = -1;
        int best = INT_MAX;
        int j;
        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < best) {
                best = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        if (u == end) break; 
        visited[u] = 1;

        ADJNODE *p = g->nodes[u]->neighbor;
        while (p != NULL) {
            int v = p->nid;
            int w = p->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
            p = p->next;
        }
    }

    EDGELIST *res = new_edgelist();

    if (dist[end] == INT_MAX) {
        free(visited);
        free(parent);
        free(dist);
        return res;
    }

    int cap = 0;
    int cur = end;
    while (cur != -1) {
        cap++;
        cur = parent[cur];
    }

    int *path = malloc(cap * sizeof(int));
    int idx = 0;
    cur = end;
    while (cur != -1) {
        path[idx++] = cur;
        cur = parent[cur];
    }

    int k;
    for (k = idx - 1; k > 0; k--) {
        int u = path[k];
        int v = path[k - 1];
        int w = get_edge_weight(g, u, v);
        insert_edge_end(res, u, v, w);
    }

    free(path);
    free(visited);
    free(parent);
    free(dist);

    return res;
}
