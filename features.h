#ifndef features_h
#define features_h

#include <string>
#include <vector>
#include "base.h"
#include "sparsemat.h"
#include "json.hpp"

class MatrixFeatures
{
public:
	// constructor
	MatrixFeatures(){}
	MatrixFeatures(std::string mfile):mat_file(mfile){}

	// copy constructor
	MatrixFeatures(const MatrixFeatures & matft):mat_file(matft.mat_file),features(matft.features),mat(matft.mat){}

	// copy assignment constructor
	MatrixFeatures & operator=(const MatrixFeatures & matft);

	// destructor 
	~MatrixFeatures(){}

	// read matrix from coo, index in file begin with 0
	void ReadCOO0();

	// read matrix from coo, index in file begin with 1
	void ReadCOO1();

	// print the CSR matrix: from row 0 to row num
	void PrintCSRByRow(INT num);

	// output the features to a json file for future usage
	void DumpFeatures2JsonFile(const std::string json_file);

	//================================================================
	// extract features

	void Features_1_1_Nrows();

protected:
	std::string mat_file;
	nlohmann::json features;
	SpaCSR mat;

};

#endif
