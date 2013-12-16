#include "Container.h"

#include "Unit.h"
#include "Missile.h"

#include <algorithm>

template <typename T>
std::vector<Container<T> *> Container<T>::_instance_list;

template <typename T>
Container<T>::Container() {
	_instance_list.push_back(this);
}

template <typename T>
Container<T>::~Container() {
	_instance_list.erase(std::remove(_instance_list.begin(), _instance_list.end(), this), _instance_list.end());
}

template <typename T>
T * Container<T>::get_t(int index) {
	if(index>=0 && index<(int)_list.size()) return _list[index];
	else return NULL;
}

template <typename T>
void Container<T>::add_t(T * t) {
	if(std::find(_list.begin(), _list.end(), t) == _list.end()) {
		_list.push_back(t);
	}
}

template <typename T>
void Container<T>::remove_t(int index) {
	if(index>=0 && index<(int)_list.size()) {
		typename std::vector<T *>::iterator it = _list.begin()+index;
		_list.erase(it);
	}
}

template <typename T>
void Container<T>::remove_t(T * t) {
	_list.erase(std::remove(_list.begin(), _list.end(), t), _list.end());
}

template <typename T>
bool Container<T>::contain_t(T * t) {
	return std::find(_list.begin(), _list.end(), t) != _list.end();
}

template <typename T>
int Container<T>::get_number_t() {
	return (int)(_list.size());
}

template <typename T>
void Container<T>::on_destroyed(T * t) {
	unsigned int i;
	for(i=0; i<_instance_list.size(); i++) {
		_instance_list[i]->remove_t(t);
	}
}

template class Container<Unit>;
template class Container<Missile>;
