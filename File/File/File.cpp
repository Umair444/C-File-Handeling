#include "File.h"


using namespace std;

int main() 
{
	cout << "Hello World" << endl;

	File f1("text.txt", ',');

	string** filter = f1.Filter("5", 4, 1);

	cout << "Row: " << (int)filter[0][1][0] << endl;
	cout << "Columns: " << (int)filter[1][0][0] << endl;

	/*for (int i = 1; i < 3; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			cout << filter[i][j] << ", ";
		}
		cout << endl;
	}*/

	//cout << filter[1][1] << ", ";

	/*string str[] = { "LastTrain","77","7","7","7" };
	f1.Write(str);*/

	return 0;
}