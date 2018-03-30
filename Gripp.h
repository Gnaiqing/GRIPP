#ifndef _GRIPP_H_
#define _GRIPP_H_

#include "Util.h"
#include "Graph.h"

using namespace std;

class Gripp
{
public:
	Gripp(int maxn);
	~Gripp();
	int LoadGraph(Graph *gp);
	item *GetItem(unsigned id);
	unsigned GetTreeId(unsigned node);
	list<unsigned> GetHopNodes(unsigned node);
	bool CanReach(unsigned nodeA,unsigned nodeB);
	void display();
private:
	Graph * graphp;
	unsigned entry_num;
	unsigned node_num;
	vector<item>* Ind_table_p;
	vector<list<unsigned> >* Inst_p;
	bool vis[Util::MAX_NODE];
	void dfs(unsigned node);
	bool search(unsigned nodeA,unsigned nodeB);
};

#endif
