// Aim      : To determine type of channel and also calculate the various entropies and mutual information
// Name     : Pranav Singh
// Roll No. : 304251
// Batch    : C3
//

#include "stdafx.h"  // remove if not using visual studio
#include<iostream>
#include<conio.h>
#include<math.h>
using namespace std;

int main()
{
	float chMatrix[10][10], sumRow[10], sumCol[10], pX[10], pY[10], jointMatrix[10][10], conXY[10][10], conYX[10][10], sumAll = 0, entropyX = 0, entropyY = 0, entropyYX = 0, entropyXY = 0, entropyXjY = 0, mutInfo = 0;
	int rows, columns, countNonZeroCol[10], countNonZeroRow[10];
	char matrixType;
	cout << "enter the dimensions of channel matrix";
	cin >> rows >> columns;
	bool flag1 , flag2, colflag,rowflag;
	colflag = true; rowflag = true;

	cout << "enter the channel matrix\n";
	for (int i = 0; i<10; i++)
	{
		sumRow[i] = 0;
		sumCol[i] = 0;
		countNonZeroCol[i]=0;
		countNonZeroRow[i]=0;
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<columns; j++)
		{
			cout << "(" << i + 1 << "," << j + 1 << ")";
			cin >> chMatrix[i][j];
			sumCol[j] += chMatrix[i][j];
			sumRow[i] += chMatrix[i][j];
			sumAll += chMatrix[i][j];
		} cout <<endl;
	}

	cout << "\n sum All : " << sumAll;

	cout << "\n sum Row : \n";
    for (int i = 0; i<rows; i++)		cout << sumRow[i] << "\t";


	cout << "\n sum Coloumn : \n";
	for (int i = 0; i < columns; i++)   cout << sumCol[i] << "\t";



    // check the type of channel matrix entered

	if (sumAll > 0.99 && sumAll<=1)
	{
		matrixType = 'j';
		cout << "\n made matrix type j\n";
		flag1 = false;
		flag2 = false;
	}
	else
	{
		flag1 = true;
		flag2 = true;
		for (int i = 0; i<rows; i++)
		{
			if (flag1 && (sumRow[i] != 1))
			{
				flag1 = false;
			}
		}

		for (int i = 0; i < columns; i++)
		{
			if (flag2 && (sumCol[i] != 1))
			{
				flag2 = false;
			}
		}
	}

	if (flag1)
	{
		matrixType = 'y';
	}
	else	
		if (flag2)
		{
			matrixType = 'x';
		}


	//create other channel matrices and tell user about them

	switch (matrixType)
	   {
	       case 'j':
	         {
		        cout << "\n entered matrix is a joint probability matrix P(X,Y)";
				
				cout << "\n\n Joint Probability Matrix P(X,Y) : \n";

				for (int i = 0; i < rows; i++)
					for (int j = 0; j < columns; j++)
						jointMatrix[i][j] = chMatrix[i][j];
						

				for (int i = 0; i < rows; i++)
				{   
					countNonZeroRow[i] = 0;
					pX[i] = sumRow[i];
				}

				for (int i = 0; i < columns; i++)
				{
					countNonZeroCol[i] = 0;
					pY[i] = sumCol[i];
				}



				cout << "\n Conditional Probability Matrix P(Y|X) : \n";

				for (int i = 0; i<rows; i++)
				{
					for (int j = 0; j<columns; j++)
					{
						conYX[i][j] = jointMatrix[i][j] / pX[i];
						cout << conYX[i][j] << "\t";
						if (conYX[i][j] != 0)
						{
							countNonZeroCol[j]++;
							countNonZeroRow[i]++;
						}
					} cout << endl;
				}

				if (rows == columns == 2)		cout << "\n\n and it is a binary symetric channel";
				for (int i = 0; i < columns; i++)  if (countNonZeroCol[i] != 1)  colflag = false;
				for (int i = 0; i < rows; i++)  if (countNonZeroRow[i] != 1)  rowflag = false;
				if (colflag && rowflag) cout << " \n\n and it is a noise less channel";
				else if (colflag) cout << "\n\n and it is a Lossless channel";
				else if (rowflag) cout << "\n\n and it is a Deterministic channel";

				cout << "\n Conditional Probability Matrix P(X|Y) : \n";

				for (int i = 0; i<rows; i++)
				{
					for (int j = 0; j<columns; j++)
					{
						conXY[i][j] = jointMatrix[i][j] / pY[j];
						cout << conXY[i][j] << "\t";
					} cout << endl;
				}
			
				break;
	         }
	       case 'y':
	         {
			   cout << "\n entered matrix is a conditional probability matrix P(Y|X)";				    
                
				cout << "\n Do you wish to enter P(X) to calculate entropies (Y for yes) and proceed further?\t";
				char choiceLoc;
				cin >> choiceLoc;
				if (choiceLoc == 'Y' || choiceLoc == 'y')
				{
					for (int i = 0; i < rows; i++)
					{
						cout << "P(X" << i + 1 << ") = ";
						cin >> pX[i];
					}

					for (int i = 0; i<10; i++)
					{
						sumRow[i] = 0;
						sumCol[i] = 0;
					}


					cout << "\n Joint Probability Matrix P(X,Y) : \n";

					for (int i = 0; i<rows; i++)
					{
						for (int j = 0; j<columns; j++)
						{
							jointMatrix[i][j] = chMatrix[i][j] * pX[i];
							cout << jointMatrix[i][j] << "\t";
							sumCol[j] += jointMatrix[i][j];
							sumRow[i] += jointMatrix[i][j];
						} cout << endl;
					}

					for (int i = 0; i < rows; i++)			pX[i] = sumRow[i];
					for (int i = 0; i < columns; i++)       pY[i] = sumCol[i];

                  
					cout << "\n Conditional Probability Matrix P(Y|X) : \n";

					for (int i = 0; i < rows; i++)			pX[i] = sumRow[i];
					for (int i = 0; i < columns; i++)       pY[i] = sumCol[i];

					for (int i = 0; i<rows; i++)
					{
						for (int j = 0; j<columns; j++)
						{
							conYX[i][j] = jointMatrix[i][j] / pX[i];
							cout << conYX[i][j] << "\t";
							sumCol[j] += conYX[i][j];
							sumRow[i] += conYX[i][j];
							if (conYX[i][j] != 0)
							{
								countNonZeroCol[j]++;
								countNonZeroRow[i]++;
							}
						} cout << endl;
					}

					if (rows == columns == 2)		cout << "\n\n and it is a binary symetric channel";
					for (int i = 0; i < columns; i++)  if (countNonZeroCol[i] != 1)  colflag = false;
					for (int i = 0; i < rows; i++)  if (countNonZeroRow[i] != 1)  rowflag = false;
					if (colflag && rowflag) cout << " \n\n and it is a noise less channel";
					else if (colflag) cout << "\n\n and it is a Lossless channel";
					else if (rowflag) cout << "\n\n and it is a Deterministic channel";

					cout << "\n Conditional Probability Matrix P(X|Y) : \n";


					for (int i = 0; i<rows; i++)
					{
						for (int j = 0; j<columns; j++)
						{
							conXY[i][j] = jointMatrix[i][j] / pY[j];
							cout << conXY[i][j] << "\t";
						} cout << endl;
					}

				}
				else
				{
					exit(0);
				}
		        break;
	         }
	       case 'x':
	         {
		        cout << "\n entered matrix is a conditional probability matrix P(X/Y)";

				cout << "\n Do you wish to enter P(Y) to calculate entropies ?\t";

				char choiceLoc;
				cin >> choiceLoc;
				if (choiceLoc == 'Y' || choiceLoc == 'y')
				{
					for (int i = 0; i < rows; i++)
					{
						cout << "P(Y"<<i+1<<") = ";
						cin >> pY[i];
					}

					for (int i = 0; i<10; i++)
					{
						sumRow[i] = 0;
						sumCol[i] = 0;
					}

					cout << "\n Joint Probability Matrix P(X,Y) : \n";

					for (int i = 0; i<rows; i++)
					{
						for (int j = 0; j<columns; j++)
						{
							jointMatrix[i][j] = chMatrix[i][j] * pY[j];
							sumCol[j] += jointMatrix[i][j];
							sumRow[i] += jointMatrix[i][j];
						}
					}

					for (int i = 0; i < rows; i++)		pX[i] = sumRow[i];
					for (int i = 0; i < columns; i++)	pY[i] = sumCol[i];
					

					cout << "\n Conditional Probability Matrix P(Y|X) : \n";

					for (int i = 0; i < rows; i++)			pX[i] = sumRow[i];
					for (int i = 0; i < columns; i++)       pY[i] = sumCol[i];

					for (int i = 0; i<rows; i++)
					{
						for (int j = 0; j<columns; j++)
						{
							conYX[i][j] = jointMatrix[i][j] / pX[i];
							cout << conYX[i][j] << "\t";
							sumCol[j] += conYX[i][j];
							sumRow[i] += conYX[i][j];
							if (conYX[i][j] != 0)
							{
								countNonZeroCol[j]++;
								countNonZeroRow[i]++;
							}
						} cout << endl;
					}

					if (rows == columns == 2)		cout << "\n\n and it is a binary symetric channel";
					for (int i = 0; i < columns; i++)  if (countNonZeroCol[i] != 1)  colflag = false;
					for (int i = 0; i < rows; i++)  if (countNonZeroRow[i] != 1)  rowflag = false;
					if (colflag && rowflag) cout << " \n\n and it is a noise less channel";
					else if (colflag) cout << "\n\n and it is a Lossless channel";
					else if (rowflag) cout << "\n\n and it is a Deterministic channel";


					cout << "\n Conditional Probability Matrix P(X|Y) : \n";

					for (int i = 0; i<rows; i++)
					{
						for (int j = 0; j<columns; j++)
						{
							conXY[i][j] = jointMatrix[i][j] / pY[j];
							cout << conXY[i][j] << "\t";
						} cout << endl;
					}
				}
				else
				{
					exit(0);
				}

		        break;
	         }
	       default:
	         {
		        cout << "\n entered matrix is not of any recognised type";
				exit(0);
	         }

	}


	// calculate entropies

	for (int i = 0; i < rows; i++)     // for H(X)
	{
		entropyX += (pX[i] * (log2f(1 / pX[i])));
		pX[i] = sumRow[i];
	}
	for (int i = 0; i < columns; i++)   // for H(Y)
	{
		entropyY += (pY[i] * (log2f(1 / pY[i])));
		pY[i] = sumCol[i];
	}

	

	for (int i = 0; i < rows; i++)     // for H(X,Y)
		for (int j = 0; j < columns; j++)
			if(jointMatrix[i][j]!=0) entropyXjY += (jointMatrix[i][j] * (log2f(1 / jointMatrix[i][j])));


	entropyXY = entropyXjY - entropyY;  //for H(X|Y)

	entropyYX = entropyXjY - entropyX;  // for H(Y|X)

	cout << "\nentropies : \t H(X) = " << entropyX << "\t H(Y) =" << entropyY << "\t H(X,Y) =" << entropyXjY << "\t H(Y|X) =" << entropyYX << "\t H(X|Y) =" << entropyXY;

	mutInfo = entropyX + entropyY - entropyXjY;  // for I(X,Y)

	cout << "\n I(X,Y) = " << mutInfo;

}


