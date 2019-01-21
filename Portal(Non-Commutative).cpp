  /****************
  Created by Samuelito Perro
  A program that solves the traveling salesman problem
  JK, just calculates the shortest path
  *****************/
  #include <iostream>
  #include <string>
  #include <fstream>
  #include <cstdlib>
  #include <vector>
  #include <queue>
  #include <deque>
  #include <stack>



  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;
  using std::ifstream;
  using std::istringstream;
  using std::vector;
  using namespace std;

  int main ()
  { 
    string sbuf1,
    sbuf2,
    OriStr,
    DestStr;

    ifstream ifl;

    char *ep;

    vector <vector<bool>> Nodes;
    vector <bool> Connections;

    cout << "Content-Type: text/plain\n\n";

// Getting info from the html
    getline(cin, OriStr);
    getline(cin, DestStr);

// Converting strings to ints
    int Or = strtol(OriStr.c_str(), &ep, 10),
    Des = strtol(DestStr.c_str(), &ep, 10);

// Opening connections file
ifl.open("/home/student2018/scp002/webdata/Connections.txt");
    if (!ifl)
    {
      cout << "Woooops. I could not find the password on the server." << endl;
      exit(0);
    }

// Getting Connections for each node and building SQUAREArray
for (int z = 0; z < 5; z++)
{
    for (int i = 0; i < 5; i++)
    {
        getline(ifl, sbuf1);
        if (sbuf1 != "X" && sbuf1 == "1")
        {
        Connections.push_back(true);
        }
        
        else
        {
        Connections.push_back(false);
        }
        
    }
    Nodes.push_back(Connections);
    Connections.clear();
}



// Settings for calculating shortest path
vector <bool> visited;
for (int i = 0; i < 5; i++)
{
    visited.push_back(false); // Initialize al to false
}
queue <int> Q;
stack <int> path;

// Starting by Origin, add to queue and mark as visited
Q.push(Or);
visited[Or] = true;

// Define current, path checker, and final answer
int current;
int checker;
vector <int> Answer;

while(!Q.empty()) // While there is stuff in the queue
    {
        // Add Q element to the path and peek it
        current = Q.front(); //Use this later to check connections
        if (path.empty() || path.top() != current)
        {
            path.push(current);
        }
        Q.pop();

        checker = Q.size(); // Use this to check if the algorithm got "stuck"

        //Check next vertices and move on
        for (int i = 0; i < Nodes[current].size(); i++)
        {
            if (Nodes[current][i] == true) // if the connection exists
            {
                if (i == Des) // We reached the end of the path
                {
                    // Output and quit
                    path.push(i);
                    while(!path.empty())
                    {
                        Answer.push_back(path.top());
                        path.pop();
                    }
                    for (int i = Answer.size()-1; i > -1; i--)
                    {
                        cout << Answer[i];
                    }
                    cout << endl;
                    
                    exit(0);
                }
                else if (visited[i] == false) // If the connection has not been visited
                {
                    // Add to Queue and mark as visited.
                    Q.push(i);
                    visited[i] = true;
                }
            }
        }
        if (checker == Q.size()) //This means the current node was a mistake, so pop from path
        {
            path.pop();
        }
    }
}