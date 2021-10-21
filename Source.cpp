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
		cout << "how many filthy blocks of meat do you want to pick, king\n";
		cin >> numOfHumans;

		cout << "how many dissapointing assortment of bones do you want in opposing team, king\n";
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
					cout << "filthy piece of meat did " << hPlayer.damage << " damage to Mr.Sticks\n";
				}

				if (sPlayer.luckfactor < diceRoll) {
					//skeleton attacks human
					hPlayer.health = hPlayer.health - sPlayer.damage;
					cout << "Mr.Sticks " << sPlayer.damage << " damage to filthy piece of meat\n";
				}

				if(diceRoll < hPlayer.luckfactor && diceRoll < sPlayer.luckfactor) {
					//nobody was able to attack
					cout << " you god damn dissapointments, Can you not even hit each other, are you in love? do you wanna fuck each other? fucking fight already!\n";
				}
			}

			if (sPlayer.health <= 0) {
				//human won
				cout << " Professional retarded piece of meat suprisingly won !\n";

				//shifitng each elemnt back be one and eliminating the last element
				for (int l = 0; l < skeletonArmy.size() - 1; l++)
				{
					skeletonArmy[l] = skeletonArmy[l + 1];
				}
				skeletonArmy.pop_back();
			}
			else if (hPlayer.health <= 0) {
				//skeleton won
				cout << " dissapointing assortment of bones has suprisingly beaten filthy bag of meat, making Mr.Sticks a bit less dissapointing\n";

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
			cout << "***              the retarded pieces of meat HAVE WON !!!              ***\n";
			cout << "Number of Professional retards left : " << humanArmy.size() << endl;
		}
		else {
			cout << "***              the dissapointing assortemnt of bones have won!!!              ***\n";
			cout << "number of Hardy dildoes left: " << skeletonArmy.size() << endl;
		}

		cout << "wanna run away from the battlefield and cry in your bed you pathetic loser of a king ?\n";
		cout << " yes i am fucking loser = 1, nope, this man's gonna some more blood to quench his thirst = 0\n";
		cin >> leave;

		if (!leave) {
			skeletonArmy.clear();
			humanArmy.clear();
		}
	}
}
