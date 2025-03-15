#include "graph.h"

#define MAX_VTX 4096

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};  

/*----------------------------------------------------------------------------------------*/
Graph * graph_init()
{
    Graph *g = NULL;
    int x, y;

    if (!(g = (Graph *)malloc(sizeof(Graph))))
    {
        return NULL;
    }

    g->num_edges = 0;
    g->num_vertices = 0;

    for (x = 0; x < MAX_VTX; x++)
    {
        for (y = 0; y < MAX_VTX; y++)
        {
            g->connections[x][y] = FALSE;
        }  
    }
    
    return g;
}

/*----------------------------------------------------------------------------------------*/
void graph_free(Graph *g)
{
    int i;

    if (g != NULL)
    {
        for (i = 0; i < g->num_vertices; i++) 
        {
            vertex_free(g->vertices[i]);
        }
        free(g);
    }
}

/*----------------------------------------------------------------------------------------*/
Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *v;

    if (is_invalid_graph(g) || desc == NULL)
    {
        return ERROR;
    }

    v = vertex_initFromString(desc);

    if (v == NULL)
    {
        return ERROR;
    }

    else if (is_invalid_vertex(v))
    {
        vertex_free(v);
        return ERROR;
    }
    
    if (graph_contains(g, vertex_getId(v)))
    {
        vertex_free(v);
        return OK;
    }
    
    g->vertices[g->num_vertices] = v;
    g->num_vertices++;

    return OK;
}

/*----------------------------------------------------------------------------------------*/
Status graph_newEdge(Graph *g, long orig, long dest)
{
    int orig_index = -1;
    int dest_index = -1;
    int i;
    
    if (is_invalid_graph(g) || orig < 0 || dest < 0)
    {
        return ERROR;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == orig)
        {
            orig_index = i;
        }
        if (g->vertices[i]->id == dest)
        {
            dest_index = i;
        }
    }

    if (orig_index == -1 || dest_index == -1)
    {
        return ERROR;
    }

    g->connections[orig_index][dest_index] = TRUE;
    g->num_edges++;

    return OK;
}

/*----------------------------------------------------------------------------------------*/
Bool graph_contains(const Graph *g, long id)
{
    int i;
    
    if (is_invalid_graph(g) || id < 0)
    {
        return FALSE;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == id)
        {
            return TRUE;
        }        
    }

    return FALSE;
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfVertices(const Graph *g)
{
    if (is_invalid_graph(g))
    {
        return -1;
    }

    return g->num_vertices;
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfEdges(const Graph *g)
{
    if (is_invalid_graph(g))
    {
        return -1;
    }

    return g->num_edges;
}

/*----------------------------------------------------------------------------------------*/
Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    int orig_index = -1;
    int dest_index = -1;
    int i;
    
    if (is_invalid_graph(g) || orig < 0 || dest < 0)
    {
        return FALSE;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == orig)
        {
            orig_index = i;
        }
        if (g->vertices[i]->id == dest)
        {
            dest_index = i;
        }
    }

    if (orig_index == -1 || dest_index == -1)
    {
        return FALSE;
    }

    return g->connections[orig_index][dest_index];
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int counter = 0;
    int index = -1;
    int i;
    
    if (is_invalid_graph(g) || id < 0)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return -1;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (g->connections[index][i] == TRUE)
        {
            counter++;
        }
    }
    
    return counter;
}

/*----------------------------------------------------------------------------------------*/
long *graph_getConnectionsFromId(const Graph *g, long id)
{
    long *connections = NULL;
    int n_connections = 0;
    int counter = 0;
    int index = -1;
    int i;

    if (is_invalid_graph(g) || id < 0)
    {
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->vertices[i]->id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return NULL;
    }

    n_connections = graph_getNumberOfConnectionsFromId(g, id);

    if (n_connections == -1)
    {
        return NULL;
    }

    if (!(connections = (long *)malloc(n_connections * sizeof(long))))
    {
        return NULL;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (g->connections[index][i] == TRUE)
        {
            connections[counter] = g->vertices[i]->id;
            counter++;
        }
    }

    return connections;
}

/*----------------------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i;
    
    if (is_invalid_graph(g) || tag == NULL)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(g->vertices[i]->tag, tag) == 0)
        {
            return graph_getNumberOfConnectionsFromId(g, g->vertices[i]->id);
        }
    }

    return -1;
} 

/*----------------------------------------------------------------------------------------*/
long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int i;
    
    if (is_invalid_graph(g) || tag == NULL)
    {
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(g->vertices[i]->tag, tag) == 0)
        {
            return graph_getConnectionsFromId(g, g->vertices[i]->id);
        }
    }

    return NULL;
}

/*----------------------------------------------------------------------------------------*/
int graph_print (FILE *pf, const Graph *g)
{
    int character_counter = 0;
    int i, j;

    if (is_invalid_graph(g) || pf == NULL)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        character_counter += vertex_print(pf, g->vertices[i]);
        character_counter += fprintf(pf, ": ");
        for (j = 0; j < MAX_VTX; j++)
        {
            if (g->connections[i][j] == TRUE)
            {
                character_counter += vertex_print(pf, g->vertices[j]);
            }
        }

        character_counter += fprintf(pf, "\n");
    }

    return character_counter;
} 

/*----------------------------------------------------------------------------------------*/
Status graph_readFromFile (FILE *fin, Graph *g)
{
    int num_vertices = 0;
    char temp[MAX_DATA];
    int temp_id_orig = 0;
    int temp_id_dest = 0;
    int i;

    if (is_invalid_graph(g) || fin == NULL)
    {
        return ERROR;
    }

    fscanf(fin, "%d\n", &num_vertices);
    if (num_vertices < 0)
    {
        return ERROR;
    }

    for (i = 0; i < num_vertices; i++)
    {
        if (fgets(temp, MAX_DATA, fin) == NULL)
        {
            return ERROR;
        }
        
        if (graph_newVertex(g, temp) == ERROR)
        {
            return ERROR;
        }
    }

    while (fscanf(fin, "%d %d\n", &temp_id_orig, &temp_id_dest) == 2)
    {
        if (graph_newEdge(g, temp_id_orig, temp_id_dest) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

/*----------------------------------------------------------------------------------------*/
Bool is_invalid_graph (const Graph *g)
{
    if (g == NULL)
    {
        return TRUE;
    }

    if (g->num_vertices < 0 || g->num_vertices > MAX_VTX)
    {
        return TRUE;
    }

    if (g->num_edges < 0 || g->num_edges > MAX_VTX * MAX_VTX)
    {
        return TRUE;
    }

    return FALSE;
}