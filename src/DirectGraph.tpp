template<class T>
inline void DirectGraph<T>::addVertex(const Vertex<T>& add)
{
	if(graph_container.contains(add))
	{
		auto ext = graph_container.extract(add);
		ext.key() = add;
		graph_container.insert(std::move(ext));
	}
	else{
		graph_container[{add}];
	}
}

template<class T>
inline void DirectGraph<T>::addEdge(const Vertex<T>& v1, const Vertex<T>& v2){
	graph_container[{v1}].emplace(v2);
}


template<class T>
void DirectGraph<T>::createGraph(const char* path)
{
	std::ifstream file(path); 
	std::string linebuffer,Buf;
 	
 	while (file && getline(file, linebuffer))
	{
		if (linebuffer.length() == 0){
			continue;
		}

		std::stringstream ss(linebuffer);
		
		ss >> Buf;
    		T info_vertex = convert<T>(stoi(Buf));
    		
    		ss >> Buf;
    		
    		if(Buf.find('-') != std::string::npos){
    			Buf = "0";
    		}
    		unsigned weigth_vertex = (unsigned)(stoi(Buf));
    	
    		Vertex<T> vertex{info_vertex, weigth_vertex};
    		
    		addVertex(vertex);
    		
    		unsigned count;
    		for(count = 0;ss >> Buf;count++){
    			addEdge({convert<T>((stoi(Buf)))},(vertex));
    		}
    		
    		if(count == 0){
    			addEdge({convert<T>(0)},vertex);
    		}
    	}
    	
    	
    	const auto& last{convert<T>(static_cast<int>(graph_container.size()))};
    	bool is_last = true;
    	for(const auto& vertex : graph_container)
    	{
    		auto &succesors = vertex.second;
    		if(succesors.empty()){
    			if(vertex.first.get_weigth() != 0){
    				addEdge(vertex.first,last);
    			}
    			else
    				is_last = false;
    		}
    	}
    	if(is_last)
    		addVertex(last);
    	
}


template<class T>
void DirectGraph<T>::dispAdjMatrix(void) const 
{
	#define DISP(a) (a>9  ? " " : "  ")
	
	std::cout<<"MA |  ";
        for(const auto& vertex : graph_container){
        	std::cout<<vertex.first.get_info()<<DISP(convert<T>(vertex.first.get_info()))<<"|  ";
        }
	
	std::cout<<std::endl;
	for(const auto& vertex : graph_container)
	{
		const auto& succesors = vertex.second;
		std::cout << vertex.first.get_info()<<DISP(convert<T>(vertex.first.get_info())) <<"|  ";
		for(unsigned i = 0; i < graph_container.size(); i++)
		{
			
			if(succesors.contains({(convert<T>(i)),0})){
				std::cout<<1<<"  |  ";
			}
			else{
				std::cout<< 0 <<"  |  ";
			}
		}
		std::cout<<std::endl;
	}
	#undef DISP

}

template<class T>
void DirectGraph<T>::dispValMatrix(void) const
{
	
	#define DISP(a) (a>9  ? " " : "  ")
	std::cout<<"MV |  ";
        for(const auto& vertex : graph_container){
        	std::cout<<vertex.first.get_info()<<DISP(convert<T>(vertex.first.get_info()))<<"|  ";
        }

        std::cout<<std::endl;
        for(const auto& vertex : graph_container)
        {
                const auto& vertex_inside = vertex.first;
	const auto& succesors = vertex.second;
                std::cout << vertex.first.get_info()<<DISP(convert<T>(vertex.first.get_info()))<<"|  ";
                for(unsigned i = 0; i < graph_container.size(); i++)
                {

                        if(succesors.contains({convert<T>(i)}))
                        {
                                std::cout<<vertex_inside.get_weigth() <<DISP(vertex_inside.get_weigth())<<"|  ";
                        }
                        else{
                                std::cout<<"*" <<"  |  ";
                        }
                }
                std::cout<<std::endl;
        }
        #undef DISP
	
}

template<class T>
bool DirectGraph<T>::isEntry(const Vertex<T>& v,const std::map<Vertex<T>,std::set<Vertex<T>>>& graph) const
{
    bool entry = false;
    if(graph.contains(v))
    {
        entry = true;
        for(const auto& vertex : graph)
        {
            const auto& succesors = vertex.second;
            if(succesors.contains(v)){
                entry = false;
            }
        }
    }
    return entry;
}

template<class T>
std::set<Vertex<T>> DirectGraph<T>::findPred(const std::set<Vertex<T>>& v_entry)
{
    std::set<Vertex<T>> predecessors;
    for(const auto& vertex_find : v_entry)
    {
            for(const auto& vertex : graph_container)
            {
                const auto& succesors = vertex.second;
                if(succesors.contains(vertex_find)){
                    predecessors.insert(vertex.first);
                    
                }
            }
    }

    return predecessors;
}

