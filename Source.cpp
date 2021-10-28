#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

int main() {
	//starting material
	int numOfHumans, numOfSkeletons, diceRoll;
	bool leave = 0;

	std::default_random_engine decaDice(time(NULL));
	std::uniform_int_distribution<int> rollDice(1, 10);
	
	struct humans {
		int health = 100;
		int damage = 20;
		int luckfactor = 5;
	};

	struct skeletons {
		int health = 50;
		int damage = 30;
		int luckfactor = 2;
	};

	std::vector<humans> humanArmy;
	std::vector<skeletons> skeletonArmy;

	//game loop
	while (!leave) {

		int j = 0; //keeps count of fights

		//introduction, setting number of trooops
		cout << "how many Humans do you want to pick, king\n";
		cin >> numOfHumans;

		cout << "how many Skeletons do you want in opposing team, king\n";
		cin >> numOfSkeletons;

		//filling the vectors 
		for (int i = 0; i < numOfHumans; i++)
		{
			humans human;
			humanArmy.push_back(human);
		}

		for (int i = 0; i < numOfSkeletons; i++)
		{
			skeletons skeleton;
			skeletonArmy.push_back(skeleton);
		}

		cout << "***              BATTLE STARTS!              ***\n\n";

		//game mechanics
		//instead of moving through the vector, we're making the vector elements shift and only using the 1st element 
		while (!skeletonArmy.empty() && !humanArmy.empty())
		{
			cout << "***              Fight " << j + 1 << " Start !              ***\n";

			humans hPlayer = humanArmy[0]; //the human participating
			skeletons sPlayer = skeletonArmy[0]; //the skeleton participating

			while (sPlayer.health > 0 && hPlayer.health > 0) {

				diceRoll = rollDice(decaDice);//chance of hitting
				//human has luckFactor = 5 , so if we roll a 6, he attakcs

				if (diceRoll > hPlayer.luckfactor) {
					//human attacks skeleton
					sPlayer.health = sPlayer.health - hPlayer.damage;
					cout << "Mr.Human did " << hPlayer.damage << " damage to Mr.Sticks\n";
				}

				if (sPlayer.luckfactor < diceRoll) {
					//skeleton attacks human
					hPlayer.health = hPlayer.health - sPlayer.damage;
					cout << "Mr.Sticks " << sPlayer.damage << " damage to Mr.Human\n";
				}

				if(diceRoll < hPlayer.luckfactor && diceRoll < sPlayer.luckfactor) {
					//nobody was able to attack
					cout << "Nobody landed a hit\n";
				}
			}

			if (sPlayer.health <= 0) {
				//human won
				cout << "Mr.Human won !\n";

				//shifitng each elemnt back by one and eliminating the last element
				for (int l = 0; l < skeletonArmy.size() - 1; l++)
				{
					skeletonArmy[l] = skeletonArmy[l + 1];
				}
				skeletonArmy.pop_back();


			}
			else if (hPlayer.health <= 0) {
				//skeleton won
				cout << "Mr.Sticks has beaten Mr.Human\n";

				//shifitng each elemnt back be one and eliminating the last element
				for (int k = 0; k < humanArmy.size() - 1; k++)
				{
					humanArmy[k] = humanArmy[k + 1];
				}
				humanArmy.pop_back();
			}
			else {
				//error mssg, cin just to stop the code
				cout << "error in code bruh, koyi bhi nahi mara\n";
				cin >> numOfHumans;
			}

			j++;
			cout << "\n\n";
		}

		cout << "***              Battle Over !!              ***\n\n";

		if (skeletonArmy.size() == 0) {
			cout << "***              humans HAVE WON !!!              ***\n";
			cout << "Number of Humans left : " << humanArmy.size() << endl;
		}
		else {
			cout << "***              the skeletons have won!!!              ***\n";
			cout << "number of Skeletons left: " << skeletonArmy.size() << endl;
		}

		cout << "Please input 1 or true to leave, and 0 or false to simulate another battle";
		cin >> leave;

		if (!leave) {
			skeletonArmy.clear();
			humanArmy.clear();
		}
	}
}
