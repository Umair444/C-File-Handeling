#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

#pragma once
class File
{
public:
	File(std::string, char, char*);
	~File();

	// Functions
	int CountRows();
	int CountColumns();
	std::string* Series(int, int);
	std::string** Filter(std::string, int, int);
	std::string** Join(File& obj, int c1, int c2);

	void Write(std::string[]);			// Add a row
	void transpose();

	// Operators for Join

private:
	int rows;
	int columns;
	std::string filename;
	int delimeter;
	std::string** matrix;
	char* columnMetaData;				// Data type of Each Coloumn

	std::string* Split(std::string, int);
	std::string** SplitAll();
	void TrueDataTypes(std::string *);
};

File::File(std::string filename, char delimeter, char* Types = nullptr)
{
	this->filename = filename;
	this->delimeter = delimeter;
	this->rows = CountRows();
	this->columns = CountColumns();
	this->matrix = SplitAll();

	columnMetaData = new char[columns + 1];
	if (Types == nullptr)
	{
		for (int i = 1; i < columns + 1; i++)
			this->columnMetaData[i] = 's';
	}
	else
	{
		for (int i = 1; i < columns + 1; i++)
			this->columnMetaData[i] = Types[i];
	}
}

File::~File()
{
}

int File::CountRows() 
{
	std::ifstream myfile(filename);
	std::string line;

	int count = 0;

	// Check if filename is right
	if (!myfile.is_open()) {
		std::cout << "Filename Incorrect";
		exit(-1);
	}
	// Count
	while (!myfile.eof()) {
		getline(myfile, line);
		count++;
	}

	return count;
}

inline int File::CountColumns()
{
	int count = 0;
	std::string line;

	if (line == "")
	{
		std::ifstream myfile(filename);
		getline(myfile, line);
	}

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == delimeter)
			count++;
	}
	return count + 1;
}

inline std::string* File::Split(std::string out, int size = 0)
{
	if (size == 0)
		size = columns;

	size_t foundF = 0, foundL = 0;
	std::string* data = new std::string[size];
	for (int i = 0; i < size; i++)
	{
		foundL = out.find(delimeter, foundF);
		data[i] = out.substr(foundF, foundL - foundF);
		foundF = foundL + 1;
	}

	return data;
}

inline std::string** File::SplitAll()
{
	/*
	STEPS
	1. Allocate 2D memory
	2. Split the data
	3. get line results -> save it as [r][c]
	4. return double string array
	*/
	std::string line;
	std::ifstream myfile(filename);
	std::string** out = new std::string * [rows+1];
	for (int i = 0; i < rows+1; i++)
		out[i] = new std::string[columns+1];

	if (myfile.is_open()) {
		for (int r = 1; r < rows+1; r++) {
			getline(myfile, line);
			std::string* temp = Split(line);
			for (int c = 1; c < columns+1; c++)
				out[r][c] = temp[c-1];
			
		}
	}

	out[0][1] = rows;
	out[1][0] = columns;

	return out;
}

inline void File::TrueDataTypes(string* data)
{
	// Convert a column to True Data Types given in columnMetaData

	int* i = new int[rows];
	double* d = new double[rows];
	string* s = new string[rows];
	time* t = new time[rows];

	for (int var = 0; var < columns; var++)
	{
		switch (columnMetaData[var])
		{
		case ('i'):
			for (int fill = 0; fill < rows; fill++)
			{
				i[fill] = (int)matrix[fill][var][0];
			}
			break;
		case ('d'):
			for (int fill = 0; fill < rows; fill++)
			{
				d[fill] = (double)matrix[fill][var][0];
			}
			break;
		case ('t'):
			for (int fill = 0; fill < rows; fill++)
			{
				t[fill] = (int)matrix[fill][var][0];
			}
			break;
		case ('s'):
			for (int fill = 0; fill < rows; fill++)
			{
				s[fill] = matrix[fill][var];
			}
			break;
		default:
			break;
		}
	}
}

inline std::string* File::Series(int index, int axis = 0)
{
	// For Column
	if (axis == 0)
	{
		if (index > rows)
		{
			std::cout << "Input the Correct Dimensions";
			exit(-1);
		}

		std::string* out = new std::string[rows];
		for (int i = 0; i < rows; i++)
		{
			out[i] = matrix[i][index];
		}

		return out;
	}
	// For Row
	else if (axis == 1)
	{
		if (index > columns)
		{
			std::cout << "Input the Correct Dimensions";
			exit(-1);
		}

		std::string* out = new std::string[columns];
		for (int i = 0; i < columns; i++)
		{
			out[i] = matrix[index][i];
		}

		return out;
	}
	// Break
	else
	{
		std::cout << "Input axis = 0|1";
		exit(-1);
	}
}

inline std::string** File::Filter(std::string search, int index, int file)
{
	int count = 1;
	// Convert to Matrix
	std::string** out = new std::string* [rows+1];
	for (int i = 0; i < rows+1; i++)
		out[i] = new std::string[columns+1];

	for (int i = 1; i < rows + 1; i++)
	{
		if (matrix[i][index] == search)
		{
			for (int j = 1; j < columns + 1; j++)
			{
				out[count][j] = matrix[i][j];		// Store all the columns
			}
			count++;
		}
	}

	out[0][1] = count - 1;
	out[1][0] = columns;

	//out[0][columns + 1] = std::to_string(count);
	std::cout << "Query Generated Successfully" << std::endl;

	if (file == 1)		// Generate a seperate File
	{
		std::ofstream filterFile("Filter.txt");
		for (int r = 1; r < count; r++) {
			for (int c = 1; c < columns + 1; c++)
			{
				filterFile << out[r][c] << ",";
			}
			filterFile << std::endl;
		} 
	}
	return out;
}

inline std::string** File::Join(File& obj, int c1, int c2)
{
	int r1 = rows, r2 = obj.CountRows();
	int maxR = r1 * r2 * r2;
	int r0 = 0;

	int c1 = columns, c2 = obj.CountColumns();
	// Convert both files to matrices
	string** f1 = matrix;
	string** f2 = obj.SplitAll();
	string** out = new string * [maxR];		// rows
	for (int i = 0; i < maxR; i++)  		// coloumns of every row allocation (+1 for size)
		out[i] = new string[c1 + c2 + 1];


	// Match using columns
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < r2; j++)
		{
			if (f1[i][c1] == f2[j][c2])
			{
				for (int k = 0; k < c1; k++) {
					out[r0][k] = f1[i][k];
					// 	cout << out[r0][k];
				}
				for (int l = 0; l < c2; l++) {
					out[r0][l + c1] = f2[j][l];
					// 	cout << out[r0][l+nof1];
				}
			}
		}
		r0++;			// After Extracting all the rows in one new column
		//	cout << endl;
	}
	out[0][c1 + c2] = to_string(r0);
}

inline void File::Write(std::string data[])
{
	std::ofstream out(filename, std::ios::app); // Always Append

	if (out.is_open()) {
		out << '\n';
		for (int i = 0; i < columns; i++) {
			out << data[i];
			if (i != columns - 1)
				out << ',';
		}
		out.close();
	}
}

inline void File::transpose()
{
	std::ofstream out(filename);

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			out << matrix[c][r];
			if (c != columns - 1)
				out << ',';
		}
		out << '\n';
	}
}