/*
OUTPUT :-

-------------------------example 1---------------------------

enter the dimensions of channel matrix3
3
enter the channel matrix
(1,1).8
(1,2).2
(1,3)0

(2,1)0
(2,2)1
(2,3)0

(3,1)0
(3,2).3
(3,3).7


sum All : 3
sum Row :
1       1       1
sum Coloumn :
0.8     1.5     0.7
entered matrix is a conditional probability matrix P(Y/X)
Do you wish to enter P(X) to calculate entropies (Y for yes) ? y
P(X1) = .3
P(X2) = .4
P(X3) = .3

Joint Probability Matrix P(X,Y) :
0.24    0.06    0
0       0.4     0
0       0.09    0.21

Conditional Probability Matrix P(Y|X) :
0.8     0.2     0
0       1       0
0       0.3     0.7

Conditional Probability Matrix P(X|Y) :
1       0.109091        0
0       0.727273        0
0       0.163636        1

entropies :      H(X) = 1.57095  H(Y) =1.44133   H(X,Y) =2.05192         H(Y|X) =0.480966        H(X|Y) =0.610586
I(X,Y) = 0.960365


-------------------------example 2---------------------------

enter the dimensions of channel matrix3
3
enter the channel matrix
(1,1).24
(1,2).06
(1,3)0

(2,1)0
(2,2).4
(2,3)0

(3,1)0
(3,2).09
(3,3).21


sum All : 1
sum Row :
0.3     0.4     0.3
sum Coloumn :
0.24    0.55    0.21
made matrix type j

entered matrix is a joint probability matrix P(X,Y)

Joint Probability Matrix P(X,Y) :

Conditional Probability Matrix P(Y|X) :
0.8     0.2     0
0       1       0
0       0.3     0.7

Conditional Probability Matrix P(X|Y) :
1       0.109091        0
0       0.727273        0
0       0.163636        1

entropies :      H(X) = 1.57095  H(Y) =1.44133   H(X,Y) =2.05192         H(Y|X) =0.480966        H(X|Y) =0.610586
I(X,Y) = 0.960365


---------------------------example 3--------------------------------
enter the dimensions of channel matrix3
5
enter the channel matrix
(1,1).4
(1,2).6
(1,3)0
(1,4)0
(1,5)0

(2,1)0
(2,2)0
(2,3).3
(2,4).7
(2,5)0

(3,1)0
(3,2)0
(3,3)0
(3,4)0
(3,5)1


sum All : 3
sum Row :
1       1       1
sum Coloumn :
0.4     0.6     0.3     0.7     1
entered matrix is a conditional probability matrix P(Y|X)
Do you wish to enter P(X) to calculate entropies (Y for yes) and proceed further?      y
P(X1) = .3
P(X2) = .4
P(X3) = .3

Joint Probability Matrix P(X,Y) :
0.12    0.18    0       0       0
0       0       0.12    0.28    0
0       0       0       0       0.3

Conditional Probability Matrix P(Y|X) :
0.4     0.6     0       0       0
0       0       0.3     0.7     0
0       0       0       0       1


and it is a Lossless channel
Conditional Probability Matrix P(X|Y) :
1       1       0       0       0
0       0       1       1       0
0       0       0       0       1

entropies :      H(X) = 1.57095  H(Y) =2.21475   H(X,Y) =2.21475         H(Y|X) =0.643802        H(X|Y) =0
I(X,Y) = 1.57095
*/