template<class T>
void DirectGraph<T>::get_rank(void)
{
    
    std::set<Vertex<T>> entry_deleted;
    std::map<Vertex<T>, std::set<Vertex<T>>> graph_container_temp(graph_container);
    unsigned rang = 0;
    while(!graph_container_temp.empty())
    {
        for(auto& vertex : graph_container_temp)
        {
            auto &vertex_inside = vertex.first;
            
            if(isEntry(vertex_inside,graph_container_temp))
            {
                entry_deleted.insert(vertex_inside);
                auto extr = graph_container.extract(vertex_inside);
                extr.key().set_rank(rang);
                graph_container.insert(std::move(extr));
                    
            }
        }
	for(const auto& vertex : entry_deleted){
            
            graph_container_temp.erase(vertex);
        }
        
        entry_deleted.clear();
        rang++;
    }
}

template<class T>
void DirectGraph<T>::get_calendar(void)
{
	int early = 0, later = 0;
    	for(const auto& vertex : graph_container)
    	{
    		early = calendar_early(*this,vertex.first);
    		auto extr = graph_container.extract(vertex.first);
    		extr.key().set_early(early);
    		graph_container.insert(std::move(extr));
    	}
    	
    	for(const auto& vertex : graph_container)
    	{	
    		later = early - calendar_later(*this,vertex.first);
    		auto extr = graph_container.extract(vertex.first);
    		extr.key().set_later(later);
    		graph_container.insert(std::move(extr));
    	}
}

template<class T>
int calendar_early(DirectGraph<T>& G, const Vertex<T>& vertex)
{
	int early = 0;
	if(vertex.get_info() == 0)
		return vertex.get_weigth();
	const auto& pred = G.findPred(std::set<Vertex<T>>{vertex});
	for(auto vertex_pred : pred)
	{
		int early_pred = calendar_early(G,vertex_pred) + vertex_pred.get_weigth();
		early = early_pred > early? early_pred : early; //max
	}
	
	return early;
}

template<class T>
int calendar_later(DirectGraph<T>& G, const Vertex<T>& vertex)
{
	int later = 0;
	if(vertex.get_info() == G.graph_container.end()->first.get_info() -1){
		
		return vertex.get_weigth();
	}
	const auto& succ = G.graph_container[{vertex}];
	for(auto vertex_succ : succ)
	{
		int later_pred = calendar_later(G,vertex_succ) + vertex.get_weigth();
		later = later_pred < later ? later: later_pred; // max
	}
	return later;
}

template<class T> 
bool DirectGraph<T>::directed(void)
{
	std::cout<<"\nVerification of directed graph !"<<std::endl;
	bool ret = true;
	bool neg = false;
	std::cout<<"Verification of if the graph contain cycle..."<<std::endl;
	std::cout<<"Verification of if the graph contain negative weight..."<<std::endl;
	for(const auto& vertex : graph_container)
	{
		const auto& key = vertex.first;
		const auto& value = vertex.second;
		ret = is_directed(key,value,*this);
		if(!ret)
		{
			std::cout<<"Cycle on vertex : "<< key.get_info() << std::endl;
			return ret;
		}
		
		if(key.get_weigth() <= 0 && graph_container.begin()->first.get_info() != key.get_info() && graph_container.end()->first.get_info() - 1!= key.get_info())
		{
			neg = true;
			std::cout<<key.get_info()<<" has a negative weigth "<<std::endl;
		}
		
	}
	
	std::cout<<"There is no cycle"<<std::endl;
	std::cout<<"There is no negative weigth"<<std::endl;
	if(neg){
		std::cout<<"This graph contains vertex with negative weigth"<<std::endl;
		return false;
	}
	std::cout<<"Verify weigth of first vertex"<<std::endl;
	if(graph_container.begin()->first.get_weigth()!= 0){
		std::cout<<"weigth different of 0 for the first vertex !!!"<<std::endl;
		return false;
	}
	else{
		std::cout<<"weigth of first vertex is 0"<<std::endl;
	}
	
	std::cout<<"Verify if there is more than one entry..."<<std::endl;
	int count = 0;
	std::cout<<"entry : ";
	for(const auto& vertex : graph_container)
	{
		const auto& key = vertex.first;
		if(isEntry(key,graph_container)){
			std::cout<< key.get_info()<< " ";
			count++;
		}
	}
	std::cout<<std::endl;
	if(count >1){
		std::cout<<"There is more than one entry in this graph"<<std::endl;
		return false;
	}
	else{
		std::cout<<"There is just one entry"<<std::endl;
	}
	count = 0;
	std::cout<<"Verify if there is more than one exit...."<<std::endl;
	std::cout<<"Exit :";
	for(const auto& vertex : graph_container)
	{
		const auto& succ = vertex.second;
		if(succ.empty())
		{
			std::cout<<vertex.first.get_info()<<" ";
			count ++;
		}
	}
	std::cout<<std::endl;

	if(count > 1)
	{
		std::cout<<"There is more than one exit in this graph"<<std::endl;
		return false;
	}
	else{
		std::cout<<"There is just one exit"<<std::endl;
	}
			
	std::cout<<"All weigth of each vertex is unique"<<std::endl;
		
	return ret;
}

