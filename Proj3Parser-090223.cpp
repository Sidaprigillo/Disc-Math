//Aprigillo, Resid Teomar
//090223
//works for all cases now...
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

class Parser
{
private:
    bool conclusion = false;

    int finder = 0;
    int forValid = 0;
    int decimalCount = 0;

    string chr = "";

    char extracted = 0;
    char *isValid = new char[1] {0};

public:
    void defaultValues()
    {
        conclusion = false;
        finder = 0;
        forValid = 0;
        decimalCount = 0;
        chr = "";

        extracted = 0;
        isValid[1] = {0};
    }

    bool isDouble(string input)
    {
        isValid[input.length() - 1] = {0};

        while (finder != input.length())
        {
            extracted = input[finder];

            if (isblank(extracted))
            {
                if (finder == 0)
                {
                    finder++;//nothing...
                }
                else if(extracted == input[finder-1])
                {
                    finder++;//do nothing really...
                }
                else
                {
                    while(finder != input.length())
                    {
                        finder++;
                        extracted = input[finder];
                        if(isdigit(extracted))
                        {
                            conclusion = false;
                            break;
                        }
                        else if (isalpha(extracted) && extracted != 'e')
                        {
                            conclusion = false;
                            break;
                        }
                        else
                        {
                            conclusion = true;
                        }
                    }
                    break;
                }
            }
            else if(isalpha(extracted))
            {
                if(extracted == 'e')
                {
                    if(input.length() == 1)
                    {
                        break;
                    }
                    else if(!isdigit(input[finder+1]))
                    {
                        if(input[finder+1] == '-')
                        {
                            isValid[forValid] = extracted;
                            forValid++;
                            conclusion = true;
                            finder++;
                        }
                        else if(!isalnum(input[finder+1]))
                        {
                            conclusion = true;
                            finder++;
                        }
                        else
                        {
                            conclusion = false;
                            break;
                        }
                    }
                    else
                    {
                        isValid[forValid] = extracted;
                        conclusion = true;
                        finder++;
                        forValid++;
                    }
                }
                else 
                {
                    conclusion = false;
                    break;
                }
            }
            else if(isdigit(extracted))
            {
                isValid[forValid] = extracted;
                conclusion = true;
                forValid++;
                finder++;
            }
            else if(ispunct(extracted))
            {
                if(extracted == '.')
                {
                    decimalCount++;
                    if(decimalCount > 1)
                    {
                        conclusion = false;
                        break;
                    }
                    if(input.length() == 1)
                    {
                        conclusion = false;
                        break;
                    }                    
                    else if (finder == 0)
                    {
                        isValid[forValid] = extracted;
                        forValid++;
                        if(isdigit(input[finder+1]))
                        {
                            finder++;
                        }
                        else
                        {
                            finder++;
                        }
                    }
                    else if(isdigit(input[finder-1]) || isdigit(input[finder+1])) 
                    {
                        isValid[forValid] = extracted;
                        conclusion = true;
                        forValid++;
                        finder++;
                        while(finder != input.length())
                        {
                            extracted = input[finder];
                            if(isdigit(extracted))
                            {
                                isValid[forValid] = extracted;
                                forValid++;
                                finder++;
                            }
                            else
                            {
                                conclusion = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        conclusion = false;
                        break;
                    }
                }
                else if(extracted == '-')
                {
                    if(input.length() == 1)
                    {
                        conclusion = false;
                        break;
                    }
                    else
                    {
                        isValid[forValid] = extracted;
                        forValid++;
                        finder++;
                        while(finder != input.length())
                        {
                            //finder++;
                            extracted = input[finder];
                            if(isdigit(extracted))
                            {
                                isValid[forValid] = extracted;
                                conclusion = true;
                                forValid++;
                                finder++;
                            }
                            else if (extracted == '.')
                            {
                                isValid[forValid] = extracted;
                                conclusion = true;
                                forValid++;
                                finder++;
                                break;
                            }
                            else
                            {
                                conclusion = false;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    conclusion = false;
                    break;
                }
            }
        }
        return conclusion;
    }

    void output(string input)
    {
        if (conclusion == true)
        {
            for (int i = 0; i < forValid; i++)
            {
                cout << isValid[i];
            }
            cout << " : this is a valid floating pt number with value: ";
            
            for (int i = 0; i < forValid; i++)
            {
                cout << isValid[i];
            }
            cout << endl;                        
        }
        else
        {
            cout << input << " : invalid floating pt number\n";
        }
    }

    void deleteA()
    {
        delete[] isValid;
    }

};

int main ()
{
    string input = "";

    Parser proj3;

    cout << "> ";
    while (getline(cin, input))
    {
        proj3.defaultValues();
        proj3.isDouble(input);
        proj3.output(input);

        cout << "> ";

    }

    proj3.deleteA();
    cout << "Hello World";
    return 0;
}