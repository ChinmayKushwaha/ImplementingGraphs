#include <bits/stdc++.h>

using namespace std;

class graphs
{
public:
    unordered_map<string, list<pair<string, int>>> adj;

    void addCity(string u, string v, int w)
    {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    vector<string> BFS(string node)
    {
        vector<string> ans;
        queue<string> q;
        q.push(node);
        unordered_map<string, bool> visited;
        visited[node] = true;

        while (!q.empty())
        {
            string frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);

            for (auto i : adj[frontNode])
            {
                if (!visited[i.first])
                {
                    q.push(i.first);
                    visited[i.first] = true;
                }
            }
        }

        return ans;
    }

    unordered_map<string,int> Dijkstra(string temp,string source)
    {
        vector<string> bfs = BFS(temp);

        unordered_map<string,int> dist;

        for (auto i:bfs)
        {
            dist[i] = INT_MAX;
        }

        dist[source] = 0;
        set<pair<int, string>> st;

        st.insert(make_pair(0, source));

        while (!st.empty())
        {
            auto top = *(st.begin());

            int nodeDist = top.first;
            string topNode = top.second;

            st.erase(st.begin());

            for (auto neighbour : adj[topNode])
            {
                if (nodeDist + neighbour.second < dist[neighbour.first])
                {
                    auto record = st.find(make_pair(dist[neighbour.first], neighbour.first));

                    if (record != st.end())
                    {
                        st.erase(record);
                    }

                    dist[neighbour.first] = nodeDist + neighbour.second;

                    st.insert(make_pair(dist[neighbour.first], neighbour.first));
                }
            }
        }
        return dist;
    }
};

int main()
{
    cout << "Please enter the city and its neighbour city and the distance between them" << endl;

    char ch = 'Y';

    graphs city;

    string temp;

    while (ch == 'Y')
    {
        string u, v;
        int w;
        cin >> u >> v;
        cin >> w;
        temp = u;
        city.addCity(u, v, w);

        cout << "If you want to add more cities, then press 'Y'" << endl;
        cin >> ch;
    }

    vector<string> ans = city.BFS(temp);

    cout << "All cities present in this graph are:" << endl;

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl << endl;

    string begin_city;
    cout << "Enter the city from which you want to begin you journey:" << endl;
    cin >> begin_city;
    cout << endl;

    unordered_map<string,int> dist = city.Dijkstra(temp,begin_city);
    cout << "Shortest distance from " << begin_city << " to :" << endl << endl;

    for(auto i:dist)
    {
        cout << i.first << " " << i.second << endl;
    }
}

/*
Jaipur Jhansi 3
Y
Jaipur Kota 4
Y
Kota Delhi 5
Y
Kota Agra 9
Y
Delhi Agra 1
Y
Delhi Jhansi 8
N
*/
