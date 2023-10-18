//Aprigillo, Resid Teomar
//early.cpp
//02/21/23
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

class engg151Signal
{
 public:

 engg151Signal()
 {
    double x[1] = {0};
    int startindex = 0;
 }

 engg151Signal ( double * x, int start, int duration );
 bool importSignalFromFile (string filename)
 {
   fileopen.open(filename);
   if (fileopen.is_open())
   {
     stringstream aaaa;
     getline(fileopen, input);
     inputi << input;
     inputd << input;
     inputt << input;
     aaaa << input;

     if (inputi >> Istartvalue)
     {
       inputd >> Fltvalue;
       inputt >> thirdTest;
       if (Istartvalue == Fltvalue)
       {
         inputi >> extra;
         if(extra.length() == 0)
         {
           Istartvalue = 0;
         }
         else
         {
           if (inputd >> Fltvalue)
           {
             inputt >> thirdTest;
             Fltvalue = thirdTest;
             if (inputt >> extra)
             {
               //cout << "found an extra: " << extra << endl;
             }
           }
           else
           {
             Istartvalue = 0;
             Fltvalue = thirdTest;
             inputt >> dbouelextra;
             //cout << "found a commment: " << dbouelextra << endl;
           }
         }
       }
       else
       {
         Istartvalue = 0;
         inputd >> extra;
         if (extra.length() != 0)
         {
           if (inputt >> Fltvalue)
           {
             //floatStarter = true;
           }
           else
           {
             //noStarter = true;
             //floatStarter = true;
             Fltvalue = thirdTest;
             inputd >> extra;
             //cout << "found a comment: " << extra << endl;
           }
         }
       }
       //succeeding lines
       endValue = Istartvalue;
       int t = 0;
       while (t == 0)
       {
         stringstream ss1;
         string sss;

         getline(fileopen, sss);
         ss1 << sss;
         if (ss1 >> succeeding)
         {
           values.push_back(succeeding);
           /*if (ss1 >> eextra)
           {
             cout << "fuond a comment: " << eextra << endl;
           }*/
           endValue++;
         }
         else
         {
           t = 1;
         }
       }

       values.insert(values.begin(), Fltvalue);
       values.shrink_to_fit();
       x = values.capacity();
       durationValue = endValue - Istartvalue + 1;
       signalvalues = new double[x]{0};

       if (durationValue != 0)
       {
         durationKnown = true;
       }

       if (durationKnown == true)
       {
         for (int i = 0; i < x; i++)
         {
           signalvalues[i] = values[i];
         }
       }

       //space
       imported = true;
       return imported;
     }

     else //for non-int, but possible floatpt, input in first line
     {
       if(aaaa >> Fltvalue)
       {
         floatStarter = true;
       }
       if(floatStarter == true)
       {
         Istartvalue = 0;
         inputt >> thirdTest;
         inputd >> extra;
         if (extra.length() != 0)
         {
           if (inputd >> Fltvalue)
           {
             //floatStarter = true;
             //cout << "tiiiiiiis\n";
           }
           else
           {
             //noStarter = true;
             //floatStarter = true;
             Fltvalue = thirdTest;
             inputd >> extra;
             //cout << "found a comment: " << extra << endl;
           }
         }

         //succeeding lines
         endValue = Istartvalue;
         int t = 0;
         while (t == 0)
         {
           stringstream ss1;
           string sss;

           getline(fileopen, sss);
           ss1 << sss;
           if (ss1 >> succeeding)
           {
             values.push_back(succeeding);
             /*if (ss1 >> eextra)
             {
               cout << "fuond a comment: " << eextra << endl;
             }*/
             endValue++;
           }
           else
           {
             t = 1;
           }
         }

         values.insert(values.begin(), Fltvalue);
         values.shrink_to_fit();
         x = values.capacity();
         durationValue = endValue - Istartvalue + 1;
         signalvalues = new double[x]{0};

         if (durationValue != 0)
         {
           durationKnown = true;
         }

         if (durationKnown == true)
         {
           for (int i = 0; i < x; i++)
           {
             signalvalues[i] = values[i];
           }
         }

         //space
         imported = true;
         return imported;
       }
       else
       {
         inputd >> dbouelextra;
         cout << "invalid first line: " << dbouelextra << endl;
         cout << "must start with an int or float" << endl;
         imported = false;
         return imported;
       }
     }
   }
   else
   {
     imported = false;
     return imported;
   }
 }

 void feedback(bool fed, string name, int startIndex, int crossDuration)
 {
   if (fed == true)
   {
     cout << "Signal with start index " << startIndex << ", duration " << crossDuration << ", imported from " << name << endl;
   }

   else
   {
     cout << "Unable to import a valid signal from " << name << endl;
   }
 }

 void feedback2(bool fed, string name, int crossshift, int crossDuration)
 {
   if (fed == true)
   {
     cout << "\nCrosscorrelation signal with start index " << crossshift << ", duration " << crossDuration << ", exported to " << name << endl;
   }

   else
   {
     cout << "Unable to export signal with start index " << crossshift << ", duration " << crossDuration << ", to " << name << endl;
   }
 }

 bool exportSignalToFile ( string filename )
 {
   ofstream exporr;
   exporr.open(filename);

   if (exporr.is_open())
   {
     exporr << shift;

     for (int i = 0; i < corrDuration; i++)
     {
       exporr << "         " << nxcorr[i] << endl;
     }

     exporr.close();

     exported = true;
     return exported;
   }
   else
   {
     return exported;
   }
 }

 int start()
 {
   return Istartvalue;
 }
 int end1/*end*/()
 {
   return endValue;
 }
 int duration()
 {
   return durationValue;
 }