template<class T>
bool is_directed(const Vertex<T>& to_find, const std::set<Vertex<T>>& search, DirectGraph<T>& G)
{
	if(search.empty()){
		return true;
	}
	
	for(const auto& vertex : search)
	{
		if(vertex.get_info() == to_find.get_info()){
			return false;
		}
	}
	
	for(const auto& vertex : search){
		return  is_directed(to_find, G.graph_container.find(vertex)->second, G);
	}
	
	return true;
}
	
template<class T>
void DirectGraph<T>::disp_margin(void)
{
	#define DISP(a) (a>9  ? " " : "  ")
	std::string best_path = "";
	int rank;
	for(const auto& vertex : graph_container)
	{
		const auto& vertex_inside = vertex.first;
		T info = vertex_inside.get_info();
		rank = vertex_inside.get_rank();
		int early = vertex_inside.get_early();
		int later = vertex_inside.get_later();
		if(later - early == 0)
		{
			if constexpr(std::is_same_v<T,char>)
			{
				best_path.push_back(info);
				best_path +=" ";
			}
			else
				best_path += std::to_string(info) + " ";
			
			
		}
		
		std::cout << "Vertex "    << info          << DISP(info)
			  << " | Rank "   << rank          << DISP(rank) 
			  << " | Early "  << early         << DISP(early) 
			  << " | Later "  << later         << DISP(later)
			  << " | Margin " << later - early << std::endl;  
	}
	
	std::cout<<"\nCritical path !\n";
	disp_critical_path(graph_container.begin()->first,graph_container.find(graph_container.begin()->first)->second,*this,"");
	std::cout<<std::endl;
	#undef DISP
	
}

template<class T>
void disp_critical_path(const Vertex<T>& v, const std::set<Vertex<T>>& succ, DirectGraph<T>& G, std::string critical_path)
{
	critical_path += std::to_string(v.get_info());
	
	if(!succ.empty()){
		critical_path += "->";
		
	}
	else
	{
		std::cout<<critical_path<<std::endl;
		critical_path = "";
		return;
	}
	
	int marge = v.get_later() - v.get_early();
	int vec_later = calendar_later(G,v);
	
	for(const auto& vertex : succ)
	{
		if(marge == 0)
		{
			if(vec_later - v.get_weigth() == (unsigned)(calendar_later(G,vertex)))
				disp_critical_path(vertex, G.graph_container.find(vertex)->second, G,critical_path);
		}
	}
	
	return;
}

template<class T>
inline std::ostream& operator <<(std::ostream& os,const DirectGraph<T>& graph)
{
	#define DISP(a) (a>9  ? " " : "  ")
	os<<"All links of graph : "<<std::endl;
	for(const auto& element : graph.graph_container)
	{
		auto key    = element.first;
		auto inside = element.second;
		for(const auto& vertex : inside){
			os<<key.get_info()<<DISP(key.get_info())<< " --> "<<vertex.get_info()<<DISP(vertex.get_info()) << " = "<<key.get_weigth()<<std::endl;
		}
	}
	#undef DISP
	return os;
}

template<class T>
void DirectGraph<T>::write_dot_file(void)
{
	std::ofstream graph_file;
	graph_file.open("graph.dot");
	graph_file << "digraph g {" <<std::endl;
	const char* color_node = "[ color = red ]";
	int marge = NOT_DEFINED;
	for(const auto& element : graph_container)
	{
		const auto& key    = element.first;
		const auto& inside = element.second;
		if(key.get_rank() != NOT_DEFINED){
			marge = key.get_later() - key.get_early();
		}
		
		if(!marge){
			graph_file<<key.get_info()<<color_node <<std::endl;
		}
		
		for (const auto& vertex : inside)
		{
			graph_file << key.get_info()<< " -> "<<vertex.get_info()
				  <<"[ label = "<<key.get_weigth()<<" ]";
			
			if(!marge)
			{
				//int max_path = graph_container.end()->first.get_later();
				unsigned calendar_later_key  = calendar_later(*this,key);
			        unsigned calendar_later_succ = calendar_later(*this,vertex);	
			        if(calendar_later_key - key.get_weigth() == calendar_later_succ){
					graph_file<<color_node;
				}
			}
			
			graph_file<<std::endl;
		}
	}
	
	graph_file << "}";
	graph_file.close();
}	
		
template<typename T>
inline T convert(int number) 
{
	T ret;
	if(number >= 64){
		return 0;
	}
	if constexpr(std::is_same_v<T,char>){
		ret =  static_cast<char>(number+65);
	}
	else{
		ret = number;
	}
	
	return ret;
}
		 

