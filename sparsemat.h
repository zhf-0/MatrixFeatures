#ifndef sparsemat_h
#define sparsemat_h
#include <vector>
#include <string>
#include "base.h"
#include <iostream>

class SparseMat
{
public:
	// constructor
	SparseMat():row(0),col(0),nnz(0){}
	SparseMat(INT r,INT c, INT n):val(n),row(r),col(c),nnz(n){}

	// copy constructor
	SparseMat(const SparseMat & spamat):val(spamat.val),row(spamat.row),col(spamat.col),nnz(spamat.nnz){}

	// move copy constructor
	SparseMat(SparseMat &&  spamat):row(spamat.row),col(spamat.col),nnz(spamat.nnz)
	{val.swap(spamat.val);}

	// copy assignment operator
	SparseMat & operator= (const SparseMat & spamat);

	// move copy assignment operator
	SparseMat & operator= (SparseMat && spamat);

	// destructor 
	virtual ~SparseMat(){}

	// print partial matriax for verification, according to the specific matrix type in the derived class
	virtual void  PrintPartialMat(INT num)=0;

	INT GetRow() const;

	INT GetCol() const;

	INT GetNnz() const;


	// val vector : nnz
	std::vector<DOUBLE> val;

protected:
	// number of row : m
	INT row;

	// number of col : n
	INT col;

	// number of nnz : nnz
	INT nnz;

};

class SpaCOO:public SparseMat
{
public:
	// constructor
	SpaCOO():SparseMat(){}
	SpaCOO(INT r,INT c, INT n):SparseMat(r,c,n),row_vec(n),col_vec(n){}

	// copy constructor
	SpaCOO(const SpaCOO & coo):SparseMat(coo),row_vec(coo.row_vec),col_vec(coo.col_vec){}

	// move copy constructor
	SpaCOO(SpaCOO && coo):SparseMat(coo)
	{
		row_vec.swap(coo.row_vec);
		col_vec.swap(coo.col_vec);
	}

	// copy assignment operator
	SpaCOO & operator= (const SpaCOO & coo);

	// move copy assignment operator
	SpaCOO & operator= (SpaCOO && coo);

	// destructor 
	virtual ~SpaCOO(){}

	// overload the virtual function from base class, and print num entries in coo matrix 
	virtual void  PrintPartialMat(INT num);

	// read matrix from file, index in file begin with 0
	void ReadMat0(std::string file_name);

	// read matrix from file, index in file begin with 1
	void ReadMat1(std::string file_name);


	// row vector : nnz
	std::vector<INT> row_vec;

	// col vector : nnz
	std::vector<INT> col_vec;
};


class SpaCSR:public SparseMat
{
public:
	// constructor
	SpaCSR():SparseMat(){}
	SpaCSR(INT r,INT c, INT n):SparseMat(r,c,n),row_vec(r+1),col_vec(n){}
	SpaCSR(const SpaCOO & coo);

	// copy constructor
	SpaCSR(const SpaCSR & csr):SparseMat(csr),row_vec(csr.row_vec),col_vec(csr.col_vec){}

	// move copy constructor 
	SpaCSR(SpaCSR && csr):SparseMat(csr)
	{
		row_vec.swap(csr.row_vec);
		col_vec.swap(csr.col_vec);
	}

	// copy assignment operator
	SpaCSR & operator=(const SpaCSR & csr);
	SpaCSR & operator=(const SpaCOO & coo);

	// move copy assignment operator
	SpaCSR & operator=(SpaCSR && csr);

	// destructor 
	virtual ~SpaCSR(){}

	// overload the virtual function from base class, and print num rows in csr matrix 
	virtual void  PrintPartialMat(INT num);

	// row vector : row+1
	std::vector<INT> row_vec;

	// col vector : nnz
	std::vector<INT> col_vec;
};



#endif
