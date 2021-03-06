#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <limits>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <string>
#include <map>
#include <list>
#include <deque>
#include <algorithm>
 
using namespace std;
 
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int,int> pii;
 
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FORD(i,a,b) for(int i=a;i>=b;i--)
#define REP(i,n) FOR(i,0,n)
 
vb visited;  
vector<vector<pii> > g; //  O[N^3] VECTOR
 
int* c;
int* d;
 
struct comp
{
	bool operator()(const pii &a,const pii &b){
		return a.second < b.second;
	}
};
 
void dijkstra(int src)
{	
	d[src] = 0;
	
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	pq.push(pii(0,src));
	
	while(!pq.empty()){
		
		pii t = pq.top();
		int u = t.second;
		pq.pop();
		
		if(visited[u]) continue;
		d[u] = t.first;
		
		int neigh = g[u].size();
 
		REP(i,neigh){
			int v = g[u][i].first;
			int cost = g[u][i].second;
			if(!visited[v]){
				pq.push(pii(d[u]+cost,v));	
			}
		}
		
		visited[u] = true;
	}
 
}
 
void DFS(int src)
{
	c[src] = 0;
    int curr = src;
    
    stack<int> mystack;
    mystack.push(curr);
 
    while(!mystack.empty()) 
	{
        curr = mystack.top();
        mystack.pop();
 
        int minD = INT_MAX;
        vector<int> index;
        for (vector<pii> :: iterator it = g[curr].begin(); it != g[curr].end(); it++) {
            if (!visited[it->first]) {
                if (minD >= it->second) {
                    if (minD == it->second)
                        index.push_back(it->first);
                    else {
                        minD = it->second;
                        index.clear();
                        index.push_back(it->first);
                    }
                }
            }
        }
 
        if (index.size() != 0) {
            for (vector<int> :: iterator it = index.begin(); it != index.end(); it++) {
                c[*it] = c[curr] + minD;
                if (c[*it] == d[*it])
					mystack.push(*it);
            }
        }
        visited[curr] = true;
 
    }
}
int main()
{
	
	int n,m;
	
	cin >> n >> m;
	
	c = new int[n];
	d = new int[n];
	
	g = vector<vector<pii> >(n);
	
	for(int i=0;i<m;i++){
		int u,v,w;
		cin >> u >> v >> w ;
		
		g[u-1].push_back(pii(v-1,w));
	}	
	
	for(int i=0;i<n;i++)
		sort(g[i].begin(),g[i].end(),comp());
	
	int cnt =0;
	
	REP(i,n){
		
		REP(j,n){
			c[j]=INT_MAX;
			d[j]=INT_MAX;
		}
		
		visited = vb(n,false);
		dijkstra(i);   //  applied for every vertex
		
		visited = vb(n,false);
		DFS(i);
		
		REP(i,n)
		{
			//cout << d[i] << c[i] << endl;
			if(d[i]==c[i])
				cnt++;
		}
		
	}
 
	cout << cnt << endl;
	return 0;
} 
