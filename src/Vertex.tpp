#define NOT_DEFINED -1

template<class T>
inline Vertex<T>::Vertex(const T& info, unsigned weigth, int rank, int early, int later) 
	: info_   (info)
	, weigth_ (weigth)
	, rank_   (rank)
	, early_  (early)
	, later_  (later)
{
}

template<class T>
inline Vertex<T>::Vertex(const T& info, unsigned weigth, int rank, int early) 
	: Vertex(info, weigth, rank, early, NOT_DEFINED)
{
}

template<class T>
inline Vertex<T>::Vertex(const T& info, unsigned weigth, int rank) 
	: Vertex(info, weigth, rank, NOT_DEFINED)
{
}

template<class T>
inline Vertex<T>::Vertex(const T& info, unsigned weigth) 
	: Vertex(info, weigth, NOT_DEFINED)
{
}

template<class T>
inline Vertex<T>::Vertex(const T& info) 
	: Vertex(info,0)
{
}

template<class T>
inline Vertex<T>::Vertex(const Vertex<T>& other) 
	: Vertex(other.info_ , other.weigth_)
{
}

template<class T>
inline Vertex<T>::Vertex(Vertex<T>&& other) noexcept 
	: info_   (std::move(other.info_)) 
	, weigth_ (other.weigth_) 
	, rank_   (NOT_DEFINED)
	, early_  (NOT_DEFINED)
	, later_  (NOT_DEFINED)
{
	other.weigth_ = 0;
}

template<class T>
inline const T& Vertex<T>::get_info(void) const{
	return info_;
}

template<class T>
inline unsigned Vertex<T>::get_weigth(void) const{
	return weigth_;
}

template<class T>
inline int Vertex<T>::get_rank(void) const{
	return rank_;
}

template<class T>
inline int Vertex<T>::get_early(void) const{
	return early_;
}

template<class T>
inline int Vertex<T>::get_later(void) const{
	return later_;
}

template<class T>
inline void Vertex<T>::setInfo(const T& info){
	info_ = info;
}

template<class T>
inline void Vertex<T>::setWeigth(unsigned weigth){
	weigth_ = weigth;
}

template<class T>
inline void Vertex<T>::set_rank(int rank){
	rank_ = rank;
}

template<class T>
inline void Vertex<T>::set_early(int early){
	early_ = early;
}

template<class T>
inline void Vertex<T>::set_later(int later){
	later_ = later;
}

template<class T>
inline Vertex<T>& Vertex<T>::operator=(const Vertex<T> &other)
{
	info_   = other.info_;
	weigth_ = other.weigth_;
	return *this;
}

template<class T>
inline Vertex<T>& Vertex<T>::operator=(Vertex<T>&& other)
{
	info_         = std::move(other.info_);
	weigth_       = other.weigth_;
	other.weigth_ = 0;
	return *this;
}

template<class T>
inline bool Vertex<T>::operator<(const Vertex<T>& other) const {
	return info_<other.info_  ? true : false;
}

template<class T>
inline bool Vertex<T>::operator==(const Vertex<T>& other) const {
	return info_ == other.info_ ? true : false;
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex){
	return os<<vertex.info_<<" --> = "<<vertex.weigth_;
}


