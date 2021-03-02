#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type

//These will aid me in the breadth-first search. From Lab 10
unordered_map<string, bool> visited;         // have we queued up this state for visitation?
unordered_map<string, string> pred;           // predecessor state we came from
unordered_map<string, int> dist;             // distance (# of hops) from source node
unordered_map<string, vector<string>> nbrs;   // vector of neighboring states

//This function searches for each string.
void search(string s)
{
  queue<string> to_visit;
  to_visit.push(s);
  visited[s] = true;
  dist[s] = 0;
  
  while (!to_visit.empty()) 
  {
    string current = to_visit.front();
    to_visit.pop();
    for (string n : nbrs[current])
        if (!visited[n]) 
        {
            pred[n] = current;
            dist[n] = 1 + dist[current];
            visited[n] = true;
            to_visit.push(n);
        }
  }
}

//This builds the graph.
void buildGraph(void)
{
    string word; 
    ifstream file("wordlist05.txt");
    int countDif;
    
    while(file >> word)
    {
        V.push_back(word);
    }
    
    for(auto i: V)
    {
        for(auto j: V)
        {
            countDif = 0;
            for(int k = 0; k < i.length(); k++)
            {
                if(i[k] != j[k])
                {
                    countDif++;
                }
            }
            if(countDif == 1)
            {
                nbrs[i].push_back(j);
                nbrs[j].push_back(i);
            }
        }
    }
}

void findPathway(string s, string t, int &steps, vector<string> &p)
{
   if(s.compare(t) != 0)
   {
       findPathway(s, pred[t], steps, p);
       p.push_back(t);
       steps++;
   }
   else
   {
       steps = 0;
   }
}

//Implement breadth-first search, refer to Lab 10
void wordLadder(string s, string t, int &steps, vector<string> &p)
{
    buildGraph();
    search(s);
    search(t);
    
    if(pred[t].empty() == true)
    {
        steps = 0;
        return;
    }
    
    findPathway(s, t, steps, p);
}

int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
