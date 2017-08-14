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

	//conversion to bool
	operator bool() const;

	//dereference object
	operator *() const;

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

#endif
