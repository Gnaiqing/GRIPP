#ifndef _GRAPH_H_
#define _GRAPH_H_

#include"Util.h"

using namespace std;

class Graph
{
public:
	Graph(int maxn = 0);
	~Graph(); 
	void load(const char *filename);
	unsigned getN();
	unsigned getM();
	unsigned getMP(unsigned val);
	unsigned GetDegree(unsigned node);
	vector<unsigned>* GetChild(unsigned node);
	bool hasGreaterDegree(unsigned u,unsigned v);
	bool CanReach(unsigned nodeA,unsigned nodeB);
	void disp();
private:
	unsigned node_num;
	unsigned edge_num;
	vector<vector<unsigned> >	*adj_listp; 
	vector<unsigned>  *degreep;
	map<unsigned,unsigned> mp;
	bool search(unsigned nodeA,unsigned nodeB);
};
#endif
