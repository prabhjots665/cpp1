// cpp1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cuchar>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <any>
#include <charconv>
// #include <execution>
#include <filesystem>
#include <optional>
#include <memory_resource>
#include <string_view>
#include <variant>
#endif

#if __cplusplus > 201703L
#include <bit>
// #include <compare>
// #include <concepts>
#include <numbers>
// #include <ranges>
// #include <span>
// #include <syncstream>
#include <version>
#endif

using namespace std;



bool vis[101];

bool iscyclic(vector<int >adj[], int s, int parent)
{
	vis[s] = true;

	for (auto i = adj[s].begin(); i != adj[s].end(); i++)
	{
		if (vis[*i] == false) return iscyclic(adj, *i, s);
		else
			if (*i != parent) return true;
	}

	return false;
}


bool isCyclic(vector<int> adj[], int V)
{
	
	for (int i = 0; i < V; i++) 
		vis[i] = false;

	for (int i = 0; i < V; i++)
	{
		if (vis[i] == false)
		{
			if (iscyclic(adj, i, -1))
				return true;
		}
	}

	return false;

}


//int main()
//{
//	int t, tt, n, a, b;
//	int arr[31];
//	scanf("%d", &tt);
//	for (t = 0; t < tt; t++)
//	{
//		for (int i = 0; i < 31; ++i)
//			arr[i] = -1;
//		scanf("%d", &n);
//		for (int i = 0; i < n; ++i)
//		{
//			scanf("%d %d ", &a, &b);
//			arr[a] = b;
//		}
//
//		int cc = func(arr);
//		printf("%d\n", cc);
//	}
//	return 0;
//}




enum Color { WHITE, GRAY, BLACK };

int *color = new int[101];

// Graph class represents a directed graph using 
// adjacency list representation 
class Graph
{
	int V; // No. of vertices 
	list<int>* adj; // adjacency lists 

					// DFS traversal of the vertices reachable from v 
	bool DFSUtil(int v, int color[]);
public:
	Graph(int V); // Constructor 

				  // function to add an edge to graph 
	void addEdge(int v, int w);

	bool isCyclic();
};

// Constructor 
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

// Utility function to add an edge 
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v's list. 
}

// Recursive function to find if there is back edge 
// in DFS subtree tree rooted with 'u' 
bool Graph::DFSUtil(int u, int color[])
{
	color[u] = GRAY;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i; 

		if (color[v] == GRAY)
			return true;

		if (color[v] == WHITE)
		{
			if (DFSUtil(v, color) == true)
				return true;
		}
	}

	color[u] = BLACK;
    return false;
}

// Returns true if there is a cycle in graph 
bool Graph::isCyclic()
{
	// Initialize color of all vertices as WHITE
	for (int i = 0; i < V; i++)
		color[i] = WHITE;

	// Do a DFS traversal beginning with all 
	// vertices 
	for (int i = 0; i < V; i++)
		if (color[i] == WHITE)
			if (DFSUtil(i, color) == true)
				return true;

	return false;
}

// Driver code to test above 
int main()
{
	// Create a graph given in the above diagram 
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	//g.addEdge(2, 0);
	//g.addEdge(2, 3);
	g.addEdge(3, 3);

	if (g.isCyclic())
		cout << "Graph contains cycle";
	else
		cout << "Graph doesn't contain cycle";
	scanf("%d");

	return 0;
}
