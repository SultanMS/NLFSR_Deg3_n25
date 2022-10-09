/***************************************************************
* Project Name: NLFSR Optimal FeedbackFunctions of Degree3        
* Devolper:  Ibraheem Al-Hejri  (alhejri87@gmail.com)
* Date:   2022
****************************************************************/

using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdio> //printf//Streams are handled in the cstdio library as pointers to FILE objects
#include <cstdlib>//header defines several general purpose functions, including dynamic memory management,
                  //random number generation, communication with the environment, integer arithmetics,
                  //searching, sorting and converting.



FILE *fin, *fout;


class NLFSR {
public:
	NLFSR(string seed, int NLFSR_size, int para[] ); // constructor to create NLFSR with the given initial seed and tap
	string to_string();     // return a string representation of the NLFSR's current state
    bool step();          // simulate one step and return the new bit as 0 or 1. i.e. compute bm
    unsigned long int generate(); // simulate k steps and return k-bit sequance
private:
	bool reg[32];//max 128 size of the register
	int m;
	int NLFSR_para[9];
};

unsigned long int _MAX_PERIOD;

// function main begins program execution
int main()
{
	int n;
	unsigned long int period;
	unsigned long int count;
	int NLFSR_para[9];//n, type, x0, Xa, Xb, Xc, Xd, Xe;
	char Exit_1;
	string file_name, seed;

	//cout <<"Project Name: NLFSR\n\n" << endl;
	//cout <<"Press character EOF to exit the program or press another character to continue: ";
	//cin >> Exit_1;

	//while ( ( Exit_1 = cin.get()) != EOF){
	cout<<"Please enter the NLFSR size:";
		cin >> n;
		cout << endl;
     //n= 19;
		_MAX_PERIOD = pow(2.0, n) - 1;
		/*//input file setup:
		ifstream fin;
		fin.open(file_name, ios::in);
		if(fin == NULL){ cout <<"The file was not found!\n"; break;}*/
		//output file setup:
		ofstream fout;
		fout.open("output.txt", ios::out | ios::app);
		if(fout==NULL){cout <<"The output file was not found!\n";} //	break;
 		//read NLFSR parameters and compute period:
		cout << "Please wait ...\n";
		seed.clear();//str("");
		for(int i = 0; i < n; i++)
			seed +='0';
		seed[n - 1] = '1';

		NLFSR_para[0] = n;//NLFSR size
		NLFSR_para[2] = 0;//X0

		count = 0;
		NLFSR_para[1] = 1;//, n, type, X0[2], Xa[3], Xb[4], (Xc[5], Xd[6])
		for(int a = 1; a < n; a++)//Xa
		{
			NLFSR_para[3] = a;
			//for(int b = a + 1; b < n; b++)//Xb
			//{
				//NLFSR_para[4] = b;
				 for(int h = 1; h < n; h++)//Xe
					  {
						NLFSR_para[4] = h;
						  for(int f = h + 1 ; f < n; f++)//Xh
						  {
							NLFSR_para[5] = f;
				for(int c = 1; c < n; c++)//Xc
				{
					NLFSR_para[6] = c;
					for(int d = c + 1; d < n; d++)//Xd
					{
						NLFSR_para[7] = d;
						for(int e = d + 1; e < n; e++)//Xd
					    {

						NLFSR_para[8] = e;//Xf
					//	NLFSR_para[8] = 99;//Xh
						NLFSR myFLSR(seed, n, NLFSR_para);
						period = myFLSR.generate();
						count++;
						if(period == _MAX_PERIOD)
						{
							fout << period;
							fout << " (optimal)	";
							for(int i = 0; i < 8; i++)
									fout << NLFSR_para[i] << "	" ;
							fout << NLFSR_para[8] << "	" ;
							//fout << NLFSR_para[8];
							fout << endl;
							//cout <<"p = " << period << " (optimal)\n";
						}
						/*else
						{
							cout <<  count << " ( Not optimal)\n";
							cout << endl;
						}*/
					}//f

				}}//d
				}//c
			}//b
		}//a
		cout << "counter1 = " << count << endl;


		//close i/o files:
		//fin.close();
		fout.close();

		cout << "\nYou can see the output file!\n";
	//	cout <<"\nPress character EOF to exit the program or press another character to continue: ";
	//	cin >> Exit_1;
	//}//end of outer while loop
	return 0;
}//end of main function

NLFSR::NLFSR(string seed, int n, int para[])
{
	m = n;

	for(int i = 0; i < m; i++)
	{
		if(seed[i] == '1')
			reg[i] = true;
		else
			reg[i] = false;
	}
	for(int i = 0; i < 9; i++)
		NLFSR_para[i] = para[i];//contains indices

}// end of constructor

string NLFSR::to_string() //convert bool register to string
{
	string reg_content(m, '0');
	for(int i = 0; i < m; i++)
	{
		if(reg[i])
			reg_content[i] = '1';
		else reg_content[i] = '0';
	}
	return reg_content;
}

bool NLFSR::step()// this function computing feedback and shifting NLFSR register for once.
{
	bool bm;
	int fbtype, i = m-1;
	bool X0, Xa, Xf, Xh, Xc, Xd, Xe;//n, type, x0, a, b, c, d, e , h;

	X0 = reg[i];
	Xa = reg[i-NLFSR_para[3]];
	//Xb = reg[i-NLFSR_para[4]];
	Xh = reg[i-NLFSR_para[4]];
	Xf = reg[i-NLFSR_para[5]];
	Xc = reg[i-NLFSR_para[6]];
	Xd = reg[i-NLFSR_para[7]];
	Xe = reg[i-NLFSR_para[8]];
	//Xh = reg[i-NLFSR_para[8]];
	//computing bm function
	fbtype = NLFSR_para[1]; //n, type, x0, a, b, c, d, e;
	switch (fbtype)
	{
		case 1://type 1
			bm = X0^Xa^(Xh&Xf)^(Xc&Xd&Xe);//^ = XOR
			break;

		default:// catch all other numbers
			cout << "Incorrect number type entered.";
            break;
	}
	//Shifting:
	for(int i = m - 1; i > 0; i--)
	{
		reg[i] = reg[i-1];
	}
	reg[0] = bm; //reg[0] is Xn-1 while reg[m-1] = X0

return bm;
}

//generate key
unsigned long int NLFSR::generate()
{
	unsigned long int i, test_period;
	bool step_result;
	string initial_seed(to_string());
	//string reducible_case(to_string());

	i = 0;
	test_period = _MAX_PERIOD + 1;
	while(i < test_period)//true)
	{
		//cout << initial_seed << endl;
		//reducible_case = to_string();
		step_result = NLFSR::step();//call step function
		if( !initial_seed.compare(to_string()) )//if(initial_seed == to_string())
		{
			return i+1;//break;
		}
		//if(reducible_case == to_string())
		//{
		//cout << "The program is stuck in this case," << " the current seed is " << to_string() << endl;
		//	return i+1;//break;
		//}
		i++;
	}
return i+1;
}

