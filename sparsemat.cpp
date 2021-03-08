#include  "sparsemat.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

SparseMat & SparseMat::operator= (SparseMat && spamat)
{
	if(this == &spamat)
		return *this;

	row = spamat.row;
	col = spamat.col;
	nnz = spamat.nnz;
	val.swap(spamat.val);
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

SpaCOO & SpaCOO::operator=(SpaCOO && coo)
{
	if(this == &coo)
		return *this;

	SparseMat::operator=(coo);
	row_vec.swap(coo.row_vec);
	col_vec.swap(coo.col_vec);
	return *this;
}

void SpaCOO::PrintPartialMat(INT num)
{
	for(INT i=0;i<num;i++)
		std::cout<<row_vec[i]<<"   "<<col_vec[i]<<"   "<<val[i]<<std::endl;
}

void SpaCOO::ReadMat0(std::string file_name)
{
	std::ifstream myfile(file_name);
	if(!myfile.is_open())
	{
		std::cout<<"can't open the matrix file!"<<std::endl;
		exit(1);
	}

	std::string line;
	getline(myfile,line);
	std::istringstream split_line(line);
	split_line >> row >> col >> nnz;
	std::vector<INT> tmp_row_vec(nnz);
	std::vector<INT> tmp_col_vec(nnz);
	std::vector<DOUBLE> tmp_val(nnz);

	for(INT i=0;i<nnz;i++)
	{
		getline(myfile,line);
		std::istringstream tmp_line(line);
		tmp_line >> tmp_row_vec[i] >> tmp_col_vec[i] >> tmp_val[i];
	}

	getline(myfile,line);
	if(!myfile.eof())
		std::cout<<"Reading file is not finished!"<< std::endl;
	
	myfile.close();

	row_vec.swap(tmp_row_vec);
	col_vec.swap(tmp_col_vec);
	val.swap(tmp_val);
}

void SpaCOO::ReadMat1(std::string file_name)
{
	std::ifstream myfile(file_name);
	if(!myfile.is_open())
	{
		std::cout<<"can't open the matrix file!"<<std::endl;
		exit(1);
	}

	std::string line;
	getline(myfile,line);
	std::istringstream split_line(line);
	split_line >> row >> col >> nnz;
	std::vector<INT> tmp_row_vec(nnz);
	std::vector<INT> tmp_col_vec(nnz);
	std::vector<DOUBLE> tmp_val(nnz);

	for(INT i=0;i<nnz;i++)
	{
		getline(myfile,line);
		std::istringstream tmp_line(line);
		INT tmp_i,tmp_j;
		tmp_line >> tmp_i >> tmp_j >> tmp_val[i];
		tmp_row_vec[i] = tmp_i - 1;
		tmp_col_vec[i] = tmp_j - 1;
	}

	getline(myfile,line);
	if(!myfile.eof())
		std::cout<<"Reading file is not finished!"<< std::endl;
	
	myfile.close();

	row_vec.swap(tmp_row_vec);
	col_vec.swap(tmp_col_vec);
	val.swap(tmp_val);
}
//==========================================================
// class SpaCSR

SpaCSR::SpaCSR(const SpaCOO & coo):SparseMat( coo.GetRow(), coo.GetCol(), coo.GetNnz() ), 
	                         row_vec(coo.GetRow()+1), 
							 col_vec(coo.GetNnz()) 
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

SpaCSR & SpaCSR::operator=(SpaCSR && csr)
{
	if(this == &csr)
		return *this;

	SparseMat::operator=(csr);
	row_vec.swap(csr.row_vec);
	col_vec.swap(csr.col_vec);
	return *this;
}

void SpaCSR::PrintPartialMat(INT num)
{
	for(INT i=0;i<num;i++)
	{
		INT begin_idx = row_vec[i];
		INT num_entry = row_vec[i+1] - begin_idx;
		for(INT j=0;j<num_entry;j++)
			std::cout<<i<<"   "<<col_vec[begin_idx+j]<<"   "<<val[begin_idx+j]<<std::endl;
	}
}

