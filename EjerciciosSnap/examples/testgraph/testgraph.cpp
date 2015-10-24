/*
El algoritmo de Prim implementado en este trabajo tiene una complejidad temporal de n² en el peor caso, y una complejidad espacial de n
El algoritmo de Floyd-Warshal implementado en este trabajo tiene una complejidad temporal de n³ en el peor caso y una complejidad espacial de n
El algoritmo de Dijkstra implementado en este trabajo tiene una complejidad temporal de n² en el peor caso y una complejidad espacial de n
El algoritmo de Kruskal implementado en este trabajo tiene una complejidad temporal de E log V en el peor caso y una complejidad espacial de n
*/

#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include "stdafx.h"

void Prim(TPt<TNodeEDatNet<TInt,TFlt> >);
void Floyd(TPt<TNodeEDatNet<TInt,TFlt> >);
void Dijkstra(TPt<TNodeEDatNet<TInt,TFlt> >, int);
void Kruskal(TPt<TNodeEDatNet<TInt, TFlt> >);

class Vis
{
	public:
	Vis() {}
	Vis(int Nodes){}
	void DiscoverNode(const int& nodeId) {printf ("%i\n",nodeId);}
	void FinishNode(const int& nodeId){}
	void ExamineEdge (const int& nodeID1,const int& nodeID2) {}
	void TreeEdge (const int& nodeID1,const int& nodeID2) {}
	void BackEdge (const int& nodeID1,const int& nodeID2) {}
	void FwdEdge (const int& nodeID1,const int& nodeID2) {}
};

