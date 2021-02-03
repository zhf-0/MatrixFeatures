#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "features.h"
#include <iomanip>


MatrixFeatures & MatrixFeatures::operator=(const MatrixFeatures & matft)
{
	if(this == &matft)
		return *this;

	mat_file = matft.mat_file;
	features = matft.features;
	mat = matft.mat;
	return *this;
}


void MatrixFeatures::ReadCOO0()
{
	std::ifstream myfile(mat_file);
	// myfile.open(mat_file); 
	if(!myfile.is_open())
	{
		std::cout<<"can't open the matrix file!"<<std::endl;
		exit(1);
	}

	std::string line;
	getline(myfile,line);
	std::istringstream split_line(line);
	INT row, col, nnz;
	split_line >> row >> col >> nnz;
	SpaCOO coo(row,col,nnz);

	for(INT i=0;i<nnz;i++)
	{
		getline(myfile,line);
		std::istringstream tmp_line(line);
		tmp_line >> coo.row_vec[i] >> coo.col_vec[i] >> coo.val[i];
	}

	getline(myfile,line);
	if(!myfile.eof())
		std::cout<<"Reading file is not finished!"<< std::endl;
	
	myfile.close();

	mat = coo;
}

void MatrixFeatures::ReadCOO1()
{
	std::ifstream myfile(mat_file);
	// myfile.open(mat_file); 
	if(!myfile.is_open())
	{
		std::cout<<"can't open the matrix file!"<<std::endl;
		exit(1);
	}

	std::string line;
	getline(myfile,line);
	std::istringstream split_line(line);
	INT row, col, nnz;
	split_line >> row >> col >> nnz;
	SpaCOO coo(row,col,nnz);

	for(INT i=0;i<nnz;i++)
	{
		getline(myfile,line);
		std::istringstream tmp_line(line);
		INT tmp_i,tmp_j;
		tmp_line >> tmp_i >> tmp_j >> coo.val[i];
		coo.row_vec[i] = tmp_i - 1;
		coo.col_vec[i] = tmp_j - 1;
	}

	getline(myfile,line);
	if(!myfile.eof())
		std::cout<<"Reading file is not finished!"<< std::endl;
	
	myfile.close();

	mat = coo;
}

void MatrixFeatures::PrintCSRByRow(INT num)
{
	mat.PrintPartialMat(num);
}

void MatrixFeatures::DumpFeatures2JsonFile(const std::string json_file)
{
	std::ofstream j_file(json_file);
	j_file << std::setw(4) << features << std::endl;

}

void MatrixFeatures::Features_1_1_Nrows()
{
	std::string name = "nrows";
	INT val = mat.GetRow();
	features[name] = val;
}
