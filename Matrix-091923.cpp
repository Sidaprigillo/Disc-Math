//Aprigillo, Resid Teomar
//091923

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class matrices
{
private:
	string line = "";
	string name = "";

	int index = 0;
	int column = 0;
	int row = 0;
	int ind = 0;
	int columnChcker = 0;

	vector<double> matrix;
	vector<double> computedValues;
	double value = 0;
	double testing = 0;

	bool isValid = false;
	bool import = false;

	ifstream fileopen;
	ofstream fileoutput;

public:
	void resetvalues()
	{
		line = "";
		index = 0;
		column = 0;
		row = 0;
		ind = 0;
		columnChcker = 0;
		matrix.clear();
		value = 0;
		testing = 0;
		isValid = false;
	}

	void parse(string filename)
	{
	   name = filename;
	   fileopen.open(filename);
	   if (fileopen.is_open())//if file is opened
	   {
	   		resetvalues();
            stringstream test;
            getline(fileopen, line);//get the first line
            test << line;
   			if(test >> testing) //process first line
   			{
   				matrix.push_back(testing);
   				column++;
   	 			while(test >> value)
	   			{
	   				matrix.push_back(value);
	   				column++;
	   			}
	   			isValid = true;
	   			row++;
   			}
   			else
            {
                cerr << "invalid matrix, matrix starts with: " << line << endl;
                cerr << "which is not a valid floating pt. matrix should start with a valid first line." << endl;
                fileopen.close();
                return;
            }

   			if(isValid == true)//process succeeding lines if the first line is valid
            {
                while(1)
                {
                    stringstream test;
                    columnChcker = 0;
                    line = "";
                    getline(fileopen, line);

                    test << line;
                    if(test >> testing)
                    {
                    	matrix.push_back(testing);
                    	columnChcker++;
                        while(test >> value)
                        {
                        	matrix.push_back(value);
                            columnChcker++;
                        }
                        matrix.shrink_to_fit();
                        row++;

                        if(columnChcker != column) //check if the matrix has a consistent/valid columns all throughout
                        {
                        	cerr << "error, matrix is invalid. row: " << row << ", has an invalid number of columns: " << columnChcker << endl;
                        	fileopen.close();
                        	return;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

	   		fileopen.close();
	   		import = true;
	   		cout << "this is the contents of " << filename << ":\n";
	   		for(int r = 0; r < row; r++)
	   		{
	   			for(int c = 0; c < column; c++)
	   			{
	   				cout << setw(7) << matrix[ind];
	   				ind++;
	   			}
	   			cout << endl;
	   		}

	   		matrix.shrink_to_fit(); //after processing the vector, shrink to fit the size/length
	   		cout << endl;
	   		cout << "this is the number of rows: " << row << endl;
	   		cout << "this is the number of columns: " << column << endl << endl;
	   }
	   else
	   {
	   		cerr << "file not opened\n";
	   		fileopen.close();
	   		return;
	   }
	}

	string getInput()
	{
		string option = "";
		cout << "please choose among the options by entering its corresponding number:\n";
		cout << " [1]import new matrix file for matrix a\n" << " [2]import new matrix file for matrix b\n" << " [3]addition\n"
		<< " [4]subtraction\n" << " [5]product of AB\n" << " [6]product of BA\n" << " [7]export\n"
		<< " [8]terminate application\n";
		cout << "\ninput: ";
		cin >> option;

		//cout << matrix[0][0] << endl; //nice. this shit is in a different dimension...
		return option;
	}

	void processmatrix(double * functionmatrix, vector<double> rawmatrix, int row, int column)//for processing the matrix within a function
	{
		index = 0;
		for(int r = 0; r < row; r++)
 		{
 			for(int c = 0; c < column; c++)
   			{
   				functionmatrix[index] = rawmatrix[index];
   				index++;
   			}
   		}
	}

	void subtractOradd(vector<double> matrixa, vector<double> matrixb, int rowa, int rowb, int columna, int columnb, int option)
	{
		if((rowa != rowb) || (columnb != columna)) //check if both matrice have the same dimensions
		{
			cerr << "Error. cannot perform proper addition or subtraction," << endl;
			cout << "both matrices should have the same dimensions" << endl << endl;
			return;
		}

		double Amatrix[(rowa*columna)] = {0};
		double Bmatrix[(rowb*columnb)] = {0};
		double operate = 0;
		computedValues.clear();

		processmatrix(Amatrix, matrixa, rowa, columna);
		processmatrix(Bmatrix, matrixb, rowb, columnb);

   		index = 0;
   		if(option == 4)
   		{
   			cout << "\nthis is the subtraction of matrices A and B: " <<endl;
	   		for(int r = 0; r < rowa; r++) //subtract the matrices
	   		{
	   			for(int c = 0; c < columna; c++)
	   			{
	   				operate = Amatrix[index] - Bmatrix[index];
	   				computedValues.push_back(operate);
	   				cout << setw(7) << computedValues[index];
	   				index++;
	   			}
	   			cout << endl;
	   		}
   		}
   		else if(option == 3)
   		{
	   		cout << "\nthis is the addition of matrices A and B: " <<endl;
	   		for(int r = 0; r < rowa; r++) //add the matrices
	   		{
	   			for(int c = 0; c < columna; c++)
	   			{
	   				operate = Amatrix[index] + Bmatrix[index];
	   				computedValues.push_back(operate);
	   				cout << setw(7) << computedValues[index];
	   				index++;
	   			}
	   			cout << endl;
	   		}
   		}
   		column = columnb;
	   	row = rowb;
	}

	void multiplication(vector<double> matrixI, vector<double> matrixJ, int columnI, int columnJ,
		int rowI, int rowJ, string nameX, string nameY)
	{
		if(columnI == rowJ)
		{
			double passI[rowI][columnI] = {0};
			double passJ[rowJ][columnJ] = {0};
			double multArr[rowI][columnJ] = {0};
			double operate = 0;
			computedValues.clear();
			int tracker = 0;

			column = columnJ;
			row = rowI;
			for(int r = 0; r < rowI; r++) //process values of matrixI
			{
				for(int c = 0; c < columnI; c++)
				{
					passI[r][c] = matrixI[tracker];
					tracker++;
				}
			}

			tracker = 0;
			for(int r = 0; r < rowJ; r++) //process values of matrixJ
			{
				for(int c = 0; c < columnJ; c++)
				{
					passJ[r][c] = matrixJ[tracker];
					tracker++;
				}
			}

			index = 0;
			cout << "\nthis is the multiplication of the matrices: " << nameX << " & " << nameY << endl;
			for(int x = 0; x < rowI; x++)
			{
				for(int r = 0; r < columnJ; r++)
				{
					for(int c = 0; c < columnI; c++)
					{
						multArr[x][r] += passI[x][c] * passJ[c][r];
					}
					computedValues.push_back(multArr[x][r]);
					cout << setw(10) << computedValues[index];
					index++;
				}
				cout << endl;
			}
			cout << endl;
		}
		else
		{
			cerr << "error. cannot perform multiplication between the matrices." << endl;
			cout << "the row of " << nameX << ", with value: " << rowI
			<< ", should be equal to the column of " << nameY << ", with value: " << columnJ <<	endl;
			return;
		}
	}

	void execute(vector<double> matrixa, vector<double> matrixb, int rowa, int rowb, int columna, int columnb, int option,
		string fileone, string filetwo)
	{
		switch(option)
		{
		case 3: //addition
			subtractOradd(matrixa, matrixb, rowa, rowb, columna, columnb, option);
			break;

		case 4: //subtraction
			subtractOradd(matrixa, matrixb, rowa, rowb, columna, columnb, option);
			break;
		case 5: //product of AB
			multiplication(matrixa, matrixb, columna, columnb, rowa, rowb, fileone, filetwo);
			break;
		case 6: //product of BA
			multiplication(matrixb, matrixa, columnb, columna, rowb, rowa, filetwo, fileone);
			break;
		case 7: //export
			exportMatrixOutput();
			break;
		case 8: //terminate
			cout << "application terminated...";
			break;
		default:
			cout << "input not among the options supported by the program." << endl;
			cout << "please try again..." << endl;
			break;
		}
	}

	int columnvalue()
	{
		return column;
	}

	int rowvalue()
	{
		return row;
	}

	string getFileName()
	{
		return name;
	}

	vector<double> getMatrixValue()
	{
		return matrix;
	}

	bool returnImportValue()
	{
		return import;
	}

	void exportMatrixOutput()//export output matrix
	{
		if(computedValues.empty())
		{
			cerr << "error. cant export computed values, no values found" << endl;
			return;
		}
		string outputName = "";
		cout << "please specify filename: ";

		cin.ignore();
		getline(cin, outputName);
		fileoutput.open(outputName);

		if(fileoutput.is_open())
		{
			index = 0;
			//fileoutput << "this is the output matrix: " << endl;
			for(int r = 0; r < row; r++)
			{
				for(int c = 0; c < column; c++)
				{
					fileoutput << setw(10) << computedValues[index];
					index++;
				}
				fileoutput << endl;
			}
			fileoutput << endl << "With row value: " << row << endl;
			fileoutput << "And column value: " << column << endl;
			cout << "successfully exported, with file name: " << outputName << endl;
		}
		else
		{
			cerr << "failed to export file, with file name: " << outputName << endl;
			return;
		}
		fileoutput.close();
	}
};

int main(int argc, char const *argv[])
{
	int test = 0;
	int option = 0;
	bool firstattempt = true;
	bool succeedingattempt = false;
	string input = "";
	matrices a;
	matrices b;
	matrices output;

	while(a.returnImportValue() == false || b.returnImportValue() == false)
	{
		while(a.returnImportValue() == false)
		{
			if(firstattempt == true)
			{
				cout << "please specify the filename of matrix a: ";
			}
			else if(succeedingattempt == true) //if input file name still cant be opened
			{
				while(1)
				{
					cout << "do you still want to proceed? (y)/(n): ";
					cin >> input;
					cin.ignore();
					if(input == "n" || input == "N")
					{
						cout << "program terminated...";
						return 0;
					}
					else if (input == "y" || input == "Y")
					{
						cout << "please input the filename for matrix a again: ";
						break;
					}
					else
					{
						cout << "Input invalid." << endl;
					}
				}
			}
			else
			{
				cout << "please input the filename for matrix a again: ";
				succeedingattempt = true;
			}
			getline(cin, input);
			a.parse(input);
			firstattempt = false;
		}

		firstattempt = true;
		succeedingattempt = false;
		while(b.returnImportValue() == false)
		{
			if(firstattempt == true)
			{
				cout << "please specify the filename of matrix b: ";
			}
			else if(succeedingattempt == true) //if input file name still cant be opened
			{
				while(1)
				{
					cout << "do you still want to proceed? (y)/(n): ";
					cin >> input;
					cin.ignore();
					if(input == "n" || input == "N")
					{
						cout << "program terminated...";
						return 0;
					}
					else if (input == "y" || input == "Y")
					{
						cout << "please input the filename for matrix b again: ";
						break;
					}
					else
					{
						cout << "Input invalid." << endl;
					}
				}
			}
			else
			{
				cout << "please input the filename for matrix b again: ";
				succeedingattempt = true;
			}
			getline(cin,input);
			b.parse(input);
			firstattempt = false;
		}
	}

	while(1)
	{
		input = "";
		option = 0;
		stringstream ss;

		input = output.getInput();
		ss << input;
		if(ss >> option)
		{
			if(option == 8)
			{
				cout << "application terminated";
				break;
			}
			else if(option == 1 || option == 2)
			{
				input = "";
				cin.ignore();
				cout << "please input the filename: ";
				getline(cin, input);
				switch(option)
				{
					case 1:
						a.parse(input);
						break;
				    case 2:
				    	b.parse(input);
				    	break;
				    default:
				    	break;
			    }
			}
			else
			{
				output.execute(a.getMatrixValue(), b.getMatrixValue(), a.rowvalue(), b.rowvalue(), a.columnvalue(),
					b.columnvalue(), option, a.getFileName(), b.getFileName());
			}
		}
		else
		{
			cout << "input invalid. input should be a valid number that corresponds to any of the supported instructions\n";
		}
	}

	return 0;
}
