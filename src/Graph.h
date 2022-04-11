#ifndef GRAPH_H
#define GRAPH_H
namespace graph
{
	
	class Graph
	{
		public:
			virtual void createGraph(const char *path) = 0;
			virtual void dispAdjMatrix(void) const     = 0;
			virtual void dispValMatrix(void) const     = 0;
			virtual bool directed(void)                = 0;
			virtual void get_rank(void)                = 0;
			virtual void get_calendar(void)            = 0;
            		virtual void disp_margin(void)             = 0;
            		virtual void write_dot_file(void)           = 0;
			virtual ~Graph(void) = default;
	};
}

#endif





