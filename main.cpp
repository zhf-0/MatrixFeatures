#include <string>
#include "features.h"

int main()
{
	std::string file("matrix.dat");
	MatrixFeatures ft(file);
	ft.ReadCOO0();
	//ft.PrintCSRByRow(2);
	ft.Features_1_1_Nrows();
	ft.DumpFeatures2JsonFile("main_features.json");
	return 0;
}
