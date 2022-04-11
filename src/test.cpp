#include "DirectGraph.h"

int main(int argc, char **argv) 
{
	graph::Graph *g = nullptr;
	
	int start = 1;
    	
    	while(start)
    	{
    		std::string choice;
    		
    		
    		std::string path = "../graph_test/L3-C2-graphe";
    		
    		std::cout<<"Choose graph : ";
    		std::cin>>choice;
    		
    			g = new graph::DirectGraph<int>();
    		
    		g->createGraph((path + choice + ".txt").c_str());
    		std::cout<<(const graph::DirectGraph<int>&)(*g);
    		
    		std::cout<<"\nAdjency Matrix :"<<std::endl;
		g->dispAdjMatrix();
		
		std::cout<<"\nValue Matrix :"<<std::endl;
		g->dispValMatrix();
		
		if(g->directed())
		{
			std::cout<<"The graph is a directed graph !"<<std::endl;
			g->get_rank();
			g->get_calendar();
			std::cout<<"\nCalendar : "<<std::endl;
    			g->disp_margin();
    		}
    		else{
    			std::cout<<"The graph is not directed !!!!"<<std::endl;
    		}
    		
    		g->write_dot_file();
    		
    		#ifdef __linux__	
    			system("dot -Tpng graph.dot -o file.png && sxiv file.png");
    		#endif
    		
    		std::cout<<"continue ? (type 0 to quit, any other number to continue) : ";
    		std::cin>>start;
    		
    		
    		
    	}
    	
    	delete g;
    	g = nullptr;
    	
    	return 0;
  
}

