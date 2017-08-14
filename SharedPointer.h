#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

template <class T>
class SharedPointer {
public:

	//default constructor default initialises the pointer to null
	SharedPointer();

	//wraps the pointer in the smart pointer
	SharedPointer(T*);

	//copy constructor and assignment operator
	SharedPointer(const SharedPointer&);
	SharedPointer& operator=(const SharedPointer&);

	~SharedPointer();
	
	//conversion to bool
	operator bool() const;

	//dereference object
	T& operator *() const;

	//dereference an objects member
	T* operator->() const;

	//deletes underlying object
	void reset();

	//deletes underlying object and assigns ownership to the new pointer
	void reset(T*);

	//return bare pointer
	T* get() const;
	
private:
	int* reference_count;
	T* ptr;
};

template <class T>
SharedPointer<T>::SharedPointer() : reference_count(new int(0)), ptr(nullptr) {}

template <class T>
SharedPointer<T>::SharedPointer(T* ptr)
	: reference_count(new int(0)),
		ptr(ptr) {
	//if ptr is not null then increment the reference count
	if (!ptr) {
		(*reference_count)++;
	}
}

template <class T>
SharedPointer<T>::SharedPointer(const SharedPointer& shared_ptr)
	: reference_count(shared_ptr.reference_count),
		ptr(shared_ptr.ptr) {
	//is shared_ptr's underlying pointer is not null then increment the reference count
	if (!shared_ptr.ptr) {
		++*reference_count;
	}
}


#endif
