#ifndef UNIT_CONTAINER_H
#define UNIT_CONTAINER_H

#include <vector>

template <typename T>
class Container {
	private:
		std::vector<T *> _list;

		static std::vector<Container<T> *> _instance_list;

	public:
		Container();
		Container(Container const& container);
		~Container();

		T * get_t(int index);
		void add_t(T * t);
		void remove_t(int index);
		void remove_t(T * t);
		bool contain_t(T * t);
		int get_number_t();

		static void on_destroyed(T * t); //reservé au destructeur de Unit
};

#endif
