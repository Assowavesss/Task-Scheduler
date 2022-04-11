#include "DirectGraph.h"

int main(void)
{
    
    	graph::Graph *g = new graph::DirectGraph<int>();
    	g->createGraph("../graph_test/test.txt");
    	std::cout<<(const graph::DirectGraph<int>&)(*g);
    	g->dispAdjMatrix();
    	g->dispValMatrix();
    	g->get_rank();
    	g->get_calendar();
    	g->disp_margin();
    	delete g;
    	g = nullptr;
}	
