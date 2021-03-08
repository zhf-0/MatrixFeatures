#include "tensor.h"
#include <iostream>
#include "sparsemat.h"

//==========================================================
// class Vec
Vec & Vec::operator=(const Vec & vec)
{
	if(this == &vec)
		return *this;

	len = vec.len;
	val = vec.val;
	return *this;
}

Vec & Vec::operator=(Vec && vec)
{
	if(this == &vec)
		return *this;
	len = vec.len;
	val.swap(vec.val);
	return *this;
}

INT Vec::GetLen() const
{
	return len;
}

void Vec::PrintPartialTensor(INT num) const
{
	for(INT i=0;i<num;i++)
		std::cout<< val[i] <<std::endl;
}


Vec operator*(const SpaCSR & csr, const Vec & vec)
{
	if(csr.col == vec.len)
	{
		Vec tmpvec(csr.row);
		for(INT i=0;i<csr.row;i++)
		{
			DOUBLE row_sum = 0.0;
			INT begin_idx = csr.row_vec[i];
			INT end_idx = csr.row_vec[i+1];
			for(INT j=0;j<(end_idx - begin_idx);j++ )
			{
				INT csr_idx = begin_idx + j;
				row_sum += csr.val[csr_idx] * vec.val[csr.col_vec[csr_idx]];
			}
			tmpvec.val[i] = row_sum;
		}
		return tmpvec;
	}
	else
	{
		std::cout<<"the col number of matrix doesn't match the length of vec"<<std::endl;
		exit(1);
	}
}

DOUBLE & Vec::operator[](INT i)
{
	return val[i];
}
