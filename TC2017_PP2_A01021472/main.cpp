//
//  main.cpp
//  TC2017_PP2_A01021472
//
//  Created by iCaty on 10/20/15.
//  Copyright © 2015 Catalina Peralta. All rights reserved.
//

#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/config.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/graph/exterior_property.hpp>
#include <algorithm>
#include <time.h>

using namespace boost;

struct nodo
{
    int num;
};

typedef property<vertex_attribute_t, int> num_vertice;
typedef property<edge_weight_t, int> peso_arista;
typedef adjacency_list<listS, vecS, directedS, nodo, peso_arista> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
//typedef property<vertex_distance_t, int> dist;
typedef exterior_vertex_property<Graph, int> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;

typedef property_map<Graph, edge_weight_t>::type WeightMap;

struct my_visitor
{
    typedef on_discover_vertex event_filter;
    template <typename Vertex, typename Graph>
    void operator()(Vertex t, Graph& g)
    {
        std::cout<<g[t].num<<std::endl;
    }
} vis;

bool findVertex(Graph g, int n)
{
    Graph::vertex_iterator vi, vi_end, next;
    tie(vi, vi_end) = vertices(g);
    for (next = vi; vi != vi_end; vi = next)
    {
        if (g[*vi].num == n)
            return true;
        next++;
    }
    return false;
}

int findVertexPosition(Graph g, int n)
{
    int pos = 0;
    Graph::vertex_iterator vi, vi_end, next;
    tie(vi, vi_end) = vertices(g);
    for (next = vi; vi != vi_end; vi = next)
    {
        ++next;
        if (g[*vi].num == n)
        {
            return pos;
        }
        pos++;
    }
    
    return -1;
}

