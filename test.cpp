#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp"
#include <iomanip>

#include "sparsemat.h"

void TestFileReading()
{
	std::ifstream myfile("matrix.dat");
	// myfile.open(mat_file); 
	if(!myfile.is_open())
	{
		std::cout<<"can't open the matrix file!"<<std::endl;
		exit(1);
	}

	std::string line;
	getline(myfile,line);
	std::istringstream split_line(line);
	int row, col, nnz;
	split_line >> row >> col >> nnz;
	std::cout<<row<<"  "<<col<<"  "<<nnz<<std::endl;
	
	int i_idx, j_idx;
	double val;

	for(int i=0;i<nnz;i++)
	{
		getline(myfile,line);
		std::istringstream tmp_line(line);
		tmp_line >> i_idx >> j_idx >> val;
		std::cout<< i_idx << "   "<<j_idx<<"   "<<val<<std::endl;
	}

	getline(myfile,line);
	if(!myfile.eof())
		std::cout<<"Reading file is not finished!"<< std::endl;
	
	myfile.close();
}

void TestJSON()
{
	nlohmann::json features;
	std::string name = "nrow";
	int n=10;
	features[name] = n;

	std::ofstream jsonfile("test.json");
	jsonfile << std::setw(4) << features << std::endl;
}

SpaCOO foo()
{
	std::cout<<"enter foo() function"<<std::endl;
	std::string file="matrix.dat";
	SpaCOO coo;
	coo.ReadMat0(file);
	std::cout<<"leave foo() function"<<std::endl;
	return coo;
}

void TestMatrix()
{
	/* SpaCOO a; */
	SpaCOO a(3,3,4);
	a = foo();
	/* SpaCOO a(foo()); */
	std::cout<<a.GetRow()<<std::endl;
}

int main()
{
	/* TestFileReading(); */
	/* TestJSON(); */
	TestMatrix();
	return 0;
}
