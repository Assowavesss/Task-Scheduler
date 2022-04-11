#ifndef DIRECTGRAPH_H
#define DIRECTGRAPH_H
#include<iostream>
#include<map>
#include<set>
#include<cstring>
#include<string>
#include<sstream>
#include<vector> 
#include<fstream>
#include"Graph.h"
#include"Vertex.h"

namespace graph
{
	template <class T>
	class DirectGraph : public Graph
	{
		private:
			std::map<Vertex<T>, std::set<Vertex<T>>> graph_container;
			
		public:
			static_assert(std::is_arithmetic<T>::value, "Template argument must be numeric");
			
			void addVertex(const Vertex<T>& vertex);
			void addEdge(const Vertex<T>& v1, const Vertex<T>& v2);
	        	
			void createGraph(const char* path) override;
            		void dispAdjMatrix(void) const override;
            		void dispValMatrix(void) const override;
            		bool isEntry(const Vertex<T>& v,const std::map<Vertex<T>, std::set<Vertex<T>>>& graph) const; 
            		std::set<Vertex<T>> findPred(const std::set<Vertex<T>>& v_entry);
            		void get_rank(void) override;
            		void get_calendar(void) override;
            		void disp_margin(void) override;
            		void write_dot_file(void) override;
            		bool directed(void) override;
            		
                	template<class U>
                	friend int calendar_early(DirectGraph<U>& G, const Vertex<U>& vertex);
                	
                	template<class U>
                	friend int calendar_later(DirectGraph<U>& G, const Vertex<U>& vertex);
                	
                	template<class U>
			friend bool is_directed(const Vertex<U>& to_find, const std::set<Vertex<U>>& search,DirectGraph<U>& G);
			
			template<class U>
			friend void disp_critical_path(const Vertex<U>& v, const std::set<Vertex<U>>& succ,  DirectGraph<U>& graph,std::string critical_path);
                	
                	template<class U>
                	friend U convert(int number);
                	
            		template<class U>
			friend std::ostream& operator <<(std::ostream& os,const DirectGraph<U>& graph);
	};
	
	#include"DirectGraph.tpp"
	#undef NOT_DEFINED	
}


#endif
