#include "Util.h"
#include "Gripp.h"

using namespace std;

static unsigned deg[Util::MAX_NODE];
static bool used_hop[Util::MAX_NODE];
static unsigned dfn = 0;
// static list<unsigned> (*Inst_p)[Util::MAX_NODE];
static bool vis[Util::MAX_NODE];
// static vector<item> (*Ind_table_p);
class CmpDeg
{
public:
	bool operator()(unsigned u,unsigned v)
	{
		return deg[u] < deg[v];
	}
};

Gripp::Gripp(int maxn)
{
	this->Inst_p = new vector<list<unsigned> >(maxn);
	this->Ind_table_p = new vector<item>();
}

Gripp::~Gripp()
{
	delete Inst_p;
	delete Ind_table_p;
}

int Gripp::LoadGraph(Graph *gp)
{
	this->graphp = gp;
	(*Ind_table_p).push_back(item(0,0,0,Util::TREE));
	//cout<<"check 1"<<endl;
	entry_num = 1;
	unsigned n = gp->getN();
	node_num = n;
	for(unsigned i = 1;i <= n;i++) deg[i] = gp->GetDegree(i);
	priority_queue<unsigned,vector<unsigned>,CmpDeg>* Q = new priority_queue<unsigned,vector<unsigned>,CmpDeg>();
	for(unsigned i = 1;i <= n;i++)
		Q->push(i);
	unsigned u;
	memset(vis,0,sizeof(vis));
	//cout<<"check 2"<<endl;
	while(!Q->empty())
	{		
		do
		{
			u = Q->top();
			Q->pop();
		}
		while (vis[u] && !Q->empty());
		//cout<<"check xzz"<<endl;
		if(vis[u]) break;
		//cout<<"before dfs"<<endl;
		Gripp::dfs(u);
		//cout<<"after dfs"<<endl;

	}
	//cout<<"check 3"<<endl;
	dfn++;
	(*Ind_table_p)[0].post = dfn;
	//cout<<"check 4"<<endl;
	delete Q;
	//cout<<"check 5"<<endl;
	return 0;
}

void Gripp::dfs(unsigned u)
{
	//cout<<"dfs 0"<<endl;
	int cnt = entry_num++;
	(*Inst_p)[u].push_back(cnt);
	dfn++;
	//cout<<"dfs 1"<<endl;
	if(!vis[u])
	{
		vis[u] = true;
		(*Ind_table_p).push_back(item(u,dfn,0,Util::TREE));
		vector<unsigned>* ret = graphp->GetChild(u);
		vector<unsigned>& vect = *ret;
		sort(vect.begin(),vect.end(),CmpDeg());
		int len = vect.size();
		for(int i = 0;i < len;i++)
		{
			dfs(vect[i]);
		}
		delete ret;
	}
	else
	{
		(*Ind_table_p).push_back(item(u,dfn,0,Util::NONTREE));
	}
	//cout<<"dfs 2"<<endl;
	dfn++;
	(*Ind_table_p)[cnt].post = dfn;
	//cout<<"dfs 3"<<endl;
}

item * Gripp::GetItem(unsigned id)
{
	if(id >= entry_num) return NULL;
	return &(*Ind_table_p)[id];
}

unsigned Gripp::GetTreeId(unsigned node)
{
	return *(*Inst_p)[node].begin();
}

void Gripp::display()
{
	cout << entry_num <<" items in Gripp"<<endl;
	//unsigned k = min(entry_num, Util::MAX_SHOWN_ITEM);
	unsigned k = std::min(entry_num, 30u);
	cout << "First "<<k<<" items are:"<<endl;
	cout<<"node\tpre\tpost\tnontree\t"<<endl;
	for(unsigned i = 0;i < k;i++)
	{
		cout<<(*Ind_table_p)[i].node<<'\t'
			<<(*Ind_table_p)[i].pre<<'\t'
			<<(*Ind_table_p)[i].post<<'\t'
			<<(*Ind_table_p)[i].type<<'\n';
	}
}

list<unsigned> Gripp::GetHopNodes(unsigned node)
{
	list<unsigned> hop_list;
	unsigned cnt = GetTreeId(node);
	item * cntp = GetItem(cnt);
	unsigned k = cnt + 1;
	while(k < entry_num)
	{
		item * p = GetItem(k);
		if(p->pre > cntp->post) break;
		if(!used_hop[p->node] && p->type == Util::NONTREE)
		{
			used_hop[p->node] = true;
			hop_list.push_back(p->node);
		}
		k++;
	}
	return hop_list;
}

bool Gripp::CanReach(unsigned nodeA,unsigned nodeB)
{
	memset(used_hop,0,sizeof(used_hop));
	/*
	nodeA = graphp->getMP(nodeA);
	nodeB = graphp->getMP(nodeB);
	*/
	nodeA = nodeA + 1;
	nodeB = nodeB + 1;
	return search(nodeA,nodeB);
}

bool Gripp::search(unsigned nodeA,unsigned nodeB)
{
	unsigned tree_id_A = GetTreeId(nodeA);
	item * pa = GetItem(tree_id_A);
	for(auto iter = (*Inst_p)[nodeB].begin();iter != (*Inst_p)[nodeB].end()
		;iter++)
	{
		item * pb = GetItem(*iter);
		if(pa->pre <= pb->pre && pb->pre <= pa->post)
			return true;
	}
	list<unsigned> hop_list = GetHopNodes(nodeA);
	for(auto iter = hop_list.begin();iter != hop_list.end();
		iter++)
		if(search(*iter,nodeB)) return true;
	return false;
}

