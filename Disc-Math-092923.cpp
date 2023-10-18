//Aprigillo, Resid Teomar
//092923
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

class BitManipulator
{
private:
	unsigned bit32 = 0x0;
	unsigned bitMasker = 0x1;
public:
	BitManipulator()
	{
		show();
	}

	void show()
	{
		for(int x = 31; x >= 0; x--)
		{
			cout << " " << (((bitMasker << x) & bit32) >> x);
		}
		cout << endl;
	}

	void bitOn(int N)
	{
		if(error(N) == false)
		{
			return;
		}
		bit32 = ((0x1 << N-1) | bit32);
	}

	void bitOff(int N)
	{
		if(error(N) == false)
		{
			return;
		}
		int indexes[32] = {0};
		int iteration = 0;	
		for(int bit = 0; bit < 32; bit++)
		{
			unsigned tester = 0x1;
			int test = (((tester << bit) & bit32) >> bit);
			if(test == 1)
			{
				if(bit != N-1)
				{
					indexes[iteration] = bit;
					iteration++;
				}
			}
		}
		bit32 = (bit32 & 0x0);
		for(int x = 0; x < iteration; x++)
		{
			bit32 = bit32 | (0x1 << indexes[x]);
		}
	}

	void bitToggle(int N)
	{
		if(error(N) == false)
		{
			return;
		}
		bit32 = ((0x1 << N-1) ^ bit32);
	}

	void exitt(int value)
	{
		exit(value);
	}

	bool error(int N)
	{
		if(N > 32)
		{
			cerr << "Error, please choose bits 1-32 only" << endl;
			return false;
		}
		return true;
	}
};

class run : public BitManipulator
{
private:	
	string commands[5] = {"on", "off", "toggle", "showcommands","exit"};

public:
	void runProgram()
	{
		string input = "";
		string test = "";
		int N = 0;
		int option = 0;
		bool isPossible = false;

		cout << "input: ";
		getline(cin, input);
		stringstream ss(input);
		ss >> test;
		for(int x = 0; x < 5; x++)
		{
			if(test == commands[x])
			{
				option = x;
				isPossible = true;
				break;
			}
		}
		if(isPossible == false)
		{
			cerr << "Error. invalid input." << endl;
			runProgram();
			return;
		}	
		switch(option)
		{				
		case 0:
			if(!(ss >> N))
			{
				inputError();
				return;
			}
			bitOn(N);
			break;
		case 1:
			if(!(ss >> N))
			{
				inputError();
				return;
			}
			bitOff(N);
			break;
		case 2:
			if(!(ss >> N))
			{
				inputError();
				return;
			}
			bitToggle(N);
			break;
		case 3:
			showCommands();
			break;
		case 4:
			cout << "App terminated.";
			exitt(0);
		default:
			break;
		}
	}

	void inputError()
	{
		cerr << "Error. Please specify the bit in the second line." << endl;
		runProgram();
	}

	void showCommands()
	{
		cout << "Here are the commands: " << endl;
		cout << "**" << "on" << "            N" << endl;
		cout << "**" << "off" << "           N" << endl;
		cout << "**" << "toggle" << "        N" << endl;	
		cout << "**" << "showcommands" << endl;
		cout << "**" << "exit\n" << endl;
	}
};

int main(int argc, char const *argv[])
{
	run proj1;
	proj1.showCommands();
	while(1)
	{
		proj1.runProgram();
		proj1.show();
	}
	cout << "\nCode Compiled :)" << endl;
	return 0;
}