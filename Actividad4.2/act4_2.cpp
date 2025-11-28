#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <math.h>
#include <limits.h>

using namespace std;

//Estructuras para Kruskal
struct Edge {
    int u;
    int v;
    int w;
};

int findParent(int *parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = findParent(parent, parent[x]);
    return parent[x];
}

void unionSet(int *parent, int x, int y) {
    int px = findParent(parent, x);
    int py = findParent(parent, y);
    if (px != py) {
        parent[py] = px;
    }
}

//CLase Graph
class Graph
{
    public:
        int N;          
        int E;        

        bool isDirected;
        bool isWeigthed;

        double **matrix;
        int *visited;

        Graph(int, int); 

        Graph(int order, bool isD, bool isW)
        {
            N = order;
            E = 0;
            int i, j;
            isDirected = isD;
            isWeigthed = isW;

            visited = (int *) calloc(N, sizeof(int));

            matrix = new double *[N];
            for (i = 0; i < N; i++)
            {
                matrix[i] = new double [N];
                for (j = 0; j < N; j++)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        void addEdge(int, int, double);

        void topoSort();

        void Dijkstra();
        int findMin(int *, int* );

        void Prim();

        void Kruskal();

        void isCyclic(); 
};

//addEdge, agrega arista al grafo
// Complejidad: O(1)
void Graph::addEdge(int origin, int dest, double weigth)
{
    matrix[origin][dest] = weigth;

    if (isDirected == false)
    {
        matrix[dest][origin] = weigth;
    }
    E++;
}

//findMin, regresa el indice del nodo no procesado con menor distancia
//Complejidad O(N)
int Graph::findMin(int *distancias, int *procesados)
{
    int i;
    int minIndex = -1;
    int minValue = INT_MAX;

    for (i = 0; i < N; i++)
    {
        if (procesados[i] == 0 && distancias[i] < minValue)
        {
            minValue = distancias[i];
            minIndex = i;
        }
    }
    return minIndex;
}


//Dijkstra, caminos mas cortos desde un nodo origen a todos los demas
//Complejidad: O(N^2) 
void Graph::Dijkstra ( )
{
    int origen = 0; 

    int *distancias = (int *) malloc(N * sizeof(int));
    int *procesados = (int *) calloc(N, sizeof(int));
    int *desde      = (int *) malloc(N * sizeof(int));
    int i, j, u;
    int nueva_distancia;

    // Inicialización
    for (i = 0; i < N; i++)
    {
        distancias[i] = INT_MAX;
        desde[i]      = -1;
    }
    distancias[origen] = 0;


    for (i = 0; i < N; i++)
    {
        u = findMin(distancias, procesados);
        if (u == -1) {
        
            break;
        }

        procesados[u] = 1; 


        for (j = 0; j < N; j++)
        {
            if (matrix[u][j] > 0 && procesados[j] == 0)  
            {
           
                if (distancias[u] == INT_MAX) {
                    continue;
                }
                nueva_distancia = distancias[u] + (int)matrix[u][j];

                
                if (nueva_distancia < distancias[j])
                {
                    distancias[j] = nueva_distancia;
                    desde[j]      = u;
                }
            }
        }
    }

    cout << "Resultados de Dijkstra (origen = " << (char)('A' + origen) << ")" << endl;
    cout << "Nodo\tDistancia\tDesde" << endl;
    for (i = 0; i < N; i++)
    {
        cout << (char)('A' + i) << "\t";
        if (distancias[i] == INT_MAX)
            cout << "INF";
        else
            cout << distancias[i];

        cout << "\t\t";
        if (desde[i] == -1)
            cout << "-";
        else
            cout << (char)('A' + desde[i]);
        cout << endl;
    }

    free(distancias);
    free(procesados);
    free(desde);
}


//topoSort, ordenamiento topologico 
//Complejidad O(N^2) 
void Graph::topoSort ()
{
    int *inDegree = (int *) calloc(N, sizeof(int));
    int i, j;


    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (matrix[j][i] != 0)  
            {
                inDegree[i]++;
            }
        }
    }

    int *queue = (int *) malloc(N * sizeof(int));
    int front = 0;
    int back  = 0;

    for (i = 0; i < N; i++)
    {
        if (inDegree[i] == 0)
        {
            queue[back++] = i;
        }
    }

    int *orden = (int *) malloc(N * sizeof(int));
    int count = 0;

    while (front < back)
    {
        int u = queue[front++];
        orden[count++] = u;


        for (j = 0; j < N; j++)
        {
            if (matrix[u][j] != 0)   
            {
                inDegree[j]--;
                if (inDegree[j] == 0)
                {
                    queue[back++] = j;
                }
            }
        }
    }