int main(int argc, char* argv[]) 
{
	TPt<TNodeEDatNet<TInt,TFlt> > G = TNodeEDatNet<TInt,TFlt>::New();

  	G->AddNode(1);
  	G->AddNode(2);
  	G->AddNode(3);
  	G->AddNode(4);
  	G->AddNode(5);
  	G->AddNode(6);
  	G->AddNode(7);
  	G->AddNode(8);
  	G->AddNode(9);
  	G->AddNode(10);
  	G->AddNode(11);
  	G->AddNode(12);
  	G->AddNode(13);
  	G->AddNode(14);

  	G->AddEdge(1,4,8);
  	G->AddEdge(1,3,8);
  	G->AddEdge(2,5,7);
  	G->AddEdge(3,2,7);
  	G->AddEdge(3,5,8);
  	G->AddEdge(3,10,4);
  	G->AddEdge(4,8,2);
  	G->AddEdge(4,7,3);
  	G->AddEdge(4,5,1);
  	G->AddEdge(5,6,9);
	G->AddEdge(6,13,4);
  	G->AddEdge(7,4,6);
  	G->AddEdge(8,7,3);
  	G->AddEdge(8,9,3);
  	G->AddEdge(9,10,2);
  	G->AddEdge(9,12,4);
	G->AddEdge(10,3,10);
  	G->AddEdge(10,6,6);
  	G->AddEdge(11,12,6);
  	G->AddEdge(12,9,2);
  	G->AddEdge(12,14,9);
  	G->AddEdge(12,11,8);
  	G->AddEdge(13,14,6);
  	G->AddEdge(14,13,2);

	int opcion;

	while (opcion!=11)
	{
		std::cout << "1. Insertar un vértice en el grafo" << std::endl;
		std::cout << "2. Insertar una arista en el grafo" << std::endl;
		std::cout << "3. Eliminar un vértice del grafo" << std::endl;
		std::cout << "4. Eliminar una arista del grafo" << std::endl;
		std::cout << "5. Realizar un recorrido en profundidad (DFS)" << std::endl;
		std::cout << "6. Realizar un recorrido en amplitud (BFS)" << std::endl;
		std::cout << "7. Obtener el árbol utilizando el algoritmo de Prim" << std::endl;
		std::cout << "8. Obtener el árbol utilizando el algoritmo de Kruskal" << std::endl;
		std::cout << "9. Determinar la ruta más corta del vértice origen a todos los demás vértices utilizano Dijkstra" << std::endl;
		std::cout << "10. Determinar la ruta más corta del vértice origen a todos los demás vértices utilizano FLoyd-Warshall" << std::endl;
		std::cout << "11. Salir" << std::endl;
		std::cin >> opcion;
		switch(opcion)
		{
			case 1:
			{
				std::cout << std::endl;
				int num;
				std::cout << "Ingresa el número de vértice" << std::endl;
				std::cin >> num;
				G->AddNode(num);
			}
			break;
			case 2:
			{
				std::cout << std::endl;
				int num1;
				int num2;
				int weight;
				std::cout << "Ingresa el vértice origen de la arista" << std::endl;
				std::cin >> num1;
				std::cout << "Ingresa el vértice destino de la arista" << std::endl;
				std::cin >> num2;
				std::cout << "Ingresa el peso de la arista" << std::endl;
				std::cin >> weight;
				G->AddEdge(num1,num2,weight);
			}
			break;
			case 3:
			{
				std::cout << std::endl;
				int num;
				std::cout << "Ingresa el número de vértice que deseas eliminar" << std::endl;
				std::cin >> num;
				G->DelNode(num);
			}
			break;
			case 4:
			{
				std::cout << std::endl;
				int num1;
				int num2;
				std::cout << "Ingresa el vértice origen de la arista" << std::endl;
				std::cin >> num1;
				std::cout << "Ingresa el vértice destino de la arista" << std::endl;
				std::cin >> num2;
				G->DelEdge(num1,num2);
			}
			break;
			case 5:
			{
				std::cout << std::endl;
				std::cout << "Recorrido en profundidad utilizando DFS" << std::endl;
				Vis vis(G->GetNodes());
				TCnCom::GetDfsVisitor(G,vis);
				std::cout << std::endl;
			}
			break;
			case 6:
			{
				std::cout << std::endl;
				std::cout << "Recorrido en amplitud utilizando BFS:" << std::endl;
				PNGraph BFS = TSnap::GetBfsTree(G,1,true,true);
				for (PNGraph::TObj::TNodeI NI = BFS->BegNI(); NI < BFS->EndNI(); NI++)
				{
					std::cout << NI.GetId() << std::endl;
				}
				std::cout << std::endl;
			}
			break;
			case 7:
			{
				Prim(G);
			}
			break;
			case 8:
			{
				Kruskal(G);
			}
			break;
			case 9:
			{
				int value;
				std::cout << "Ingresa el nodo origen" << std::endl;
				std::cin >> value;
				Dijkstra(G,value);
			}
			break;
			case 10:
			{
				Floyd(G);
			}
			break;
			case 11:
			break;
			default:
			std::cout << "Opcion no valida" << std::endl;
			break;
		}
	}

	std::cout << "Construyendo el árbol ejemplo" << std::endl;

  	TPt<TNodeEDatNet<TInt,TFlt> > Graph = TNodeEDatNet<TInt,TFlt>::New();

  	Graph->AddNode(1);
  	Graph->AddNode(2);
  	Graph->AddNode(3);
  	Graph->AddNode(4);
  	Graph->AddNode(5);
  	Graph->AddNode(6);
  	Graph->AddNode(7);
  	Graph->AddNode(8);
  	Graph->AddNode(9);
  	Graph->AddNode(10);
  	Graph->AddNode(11);
  	Graph->AddNode(12);
  	Graph->AddNode(13);
  	Graph->AddNode(14);

  	Graph->AddEdge(1,4,8);
  	Graph->AddEdge(1,3,8);
  	Graph->AddEdge(2,5,7);
  	Graph->AddEdge(3,2,7);
  	Graph->AddEdge(3,5,8);
  	Graph->AddEdge(3,10,4);
  	Graph->AddEdge(4,8,2);
  	Graph->AddEdge(4,7,3);
  	Graph->AddEdge(4,5,1);
  	Graph->AddEdge(5,6,9);
	Graph->AddEdge(6,13,4);
  	Graph->AddEdge(7,4,6);
  	Graph->AddEdge(8,7,3);
  	Graph->AddEdge(8,9,3);
  	Graph->AddEdge(9,10,2);
  	Graph->AddEdge(9,12,4);
	Graph->AddEdge(10,3,10);
  	Graph->AddEdge(10,6,6);
  	Graph->AddEdge(11,12,6);
  	Graph->AddEdge(12,9,2);
  	Graph->AddEdge(12,14,9);
  	Graph->AddEdge(12,11,8);
  	Graph->AddEdge(13,14,6);
  	Graph->AddEdge(14,13,2);

  	for (TPt<TNodeEDatNet<TInt,TFlt> >::TObj::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
  	{
  		std::cout << "Nodo" << std::endl;
  		std::cout << NI.GetId() << std::endl;
  		std::cout << "Aristas" << std::endl;
  		for (TPt<TNodeEDatNet<TInt,TFlt> >::TObj::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++)
  		{
  			if (EI.GetSrcNId() == NI.GetId())
  			{
  				std::cout << EI.GetSrcNId() << "---" << EI.GetDstNId() << std::endl;
  			}
  		}

  		std::cout << std::endl;
  	}

  	auto begin = std::chrono::high_resolution_clock::now();
    Vis vis(G->GetNodes());
    auto end = std::chrono::high_resolution_clock::now();
	TCnCom::GetDfsVisitor(G,vis);
    auto tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"DFS: "<<tiempo.count()<<std::endl;

    begin = std::chrono::high_resolution_clock::now();
    PNGraph BFS = TSnap::GetBfsTree(Graph,1,true,true);
    end = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"BFS: "<<tiempo.count()<<std::endl;

  	begin = std::chrono::high_resolution_clock::now();
    Prim(Graph);
    end = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Prim: "<<tiempo.count()<<std::endl;

    begin = std::chrono::high_resolution_clock::now();
    Kruskal(Graph);
    end = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Kruskal: "<<tiempo.count()<<std::endl;

    begin = std::chrono::high_resolution_clock::now();
    Dijkstra(Graph,1);
    end = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Dijkstra: "<<tiempo.count()<<std::endl;

    begin = std::chrono::high_resolution_clock::now();
    Floyd(Graph);
    end = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Floyd: "<<tiempo.count()<<std::endl;
}

void Prim(TPt<TNodeEDatNet<TInt,TFlt> > Graph)
{
	std::vector<int> distance;
	std::vector<int> parents;
	std::deque<int> queue;

	for (int i = 0; i < Graph->GetNodes();i++)
	{
		distance.push_back(1000000);
		parents.push_back(0);
		queue.push_back(i+1);
	}

	distance[0] = 0;

	while (!queue.empty())
	{
		int u;
		int temp;

		for (int i = 0; i < queue.size(); i++)
		{
			u = i;
			for (int j = i+1; j < queue.size(); j++)
			{
				if (distance[queue[i]-1] > distance[queue[j]-1])
				{
					u = j;
				}
			}
		temp = queue[u];
		queue[u] = queue[i];
		queue[i] = temp;
		}

		u = queue.front();
		queue.pop_front();

		for(int v = 0; v < Graph->GetNodes();v++)
		{
			if (Graph->GetEDat(u,v+1,Graph->GetEDat(u,v+1)))
			{
				for (int j=0; j < queue.size();j++)
				{
					if (v+1 == queue[j] && distance[v] > Graph->GetEDat(u,v+1))
					{
						parents[v] = u;
						distance[v] = Graph->GetEDat(u,v+1);
					}
				}
			}
		}
	}

	std::cout << "Arbol de expansión mínima usando Prim: " << std::endl;
	for (int i = 0; i < Graph->GetNodes();i++)
	{
		std::cout << parents[i] << "---" << i+1 << " Size: " << distance[i] << std::endl;
	}
}

void Floyd(TPt<TNodeEDatNet<TInt,TFlt> > Graph)
{
	int table[Graph->GetNodes()][Graph->GetNodes()];

	for (int i = 0; i < Graph->GetNodes(); i++)
	{
		for (int j = 0; j < Graph->GetNodes();j++)
		{
			if (Graph->GetEDat(i+1,j+1,Graph->GetEDat(i+1,j+1)) || i == j)
			{
				table[i][j] = Graph->GetEDat(i+1,j+1);
			}
			else
			{
				table[i][j] = 1000000;
			}
		}
	}

	for (int k = 0; k < Graph->GetNodes(); k++)
	{
		for (int i = 0; i < Graph->GetNodes();i++)
		{
			for (int j = 0; j < Graph->GetNodes();j++)
			{
				int temp = table[i][k] + table [k][j];
				if (temp < table[i][j])
				{
					table[i][j] = temp;
				}
			}
		}
	}

	std::cout << "Rutas más cortas desde 1 utilizando FLoyd-Warshall: " << std::endl;
	for (int i = 0; i < Graph->GetNodes();i++)
	{
		std::cout << 1 << "----"<< i+1 << " Size: " << table[0][i] << std::endl;
	}
	std::cout << std::endl;
}

void Dijkstra(TPt<TNodeEDatNet<TInt,TFlt> > Graph, int origin)
{
	std::vector<int> weight;
	int parents[Graph->GetNodes()];
	std::deque<int> queue;
	std::vector<int> solution;

	for (int i = 0; i < Graph->GetNodes(); i++)
	{
		weight.push_back(1000000);
		parents[i] = 0;
		queue.push_back(i);
	}

	weight[origin-1] = 0;

	while (!queue.empty())
	{
		int u;
		int temp;

		for (int i = 0; i < queue.size(); i++)
		{
			u = i;
			for (int j = i+1; j < queue.size(); j++)
			{
				if (weight[queue[i]] > weight[queue[j]])
				{
					u = j;
				}
			}
		temp = queue[u];
		queue[u] = queue[i];
		queue[i] = temp;
		}

		u = queue.front();
		queue.pop_front();

		solution.push_back(u);

		for (int i = 0; i < Graph->GetNodes();i++)
		{
			if (Graph->GetEDat(u+1,i+1,Graph->GetEDat(u+1,i+1)) && weight[i] > weight[u] + Graph->GetEDat(u+1,i+1))
			{
				weight[i] = weight[u] + Graph->GetEDat(u+1,i+1);
				parents[i] = u;
			}
		}
	}

	std::cout << "Rutas más cortas desde  " << origin << " utilizando Dijkstra :" << std::endl;
	for (int i = 0; i < Graph->GetNodes();i++)
	{
		std::cout << origin << "----" << i+1 << " Size: " << weight[i] << std::endl;
	}
	std::cout << std::endl;
}


void Kruskal(TPt<TNodeEDatNet<TInt, TFlt> > Graph)
{
  	std::vector<std::pair<int, int>> edges;
  	std::vector<int> distances;
  	std::vector<int> visited;
  	std::vector<std::pair<int, int>> solution;
  	std::vector<int> distanceSolution;
  
  	for (int i = 0; i < Graph->GetNodes(); i++)
  	{
  		for (int j = 0; j < Graph->GetNodes(); j++)
    	{
      		int distance = Graph->GetEDat(i+1, j+1);
      		if (distance != 0)
      		{
        		edges.push_back(std::make_pair(i+1, j+1));
        		distances.push_back(distance);
      		}
    	}
  	}

  	std::pair<int,int> temp;
  	int tempDistance = 0;
  	int min = 0;

 	for (int i = 0; i < Graph->GetEdges()-1;i++)
  	{
  		min = i;
  		for (int j = i+1; j < Graph->GetEdges();j++)
  		{
  			if (distances[min] > distances[j])
  			{
  				min = j;
  			}
  		}
  		temp = edges[min];
		edges[min] = edges[i];
		edges[i] = temp;
		tempDistance = distances[min];	
		distances[min] = distances[i];
		distances[i] = tempDistance;
  	}

  	solution.push_back(edges[0]);
  	visited.push_back(edges[0].first);
  	visited.push_back(edges[0].second);

  	int i = 1;

  	while(visited.size() <= Graph->GetNodes())
  	{
    	bool firstVisited = false;
    	bool secondVisited = false;
    
    	for (int j = 0; j < visited.size(); j++)
    	{
      		if (visited[j] == edges[i].first)
      		{
        		firstVisited = true;
     		}
      		if (visited[j] == edges[i].second)
      		{
        		secondVisited = true;
      		}
    	}
    
    	if (!firstVisited || !secondVisited)
    	{
      		solution.push_back(edges[i]);
      		distanceSolution.push_back(distances[i]);
      		if (!firstVisited)
      		{
        		visited.push_back(edges[i].first);
      		}
      		if (!secondVisited)
      		{
        		visited.push_back(edges[i].second);
      		}
    	}
    	i++;
   }
  
  std::cout << std::endl;
  std::cout << "Árbol de expansión mínima usando Kruskal" << std::endl;
  for (int i = 0; i < solution.size(); i++)
  {
    std::cout << solution[i].first << "---" << solution[i].second << " Size: " << distanceSolution[i] << std::endl;
  }
  std::cout << std::endl;
  
}
