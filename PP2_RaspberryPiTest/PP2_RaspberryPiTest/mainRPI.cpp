//
//  main.cpp
//  PP2_RaspberryPiTest
//
//  Created by iCaty on 10/21/15.
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
    
    for (int i = 0; i<14; i++)
    {
        Vertex v = add_vertex(g);
        g[v].num = i+1;
    }
    
    add_edge(0, 2, 8, g);
    add_edge(0, 3, 8, g);
    add_edge(2, 1, 7, g);
    add_edge(2, 4, 8, g);
    add_edge(2, 9, 4, g);
    add_edge(1, 4, 7, g);
    add_edge(4, 5, 9, g);
    add_edge(3, 4, 1, g);
    add_edge(3, 6, 3, g);
    add_edge(3, 7, 2, g);
    add_edge(5, 12, 4, g);
    add_edge(6, 3, 6, g);
    add_edge(7, 6, 3, g);
    add_edge(7, 8, 3, g);
    add_edge(8, 9, 2, g);
    add_edge(8, 11, 4, g);
    add_edge(9, 5, 6, g);
    add_edge(9, 2, 10, g);
    add_edge(10, 11, 6, g);
    add_edge(11, 8, 2, g);
    add_edge(11, 10, 8, g);
    add_edge(11, 13, 9, g);
    add_edge(12, 13, 6, g);
    add_edge(13, 12, 2, g);
    
    std::vector<graph_traits<Graph>::vertex_descriptor> p(num_vertices(g));
    property_map<Graph, edge_weight_t>::type w = get(edge_weight, g);
    std::vector<graph_traits<Graph>::edge_descriptor> spanning_tree;
    std::vector<int> d(num_vertices(g));
    int pos = findVertexPosition(g, 1);
    property_map<Graph , edge_weight_t>::type edge_distance = get(edge_weight, g);
    DistanceMatrix dm(num_vertices(g));
    DistanceMatrixMap dmm(dm, g);
    WeightMap wm(edge_distance);
    

    auto begin = std::chrono::high_resolution_clock::now();
    depth_first_search(g, visitor(make_dfs_visitor(vis)));
    auto end = std::chrono::high_resolution_clock::now();
    auto dfs = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"DFS: "<<dfs.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    breadth_first_search(g, vertex(0, g), visitor(make_bfs_visitor(vis)));
    end = std::chrono::high_resolution_clock::now();
    auto bfs = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"BFS: "<<bfs.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    prim_minimum_spanning_tree(g, &p[0]);
    end = std::chrono::high_resolution_clock::now();
    auto prim = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Prim: "<<prim.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
    end = std::chrono::high_resolution_clock::now();
    auto kruskal = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Kruskal: "<<kruskal.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    boost::dijkstra_shortest_paths(g, pos, boost::predecessor_map(&p[0]).distance_map(&d[0]));
    end = std::chrono::high_resolution_clock::now();
    auto dijkstra = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Dijkstra: "<<dijkstra.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    floyd_warshall_all_pairs_shortest_paths(g, dmm, weight_map(wm));
    end = std::chrono::high_resolution_clock::now();
    auto floyd_warshall = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Floyd-Warshall: "<<floyd_warshall.count()<<std::endl;
    
    
    return 0;
}
