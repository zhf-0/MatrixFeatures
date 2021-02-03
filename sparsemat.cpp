#include  "sparsemat.h"
#include <iostream>

//==========================================================
// class SparseMat
SparseMat & SparseMat::operator= (const SparseMat & spamat)
{
	if(this == &spamat)
		return *this;

	row = spamat.row;
	col = spamat.col;
	nnz = spamat.nnz;
	val = spamat.val;
	return *this;
}

INT SparseMat::GetRow() const
{
	return row;
}

INT SparseMat::GetCol() const
{
	return col;
}

INT SparseMat::GetNnz() const
{
	return nnz;
}

//==========================================================
// class SpaCOO

SpaCOO & SpaCOO::operator=(const SpaCOO & coo)
{
	if(this == &coo)
		return *this;

	SparseMat::operator=(coo);
	row_vec = coo.row_vec;
	col_vec = coo.col_vec;
	return *this;
}


//==========================================================
// class SpaCSR

SpaCSR::SpaCSR(const SpaCOO & coo):SparseMat( coo.GetRow(), coo.GetCol(), coo.GetNnz() ), 
	                         row_vec(coo.GetRow()+1), 
							 col_vec(coo.GetCol()) 
{
	row_vec[0] = 0;
	for(INT i=0;i<nnz;i++)
		row_vec[coo.row_vec[i] + 1] += 1;

	std::vector<INT> num_per_row = row_vec;

	for(INT i=2;i<row+1;i++)
		row_vec[i] = row_vec[i] + row_vec[i-1];

	for(INT i=0;i<nnz;i++)
	{
		INT r_idx = coo.row_vec[i];
		INT begin_idx = row_vec[r_idx]; 
		INT end_idx = row_vec[r_idx + 1];
		INT offset = end_idx - begin_idx - num_per_row[1 + r_idx];

		num_per_row[1 + r_idx] -= 1;
		
		if(offset == end_idx - begin_idx)
		{
			std::cout<<"Converting COO to CSR(assignment function): the index is wrong!"<<std::endl;
			exit(1);
		}
		else
		{
			col_vec[begin_idx + offset] = coo.col_vec[i];
			val[begin_idx + offset] = coo.val[i];
		}
	}
}



SpaCSR & SpaCSR::operator=(const SpaCSR & csr)
{
	if(this == &csr)
		return *this;

	SparseMat::operator=(csr);
	row_vec = csr.row_vec;
	col_vec = csr.col_vec;
	return *this;
}


SpaCSR & SpaCSR::operator=(const SpaCOO & coo)
{
	/* SparseMat::operator=(coo); */
	row = coo.GetRow();
	col = coo.GetCol();
	nnz = coo.GetNnz();

	row_vec.resize(row+1) ;
	col_vec.resize(nnz);
	val.resize(nnz);

	row_vec[0] = 0;
	for(INT i=0;i<nnz;i++)
		row_vec[coo.row_vec[i] + 1] += 1;

	std::vector<INT> num_per_row = row_vec;

	for(INT i=2;i<row+1;i++)
		row_vec[i] = row_vec[i] + row_vec[i-1];

	for(INT i=0;i<nnz;i++)
	{
		INT r_idx = coo.row_vec[i];
		INT begin_idx = row_vec[r_idx]; 
		INT end_idx = row_vec[r_idx + 1];
		INT offset = end_idx - begin_idx - num_per_row[1 + r_idx];

		num_per_row[1 + r_idx] -= 1;
		
		if(offset == end_idx - begin_idx)
		{
			std::cout<<"Converting COO to CSR(assignment function): the index is wrong!"<<std::endl;
			exit(1);
		}
		else
		{
			col_vec[begin_idx + offset] = coo.col_vec[i];
			val[begin_idx + offset] = coo.val[i];
		}
	}

	return *this;
}