int main(int argc, const char * argv[])
{
    Graph g;
    
    int opcion = -1;
    bool negativeEdge = false;
    
    while (opcion != 12)
    {
        std::cout<<"--------------APLICACION BOOST--------------"<<std::endl;
        std::cout<<"1. Insertar vertice.\n2. Insertar arista.\n3. Eliminar vertice.\n4. Eliminar arista.\n5. Realizar recorrido en profundidad.\n6. Realizar recorrido en amplitud.\n7. Realizar algoritmo de Prim.\n8. Realizar algoritmo de Kruskal.\n9. Realizar algoritmo de Dijkstra.\n10. Realizar algoritmo de Floyd-Warshall.\n11. Imprimir grafo\n12. Salir"<<std::endl;
        std::cin>>opcion;
        
        switch (opcion)
        {
            case 1:
            {
                int numero;
                
                std::cout<<"Numero: ";
                std::cin>>numero;
                
                if (findVertex(g, numero))
                    std::cout<<"Ese vertice ya existe!"<<std::endl;
                else
                {
                    Vertex vertice = add_vertex(g);
                    g[vertice].num = numero;
                }
            }
                break;
            case 2:
            {
                int num1, num2, pos1, pos2, peso;
                property_map<Graph , edge_weight_t>::type edge_distance = get(edge_weight, g);
                
                std::cout<<"Primer vertice: ";
                std::cin>>num1;
                pos1 = findVertexPosition(g, num1);
                if (pos1 != -1)
                {
                    std::cout<<"Segundo vertice: ";
                    std::cin>>num2;
                    pos2 = findVertexPosition(g, num2);
                    if (pos2 != -1)
                    {
                        std::cout<<"Peso: ";
                        std::cin>>peso;
                        
                        if (peso < 0)
                            negativeEdge = true;
                        
                        Edge edge;
                        edge = (add_edge(pos1, pos2, g)).first;
                        edge_distance[edge] = peso;
                    }
                    else
                    {
                        std::cout<<"No existe el segundo vertice."<<std::endl;
                    }
                }
                else
                {
                    std::cout<<"No existe el primer vertice."<<std::endl;
                }
            }
                break;
            case 3:
            {
                int n, pos;
                
                std::cout<<"Numero: ";
                std::cin>>n;
                
                Graph::vertex_iterator vi, vi_end, next;
                tie(vi, vi_end) = vertices(g);
                for (next = vi; vi != vi_end; vi = next)
                {
                    ++next;
                    if (g[*vi].num == n)
                    {
                        remove_vertex(*vi, g);
                        std::cout<<"Borrado!"<<std::endl;
                        break;
                    }
                }
            }
                break;
            case 4:
            {
                int n1, n2, pos;
                Vertex v1, v2;
                
                std::cout<<"Vertice 1 de la arista a borrar: ";
                std::cin>>n1;
                
                Graph::vertex_iterator vi, vi_end, next;
                tie(vi, vi_end) = vertices(g);
                for (next = vi; vi != vi_end; vi = next)
                {
                    if (g[*vi].num == n1)
                    {
                        v1 = *vi;
                        
                        std::cout<<"Vertice 2 de la arista a borrar: ";
                        std::cin>>n2;
                        
                        Graph::vertex_iterator vi, vi_end, next;
                        tie(vi, vi_end) = vertices(g);
                        
                        for (next = vi; vi != vi_end; vi = next)
                        {
                            if (g[*vi].num == n2)
                            {
                                v2 = *vi;
                                
                                remove_edge(v1, v2, g);
                                std::cout<<"Borrado!"<<std::endl;
                                break;
                            }
                            next++;
                        }
                        break;
                    }
                    
                    next++;
                }
            }
                break;
            case 5:
            {
                depth_first_search(g, visitor(make_dfs_visitor(vis)));
            }
                break;
            case 6:
            {
                breadth_first_search(g, vertex(0,g), visitor(make_bfs_visitor(vis)));
            }
                break;
            case 7:
            {
                std::vector<graph_traits<Graph>::vertex_descriptor> p(num_vertices(g));
                prim_minimum_spanning_tree(g, &p[0]);
                
                for (std::size_t i = 0; i!=p.size(); i++)
                {
                    if (p[i] != i)
                        std::cout<<g[i].num<<" --> "<<i<<std::endl;
                    else
                        std::cout<<"Comienzo: "<<g[i].num<<std::endl;
                }
            }
                break;
            case 8:
            {
                
                property_map<Graph, edge_weight_t>::type w = get(edge_weight, g);
                std::vector<graph_traits<Graph>::edge_descriptor> spanning_tree;
//                std::vector <graph_traits<Graph>::edge_descriptor> e(num_edges(g));
//                kruskal_minimum_spanning_tree(g, &e[0]);
                kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
                for (std::vector <graph_traits<Graph>::edge_descriptor>::iterator edge = spanning_tree.begin(); edge != spanning_tree.end(); edge++)
                {
                    std::cout<<g[source(*edge, g)].num<< " --> " <<g[target(*edge, g)].num<< " con peso " <<w[*edge]<< std::endl;
                }
                
            }
                break;
            case 9:
            {
                if (!negativeEdge)
                {
                    int n;
                    std::cout<<"Numero de vertice origen: ";
                    std::cin>>n;
                    
                    if (findVertex(g, n))
                    {
                        std::vector<graph_traits<Graph>::vertex_descriptor> p(num_vertices(g));
                        std::vector<int> d(num_vertices(g));
                        int pos = findVertexPosition(g, n);
                        boost::dijkstra_shortest_paths(g, pos, boost::predecessor_map(&p[0]).distance_map(&d[0]));
                        
                        std::cout<<"Resultado del algoritmo de Dijkstra: "<<std::endl;
                        Graph::vertex_iterator vi, vi_end, next;
                        tie(vi, vi_end) = vertices(g);
                        for (next = vi; vi != vi_end; vi = next)
                        {
                            std::cout<<"Distancia a "<<g[*vi].num<<": "<<d[*vi]<<std::endl;
                            std::cout<<"Padre de "<<g[*vi].num<<": "<<p[*vi]<<std::endl;
                            next++;
                        }
                    }
                    else
                        std::cout<<"No existe ese vertice en el grafo!"<<std::endl;
                    
                }
                else
                    std::cout<<"Hay una arista negativa en el grafo!"<<std::endl;
            }
                break;
            case 10:
            {
                property_map<Graph , edge_weight_t>::type edge_distance = get(edge_weight, g);
                
                DistanceMatrix dm(num_vertices(g));
                DistanceMatrixMap dmm(dm, g);
                WeightMap wm(edge_distance);
                bool good = floyd_warshall_all_pairs_shortest_paths(g, dmm, weight_map(wm));
                
                if (!good)
                    std::cout<<"Hay algún ciclo negativo en el grafo. "<<std::endl;
                else
                {
                    std::cout<<"Matriz de distancias de Floyd-Warshall: "<<std::endl;
                    for (int i = 0; i<num_vertices(g); i++)
                    {
                        for (int j = i; j<num_vertices(g); j++)
                        {
                            std::cout<<"Del vertice "<<i+1<<" al "<<j+1<<": ";
                            if (dm[i][j] == std::numeric_limits<int>::max())
                                std::cout<<"inf"<<std::endl;
                            else
                                std::cout<<dm[i][j]<<std::endl;
                        }
                        std::cout<<std::endl;
                    }
                }
            }
                break;
            case 11:
            {
                Graph::vertex_iterator vi, vi_end, next;
                tie(vi, vi_end) = vertices(g);
                for (next = vi; vi != vi_end; vi = next)
                {
                    ++next;
                    std::cout<<g[*vi].num<<std::endl;
                }
                
                Graph::edge_iterator edgeIt, edgeEnd, nextEdge;
                tie(edgeIt, edgeEnd) = edges(g);
                for (nextEdge = edgeIt; edgeIt != edgeEnd; edgeIt = nextEdge)
                {
                    std::cout<<" arista " << g[source(*edgeIt, g)].num << "-->" << g[target(*edgeIt, g)].num << " peso: "<< boost::get(edge_weight, g, *edgeIt) <<  "\n";
                    nextEdge++;
                }
//                Graph::edge_iterator ed, ed_end, next1;
//                tie(ed, ed_end) = vertices(g);
//                for (next1 = ed; ed != ed_end; ed = next1)
//                {
//                    ++next1;
//                    std::cout<<g[*ed].edge_distance<<std::endl;
//                }
            }
            case 12:
                break;
            default:
                break;
        }
    }
    return 0;
}