    if (count != N)
    {
        cout << "El grafo tiene un ciclo. No existe ordenamiento topologico." << endl;
    }
    else
    {
        cout << "Orden topologico: ";
        for (i = 0; i < N; i++)
        {
            cout << (char)('A' + orden[i]) << " ";
        }
        cout << endl;
    }

    free(inDegree);
    free(queue);
    free(orden);
}


// Prim, arbol de expansion mínimo
// Complejidad: O(N^2)
void Graph::Prim()
{
    int *distancia = (int *) malloc(N * sizeof(int));
    int *procesado = (int *) calloc(N, sizeof(int));
    int *desde     = (int *) malloc(N * sizeof(int));

    int i, j, u;
    int origen = 0;
    int total = 0;


    for (i = 0; i < N; i++)
    {
        distancia[i] = INT_MAX;
        desde[i]     = -1;
    }
    distancia[origen] = 0;


    for (i = 0; i < N; i++)
    {
        u = findMin(distancia, procesado);
        if (u == -1) {
            break;
        }

        procesado[u] = 1;

        for (j = 0; j < N; j++)
        {
            if (matrix[u][j] > 0 && procesado[j] == 0)
            {
                int peso = (int)matrix[u][j];
                if (peso < distancia[j])
                {
                    distancia[j] = peso;
                    desde[j]     = u;
                }
            }
        }
    }

    cout << "Aristas del MST (Prim):" << endl;
    for (i = 0; i < N; i++)
    {
        if (i != origen && desde[i] != -1)
        {
            cout << (char)('A' + desde[i]) << " - "
                 << (char)('A' + i)
                 << "  peso = " << distancia[i] << endl;
            total += distancia[i];
        }
    }
    cout << "Costo total del MST (Prim) = " << total << endl;

    free(distancia);
    free(procesado);
    free(desde);
}

//Kruskal, arbol de expansión minimo usando aristas ordenadas
//Complejidad O(E^2)
void Graph::Kruskal()
{
    if (isDirected)
    {
        cout << "Kruskal esta definido para grafos no dirigidos." << endl;
        return;
    }

    int i, j;

    Edge *edges = (Edge *) malloc(E * sizeof(Edge));
    int edgeCount = 0;

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (matrix[i][j] > 0)
            {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].w = (int)matrix[i][j];
                edgeCount++;
            }
        }
    }


    for (i = 0; i < edgeCount - 1; i++)
    {
        for (j = i + 1; j < edgeCount; j++)
        {
            if (edges[j].w < edges[i].w)
            {
                Edge tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }


    int *parent = (int *) malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
    {
        parent[i] = i;
    }

    cout << "Aristas del MST (Kruskal):" << endl;

    int nSelected = 0;
    int k = 0;
    int total = 0;

    while (nSelected < N - 1 && k < edgeCount)
    {
        int u = edges[k].u;
        int v = edges[k].v;
        int w = edges[k].w;

        int pu = findParent(parent, u);
        int pv = findParent(parent, v);

        if (pu != pv)
        {
            cout << (char)('A' + u) << " - "
                 << (char)('A' + v)
                 << "  peso = " << w << endl;

            total += w;
            unionSet(parent, pu, pv);
            nSelected++;
        }
    
        k++;
    }

    cout << "Costo total del MST (Kruskal) = " << total << endl;

    free(edges);
    free(parent);
}

//main
int main(int argc, char* argv[])
{
    int A = 0, B = 1, C = 2, D = 3, E_ = 4, F = 5;

    Graph G1(5, 1, 0);
    G1.addEdge(A, C, 1);
    G1.addEdge(B, C, 1);
    G1.addEdge(C, D, 1);
    G1.topoSort();

    Graph G2(5, 1, 1);
    G2.addEdge(A, B, 4);
    G2.addEdge(A, C, 2);
    G2.addEdge(B, C, 3);
    G2.addEdge(B, D, 2);
    G2.addEdge(B, E_, 3);
    G2.addEdge(C, B, 1);
    G2.addEdge(C, D, 4);
    G2.addEdge(C, E_, 5);
    G2.addEdge(E_, D, 1);
    G2.Dijkstra();

    Graph G3(6, 0, 1);
    G3.addEdge(A, B, 3);
    G3.addEdge(A, E_, 6);
    G3.addEdge(A, F, 5);
    G3.addEdge(B, F, 4);
    G3.addEdge(B, C, 1);
    G3.addEdge(C, F, 4);
    G3.addEdge(C, D, 6);
    G3.addEdge(F, D, 5);
    G3.addEdge(F, E_, 2);
    G3.addEdge(D, E_, 8);
    G3.Prim();
    G3.Kruskal();

    return 0;
}

