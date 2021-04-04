/*
Name : Ali Kerem Yildiz
Student Id : 150170013
*/
// This file is the solution file for part 2b sorted_by_profit
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h> // for exit()
using namespace std;

class Sale
{

public:
	string country;
	string item_type;
	string order_id;
	int unit_sold;
	double profit;
	Sale(string country, string item_type, string order_id, int unit_sold, double profit);
};

Sale::Sale(string country, string item_type, string order_id, int unit_sold, double profit)
{
	this->country = country;
	this->item_type = item_type;
	this->order_id = order_id;
	this->unit_sold = unit_sold;
	this->profit = profit;
}
int partition(vector<Sale> &SaleList, int low, int high)
{
	double pivot = SaleList[high].profit;
	int i = low - 1;
	for (int j = low; j <= high - 1; j++)
	{
		if (SaleList[j].profit > pivot)
		{
			i++;
			swap(SaleList[i], SaleList[j]);
		}
	}
	swap(SaleList[i + 1], SaleList[high]);
	return i + 1;
}
void quickSort(vector<Sale> &SaleList, int low, int high)
{

	if (low < high)
	{
		int pi = partition(SaleList, low, high);
		quickSort(SaleList, low, pi - 1);
		quickSort(SaleList, pi + 1, high);
	}
}

void swap(Sale *temp_1, Sale *temp_2)
{

	Sale t = *temp_1;
	*temp_1 = *temp_2;
	*temp_2 = t;
}

int main(int argc, char **argv)
{

	ifstream file;
	file.open("sales.txt");

	if (!file)
	{
		cerr << "File cannot be opened!";
		exit(1);
	}

	int N = atoi(argv[1]); //you should read value of N from command line
	string country, type, order_id, line, header;
	int units_sold;
	double profit;
	getline(file, header); //this is the header line

	vector<Sale> SaleList;

	for (int i = 0; i < N; i++)
	{

		getline(file, country, '\t');  //country (string)
		getline(file, type, '\t');	   //item type (string)
		getline(file, order_id, '\t'); //order id (string)
		file >> units_sold;			   //units sold (integer)
		file >> profit;				   //total profit (float)
		getline(file, line, '\n');	   //this is for reading the \n character into dummy variable.
		SaleList.insert(SaleList.end(),Sale(country, type, order_id, units_sold, profit));
	}
	clock_t t;
	t = clock();
	quickSort(SaleList, 0, SaleList.size() - 1);
	t = clock() - t;
	cout << "Elapsed time of execution is : " << ((float)t) / CLOCKS_PER_SEC << " seconds"<<endl;
	ofstream myfile;
	myfile.open("sorted_by_profit.txt");
	if (!myfile)
	{
		cerr << "File cannot be opened!";
		exit(1);
	}
	myfile << "Country\tItem Type\tOrder ID\tUnits Sold\tTotal Profit\n";
	for (int iter = 0; iter < SaleList.size(); iter++)
	{
		myfile << SaleList[iter].country << "\t" << SaleList[iter].item_type << "\t" << SaleList[iter].order_id << "\t" << SaleList[iter].unit_sold << "\t" << SaleList[iter].profit << "\n";
	}


	return 0;
}
