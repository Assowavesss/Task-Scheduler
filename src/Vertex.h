#pragma once

namespace graph
{
	template <class T>
	class Vertex
	{
		private:
			T info_;
			unsigned weigth_;
			int rank_;
			int early_;
			int later_;
			int marge_;
		public:
			Vertex(const T& info, unsigned weigth, int rank, int early, int later);
			Vertex(const T& info, unsigned weigth, int rank, int early);
			Vertex(const T& info, unsigned weigth, int rank);
			Vertex(const T& info, unsigned weigth);
			Vertex(const T& info);
			Vertex(const Vertex<T>& other);
			Vertex(Vertex<T>&& other) noexcept;
			
			const T& get_info(void) const;
			unsigned get_weigth(void) const;
			int get_rank(void) const;
			int get_early(void) const;
			int get_later(void) const;
			
			void setInfo(const T& info);
			void setWeigth(unsigned weigth);
			void set_rank(int rank);
			void set_early(int early);
			void set_later(int later);
			
			Vertex<T>& operator=(const Vertex<T>& vertex);
			Vertex<T>& operator=(Vertex<T>&& vertex);
			bool operator<(const Vertex<T>& other) const;
			bool operator==(const Vertex<T>& other) const;
			
			template<class U>
			friend std::ostream& operator<<(std::ostream& os, const Vertex<U>& vertex);
	};

	#include"Vertex.tpp"
}