 void compute (double * x, double * y, int xDuration, int yDuration, int xS, int yS)
 {
   corrDuration = xDuration + yDuration - 1;

   double xN[corrDuration] = {0};
   double yN[corrDuration] = {0};

   double xave; // for x
   for (int i = 0; i < xDuration; i++)
   {
     xave += x[i];
   }
   xave = xave / xDuration;

   //comput x(n)
   for (int i = 0; i < xDuration; i++)
   {
     xN[i] = x[i] - xave;
   }

   double yave; // for y
   for (int i = 0; i < yDuration; i++)
   {
     yave += y[i];
   }
   yave = yave / yDuration;

   //comput y(n)
   for (int i = 0; i < yDuration; i++)
   {
     yN[i] = y[i] - yave;
   }

   //shifting the values of xN and yN
   if (xS < 0)
   {
     //for X
     for (int i = 0; i > xS; i--)// shifting xN to left
     {
       double temp = xN[0];

       for(int i = 0; i < corrDuration - 1; i++)
       {
         xN[i] = xN[i+1];
       }
       xN[corrDuration-1] = temp;
     }
   }
   else
   {
     for (int i = 0; i < xS; i++) //shifting xN to the right
     {
       double temp = xN[corrDuration - 1]   ;
       for (int i = corrDuration - 1; i > 0; i--)
       {
         xN[i] = xN[i - 1];
       }
       xN[0] = temp;
     }
   }

   if (yS < 0)
   {
     //for Y
     for (int i = 0; i > yS; i--)// shifting yN to left
     {
       double temp = yN[0];

       for(int i = 0; i < corrDuration - 1; i++)
       {
         yN[i] = yN[i+1];
       }
       yN[corrDuration-1] = temp;
     }
   }
   else
   {
     for (int i = 0; i < yS; i++) // shifting yN to the right
     {
       double temp = yN[corrDuration - 1]   ;
       for (int i = corrDuration - 1; i > 0; i--)
       {
         yN[i] = yN[i - 1];
       }
       yN[0] = temp;
     }
   }

   //auto xcorr
   //for x
   double autoX = 0;
   for (int i = 0; i < corrDuration; i++)
   {
     autoX = autoX + (xN[i] * xN[i]);
   }

   //for y
   double autoY = 0;
   for (int i = 0; i < corrDuration; i++)
   {
     autoY = autoY + (yN[i] * yN[i]);
   }

   double xcorr[corrDuration] = {0}; // computing crosscorrelation
   for (int z = 0; z < corrDuration; z++)
   {
     for (int i = 0; i < corrDuration; i++) // computing the inside xcorr
     {
       xcorr[z] = xcorr[z] + (xN[i] * yN[i]);
     }
     //for shifting the elements of the Y signal to the right
     double temp = yN[corrDuration - 1];
     for(int i = corrDuration - 1; i > 0; i--)
     {
       yN[i] = yN[i - 1];
     }
     yN[0] = temp;
   }

   //for computing normalized xcorr
   nxcorr = new double[corrDuration]{0};
   for (int i = 0; i < corrDuration; i++)
   {
     nxcorr[i] = xcorr[i] / (sqrt(autoX*autoY));
   }

   //shifting the final
   int tempp = 0;
   tempp  = abs(xS) - abs(yS);

   if (yDuration > xDuration)
   {
   	 shift = tempp - yDuration + 1;
   }

   else
   {
   	 shift = tempp - xDuration + 1;
   }

   for (int i = 0; i > shift; i--)
   {
     double temp1 = nxcorr[0];

     for(int a = 0; a < corrDuration - 1; a++)
     {
       nxcorr[a] = nxcorr[a + 1];
     }
     nxcorr[corrDuration-1] = temp1;
   }

   //printing
   if (corrDuration < 20)
   {
     cout << "\n**Normalized crosscorrelation values**\n";
     for (int i = 0; i < corrDuration; i++)
     {
       cout << "p_xy(" << i + shift << "): " << nxcorr[i] << endl;
     }
   }
 }

 //private:
 ifstream fileopen;

 //for first line
 stringstream inputi;
 stringstream inputd;
 stringstream inputt;
 int Istartvalue = 0;
 int endValue;
 double thirdTest;
 double Fltvalue = 0.0;
 string input;
 string extra = "";
 string dbouelextra = "";

 //for processing succeeding signal values
 vector<double> values;
 int x = 1;
 int durationValue = 0;
 double *signalvalues = new double [x];
 double succeeding;
 string eextra;
 bool durationKnown = false;
 bool floatStarter = false;
 bool noStarter = false;
 bool imported = false;
 bool exported = false;

 //for nxcorr
 int shift = 0;
 int corrDuration = 1;

 private:
 double *nxcorr = new double[corrDuration];

};


int main(int argc, char* argv[])
{
  if (argc == 4)
  {
    engg151Signal signalX;
    engg151Signal signalY;
    engg151Signal normalizedxcorr;

    signalX.importSignalFromFile(argv[1]);
    signalY.importSignalFromFile(argv[2]);
    signalX.feedback(signalX.imported, argv[1], signalX.Istartvalue, signalX.durationValue);
    signalY.feedback(signalY.imported, argv[2], signalY.Istartvalue, signalY.durationValue);

    if (signalX.imported == true && signalY.imported == true)
    {
      normalizedxcorr.compute(signalX.signalvalues, signalY.signalvalues, signalX.durationValue, signalY.durationValue, signalX.Istartvalue, signalY.Istartvalue);
      normalizedxcorr.exportSignalToFile(argv[3]);
      normalizedxcorr.feedback2(normalizedxcorr.exported, argv[3], normalizedxcorr.shift, normalizedxcorr.corrDuration);
    }

    else
    {
      cout << "Unable to process valid crosscorrelation\n";
    }
  }

  return 0;
}
