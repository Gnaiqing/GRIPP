#include "Gripp.h"

/* check the result of gripp reachability */
void check(unsigned node_num,unsigned check_num,Graph * gp,Gripp * grp)
{
	srand((unsigned)time(NULL));
	int con = 0,error = 0;
	for(unsigned i = 0;i < check_num;i++)
	{
		unsigned u = rand() % node_num;
		unsigned v = rand() % node_num;
		bool b1 = gp->CanReach(u,v);
		bool b2 = grp->CanReach(u,v);
		if(b1 != b2)
		{
			cout<<"Diff:"<<u<<' '<<v
			<<" DFS:"<<b1<<" GRIPP:"<<b2<<endl;
			error++;
		}
		if(b1) con++;		
	}
	cout <<"error num:"<<error << endl;
	cout<<"done:"<<con<<"pairs connected"<<endl;	
}
/* check the speed of gripp reachability */
void checkspeed(unsigned node_num,unsigned check_num,Gripp * grp)
{
	for(unsigned i = 0;i < check_num;i++)
	{
		unsigned u = rand() % node_num;
		unsigned v = rand() % node_num;
		bool b = grp->CanReach(u,v);
	}
}
int main()
{
	Graph * gp = new Graph(Util::MAX_NODE);
	string filename;
	cout << "Gripp reachability program" << endl;
	cout << "max nodes:"<<Util::MAX_NODE <<
		" max edges:" << Util::MAX_EDGE << endl;
	cout << "Please enter file name:"<<endl;
	cin >> filename;
	cout << "Loading file to graph"<<endl;
	gp->load(filename.c_str());
	gp->disp();
	//system("pause");

	cout << "Loading graph data to Gripp"<<endl;
	clock_t start,finish;
	Gripp * grp = new Gripp(Util::MAX_NODE);
	cout<<"Gripp object built"<<endl;
	
	start = clock();
	grp->LoadGraph(gp);
	finish = clock();
	cout << "Time for building Gripp:" << setprecision(4)
		 <<(double)(finish - start)/CLOCKS_PER_SEC<<"s"<<endl;
	grp->display();
	//system("pause");

	cout <<"Please enter num of pairs to be checked for Gripp's correctness"<<endl;
	int checknum;
	cin >> checknum;
	cout << "Checking for correctness" << endl;
	check(gp->getN(),checknum,gp,grp);
	//system("pause");

	cout <<"Please enter num of pairs to be checked for Gripp's speed"<<endl;
	cin >> checknum;
	cout << "Testing speed of Gripp" << endl;
	start = clock();
	checkspeed(gp->getN(),checknum,grp);
	finish = clock();
	cout << "Time for checking reachability: " << setprecision(4)
		 <<(double)(finish - start)/CLOCKS_PER_SEC<<"s"<<endl;
	double aver = (double)(finish - start)/CLOCKS_PER_SEC/checknum;
	cout << setprecision(4) << aver*1000 << "ms per pair"<<endl;
	//system("pause");

	cout <<"Goodbye"<<endl;
	delete grp;
	delete gp;

	return 0;
}
