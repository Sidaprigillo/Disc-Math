//Aprigillo, Resid Teomar
//02/18/23
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

class adder
{
public:

void addi()
{
    //first mode
    cout << "input values (w/ spaces): ";
    getline(cin, input);
    if (input.length() != 0)
    {
        storeString << input;

        int test = 0;
        while (storeString >> store[test])
        {
            test++;
        }

        while(a < test)
        {
            string extraTest = "";
            general << store[a];

            if (general >> all[a])
            {
                general >> extraTest;

                if (extraTest.length() == 0)
                {
                    strict[b] = all[a];
                    vlaid = true;
                    b++;
                }

                else
                {
                    wExtra[c] = all[a];
                    extras[c] = extraTest;
                    c++;
                    wPartial = true;
                    fullyValid = false;
                }
            }
            else
            {
                invalid[d] = store[a]; // for invalid inputs

                invalidd = true;
                fullyValid = false;
                d++;
            }

            general = stringstream();
            a++;
        }
        if (c == 0 && b == 0)
        {
            trueInvalid = true;
        }
        // output checking
        if (fullyValid == false)
        {
            if (invalidd == true)
            {
                for (int i = 0; i < d; i++)
                {
                    cout << "not valid: " << invalid[i] << endl;
                }
            }
            if (wPartial == true)
            {
                for (int i = 0; i < c; i++) // print extra chars
                {
                    cout << "number " << wExtra[i] << " with extra characters: " << extras[i] << endl;
                }

                for (int i = 0; i < a; i++) // sum of partials
                {
                    sumP = sumP + all[i];
                }

                cout << "sum of including partly valid items: " << sumP << endl;
            }

            if(vlaid == true)
            {
                for (int i = 0; i < b; i++) // sum of strict
                {
                    sumS = sumS + strict[i];
                }

                cout << "sum of valid items: " << sumS << endl;
            }

            if(vlaid == false)
            {
                cout << "no fully valid items found" << endl;
            }

        }

        if (fullyValid == true)
        {
            for (int i = 0; i < b; i++) // sum of strict
            {
                sumS = sumS + strict[i];
            }

            cout << "sum of all items: " << sumS << endl;
        }

        if (trueInvalid == true)
        {
            cout << "no fully valid items found" << endl;
        }
    }

    else
    {
        bonk = true;
    }
}


void interactive()
{
     if (bonk == true)
     {
        cout << "Entering interactive mode..." << endl;
        cout << "Type numbers to be added, STRICTLY ONE per line. Ctrl-Z to end input" << endl;
        while (getline(cin, input))
        {
            extraTest = "";

            ss1 << input;
            ss1 >> store[a];
            general << store[a];

            if (general >> all[a])
            {
                general >> extraTest;
                if (extraTest.length() == 0)
                {
                    strict[b] = all[a];
                    vlaid = true;
                    b++;
                }
                else
                {
                    wExtra[c] = all[a];
                    extras[c] = extraTest;
                    cout << "number " << wExtra[c] << " with extra characters: " << extras[c] << endl;
                    c++;
                    wPartial = true;
                }
            }

            else
            {
                cout << "invalid input: " << input << endl;
            }
            a++;
            ss1 = stringstream();
            general = stringstream();
        }

        if (c == 0 && b == 0)
        {
            trueInvalid = true;
        }

        if (trueInvalid == false)
        {
            if (wPartial)
            {
              for (int i = 0; i < a; i++) // sum of partials
                {
                    sumP = sumP + all[i];
                }
                cout << "sum of including partly valid items: " << sumP << endl;
            }

            if(vlaid == true)
            {
                for (int i = 0; i < b; i++) // sum of strict
                {
                    sumS = sumS + strict[i];
                }

                cout << "sum of valid items: " << sumS << endl;
            }

            if (vlaid == false)
            {
                cout << "no fully valid items found" << endl;
            }

        }

        if (trueInvalid == true)
        {
            cout << "no fully valid items found" << endl;
        }
     }
}

private:
    string input;
    stringstream ss1;
    stringstream storeString;
    stringstream general;
    double strict[9999];
    double all[9999];
    double wExtra[9999];
    string extras[9999];
    string store[9999];
    string invalid[9999];
    string extraTest = "";
    double sumS = 0;
    double sumP = 0;

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    bool bonk = false;
    bool wPartial = false;
    bool fullyValid = true;
    bool invalidd = false;
    bool vlaid = false;
    bool trueInvalid = false;
};


int main()
{
    adder one;
    one.addi();
    one.interactive();

    cout << "\nHello world!" << endl;
    return 0;
}
