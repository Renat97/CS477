/// maximizes the Subset S for the hw # 6 solution
#include <iostream>
#include <limits.h>
#include <list>
#include <stack>
#include <iomanip>
#include <cstring>
#define NINF INT_MIN
using namespace std;

// global variables
int storedVal[20];
int placed[20];
int removed[20];


int optVal(int D, int n, int x[], int r[]){

	// must be 5 miles apart
	int distance = 5;

	// array for storing max revenue at every mile
	int opt[D + 1];
	memset(opt, 0, sizeof(opt));

	// incremental variables
	int nextBoard = 0;
	int subProb = 1;

	for(int i = 0; i < D + 1; i++){

		if(nextBoard < n){
			if(x[nextBoard] != i){
				opt[i] = opt[i - 1];
			} // end if

			else{
				if(i <= distance){
					opt[i] = max(opt[i - 1], r[nextBoard]);

					// problem b
					cout << "sub-problem " << subProb << ": max between " << opt[i - 1] - 1 << " and " << r[nextBoard] - 1 << " is " << opt[i] - 1 << endl;
					subProb++;

				} // end if
				else{
					opt[i] = max(opt[i - distance - 1] + r[nextBoard], opt[i - 1]);

					// problem b
					cout << "sub-problem " << subProb << ": max between " << opt[i - distance - 1] - 1 << "+" << r[nextBoard] << " and " << opt[i - 1] - 1 << " is " << opt[i] - 1 << endl;
					subProb++;

					// table/value reference
					placed[i - 1] = 1;
					if((opt[i - distance - 1] + r[nextBoard]) < opt[i - 1]){

						removed[i - 1] = 1;

					}
					if((opt[i - distance - 1] + r[nextBoard]) > opt[i - 1]){

						removed[i - distance - 1] = 1;

						if(r[nextBoard - 2] == 0){

							removed[i - distance - 1] = 0;

						} // end if

					} // end if

				} // end else

				nextBoard++;

			}

		} // end if

		// previous revenue
		else{

			// boards are placed: store maximum revenue
			opt[i] = opt[i - 1];

		} // end else

		// for table
		storedVal[i - 1] = opt[i] - 1;
	}
	cout << "OPTIMAL SOLUTION: " << opt[D] - 1 << endl;

	return opt[D] - 1;

}

// Graph is represented using adjacency list. Every
// node of adjacency list contains vertex number of
// the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode {
    int v;
    int weight;

public:
    AdjListNode(int _v, int _w)
    {
        v = _v;
        weight = _w;
    }
    int getV() { return v; }
    int getWeight() { return weight; }
};

// Class to represent a graph using adjacency list
// representation
class Graph {
    int V; // No. of vertices'

    // Pointer to an array containing adjacency lists
    list<AdjListNode>* adj;

    // A function used by longestPath
    void topologicalSortUtil(int v, bool visited[],
                             stack<int>& Stack);

public:
    Graph(int V); // Constructor
    ~Graph(); // Destructor

    // function to add an edge to graph
    void addEdge(int u, int v, int weight);

    // Finds longest distances from given source vertex
    void longestPath(int s);
};

Graph::Graph(int V) // Constructor
{
    this->V = V;
    adj = new list<AdjListNode>[V];
}

Graph::~Graph() // Destructor
{
    delete [] adj;
}


void Graph::addEdge(int u, int v, int weight)
{
    AdjListNode node(v, weight);
    adj[u].push_back(node); // Add v to u's list
}

// A recursive function used by longestPath. See below
// link for details

void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<AdjListNode>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        AdjListNode node = *i;
        if (!visited[node.getV()])
            topologicalSortUtil(node.getV(), visited, Stack);
    }

    // Push current vertex to stack which stores topological
    // sort
    Stack.push(v);
}

// topological sorting for the events and there coordinates
void Graph::longestPath(int s)
{
    stack<int> Stack;
    int dist[V];

    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;

    // Process vertices in topological order
    while (Stack.empty() == false) {
        // Get the next vertex from topological order
        int u = Stack.top();
        Stack.pop();

        // Update distances of all adjacent vertices
        list<AdjListNode>::iterator i;
        if (dist[u] != NINF) {
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (dist[i->getV()] < dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
        }
    }

    // Print the calculated longest distances
    for (int i = 0; i < V; i++)
        (dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";

    delete [] visited;
}

// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram.
    // Here vertex numbers are 0, 1, 2, 3, 4, 5 with
    // following mappings:
    // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    int s = 1;
    cout << "Following are the events you could make "
         << " \n";
    g.longestPath(s);


	// Given testing values
	int D = 20;
	int x[] = {6, 7, 12, 14};
	int r[] = {5, 6, 5, 1};
	int n = 4;

	cout << endl << "PROBLEM B:" << endl;

	optVal(D, n, x, r);

	cout << endl << "PROBLEM C:" << endl;

	// Table output
	cout << "OPTIMUM VALUE: " << storedVal[19] << " is the maximum event following the table." << endl;
    // MINOR BUG, DO NOT RUN
    /*
	cout << right << setw(52) << "Coordinates" << endl;
	cout << right << setw(52) << "         " << endl << "         " <<'|';

	for(int i = 1; i <= 20; i++){

		cout << right << setw(4) << i;

	} // end for


	cout << "  |" << endl << "         " << endl;
	cout << "  PLACED|  ";


	for(int i = 0; i < 20; i++){

		cout << " " << placed[i] << "  ";

	} // end for


	cout << "|" << endl;
	cout << " REMOVED|  ";


	for(int i = 0; i < 20; i++){

		cout << " " << removed[i] << "  ";

	} // end for


	cout << "|" << endl;
	cout << "  EVENTS|  ";


	for(int i = 0; i < 20; i++){

		if(storedVal[i] >= 10){

			cout << storedVal[i] << "  ";

		} // end if

		else{

			cout << " " << storedVal[i] << "  ";

		} // end else

	} // end for

	cout << "|" << endl;
	cout << right << setw(52) << "         " << endl;

    return 0;
    */
}

