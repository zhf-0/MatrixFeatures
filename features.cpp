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
	SpaCOO coo;
	coo.ReadMat0(mat_file);
	mat = coo;
}

void MatrixFeatures::ReadCOO1()
{
	SpaCOO coo;
	coo.ReadMat1(mat_file);
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
