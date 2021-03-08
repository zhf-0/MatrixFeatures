#ifndef tensor_h
#define tensor_h

#include <vector>
#include "base.h"

class SpaCSR;

class Vec
{
public:
	// constructor 
	Vec():len(0){}
	Vec(INT l):val(l),len(l){}
	Vec(INT l, DOUBLE v):val(l,v),len(l){}

	// copy constructor
	Vec(const Vec & vec):val(vec.val),len(vec.len){}

	// move copy constructor
	Vec(Vec && vec):len(vec.len) {val.swap(vec.val);}

	// copy assignment operator
	Vec & operator=(const Vec & vec);

	// move assignment operator
	Vec & operator=(Vec && vec);

	// destructor 
	virtual ~Vec(){}

	// get the length of the vector
	INT GetLen() const;

	// print partial data for verification
	virtual void  PrintPartialTensor(INT num) const;

	// overload the operator * for spmv
	friend Vec operator*(const SpaCSR & csr, const Vec & vec);

	// overload the operator [] 
	DOUBLE & operator[](INT i);

	// val vector : len
	std::vector<DOUBLE> val;

protected:
	INT len;

};

#endif
