#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

template <class T>
class SharedPointer {
public:

	//default constructor default initialises the pointer to null
	explicit SharedPointer();

	//wraps the pointer in the smart pointer
	explicit SharedPointer(T*);

	//copy constructor and assignment operator
	explicit SharedPointer(const SharedPointer&);
	SharedPointer& operator=(const SharedPointer&);

	~SharedPointer();
	
	//conversion to bool
	operator bool() const;

	//dereference object
	T& operator *() const;

	//dereference an objects member
	T* operator->() const;

	//switches ownership to new pointer
	void reset(T* o_ptr = nullptr);

	//return bare pointer
	T* get() const;
	
private:
	int* reference_count;
	T* ptr;

	//releases ownership of the shared pointer on ptr 
	void release();
};

template <class T>
SharedPointer<T>::SharedPointer()
	: reference_count(new int(1)),
		ptr(nullptr) {}

template <class T>
SharedPointer<T>::SharedPointer(T* ptr)
	: reference_count(new int(1)),
		ptr(ptr) {}

template <class T>
SharedPointer<T>::SharedPointer(const SharedPointer& shared_ptr)
	: reference_count(shared_ptr.reference_count),
		ptr(shared_ptr.ptr) {}

template <class T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& rhs) {
  //check for self assignmenet
	if (&rhs == this) {
		return *this;
	}

	//increase ref count of rhs (prevents it being destroyed if this is destroyed)
	++(*rhs.reference_count);

	release();

	ptr = rhs.ptr;
	reference_count = rhs.reference_count;
	return *this;
}

template <class T>
SharedPointer<T>::~SharedPointer() {
	release();
}


template <class T>
void SharedPointer<T>::release() {
	//if reference count drops to 0 then free memory
	if (--(*reference_count) == 0) {
		delete reference_count;
		delete ptr;
	}

	//set pointers to null
	reference_count = nullptr;
	ptr = nullptr;
}

template <class T>
SharedPointer<T>::operator bool() const {
	return ptr;
}

template <class T>
T* SharedPointer<T>::operator->() const {
	return ptr;
}

template <class T>
T& SharedPointer<T>::operator*() const  {
	return *ptr;
}

template <class T>
void SharedPointer<T>::reset(T* other_ptr) {

	release();

	ptr = other_ptr;
	reference_count = new int(1);
}



#endif
