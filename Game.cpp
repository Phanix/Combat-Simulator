//Battle Combat Simulator
//Version 1.0
//By Hantaro


#include<iostream>
#include<ctime>
#include<random>
using namespace std;


int main()
{
	//////////variables
	//n characters
	int nHumans = 0;
	int nSkeletons = 0;
	int TotalHumans = 0;
	int TotalSkeletons = 0;
	//atributs
	int Hlife = 50;
	int Slife = 10;
	int Humanstr = 20;
	int Skeletonstr = 5;
	
	//////random
	default_random_engine RandomGenerator(time(0));
	//atributs generator
	uniform_int_distribution<int> Hattack(0, Humanstr);
	uniform_int_distribution<int> Sattack(0, Skeletonstr);
	//sucess attack
	uniform_real_distribution<float> AttackSucess(0.0f, 1.0f);

	//Welcome
	cout << "****** Skeletons vs Humans ********\n\n";

	//input Game Stats
	cout << "Input the number of Humans : ";
	cin >> nHumans;
	TotalHumans = nHumans;
	nHumans *= Hlife;
	cout << "Input the number of Skeletons : ";
	cin >> nSkeletons;
	TotalSkeletons = nSkeletons;
	nSkeletons *= Slife;

	//start game
	cout << "Combat Start" << endl;
	while ((nSkeletons > 0) && (nHumans > 0))
	{
		if (AttackSucess(RandomGenerator) > 0.3f)
			nSkeletons -= Hattack(RandomGenerator);
		if (AttackSucess(RandomGenerator) > 0.3f)
			nHumans -= Sattack(RandomGenerator);
		
	}
	//Show battles Result
	cout << "\t*****Battle Score*****" << endl << endl;;
	cout << "**Alives**" << endl;
	cout << "Humans : " <<nHumans / Hlife << endl;
	cout << "Skeletons : " << nSkeletons  / Slife<< endl;
	cout << "\t*****Lost*****" << endl;
	cout << "Humans Dead : " << TotalHumans - (nHumans / Hlife) << endl;
	cout << "Skeletons Dead : " << TotalSkeletons - (nSkeletons / Slife) << endl;
	system("pause");
	return 0;
}
