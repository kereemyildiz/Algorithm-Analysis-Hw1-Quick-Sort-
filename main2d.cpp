/*
Name : Ali Kerem Yildiz
Student Id : 150170013
*/
// This file is the solution file for part 2d  of the homework sorting already sorted data (worst case)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h> // for exit()
using namespace std;

class Sales
{

public:
	string country;
	string item_type;
	string order_id;
	int unit_sold;
	double profit;
	Sales(string country, string item_type, string order_id, int unit_sold, double profit);
};

Sales::Sales(string country, string item_type, string order_id, int unit_sold, double profit)
{
	this->country = country;
	this->item_type = item_type;
	this->order_id = order_id;
	this->unit_sold = unit_sold;
	this->profit = profit;
}
int partition(vector<Sales> &saleList, int low, int high)
{
	string pivot = saleList[high].country; // since it is regular quick sort we pick last element as pivot
	int i = low - 1; // i denotes the index that is going to swap with the element which is less than pivot
	for (int j = low; j <= high - 1; j++)
	{
		if (saleList[j].country.compare(pivot) < 0) // by comparing current country name with pivot , we can determine which one is come first alphabetically
		{
			// since it enters this block, the element which we compare to pivot less than pivot.
			i++; 
			swap(saleList[i], saleList[j]); // since elements in index j less than (alpahabetically comes first than pivot) we make swap operation
		}
		else if (saleList[j].country.compare(pivot) == 0)// country names are same
		{
			if (saleList[j].profit > saleList[high].profit)// profit should sort by descending order
			{
				i++;
				swap(saleList[i], saleList[j]); // the same logic on line 39.
			}
		}
	}
	swap(saleList[i + 1], saleList[high]); // the elements in index i is the last element which is compared with pivot and gives less output, so swap
											// we put the pivot element near index of i so we swap element in index i+1 and pivot.
	return i + 1;
}
void quickSort(vector<Sales> &saleList, int low, int high)
{

	if (low < high) // it continues until low = high which means subproblem's size is 1. since it is already sorted we dont enter that block
	{
		int pi_index = partition(saleList, low, high); // we need to find partitioning index which give us pivot element
		quickSort(saleList, low, pi_index - 1); // pivot element is places between lesser and greater elemens of itself. So we divide before pivot and after pivot
		quickSort(saleList, pi_index + 1, high);
	}
}

void swap(Sales *temp_1, Sales *temp_2)
{

	Sales t = *temp_1;
	*temp_1 = *temp_2;
	*temp_2 = t;
}

int main(int argc, char **argv)
{

	ifstream file;
	file.open("sorted.txt");

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

	vector<Sales> saleList;

	for (int i = 0; i < N; i++)
	{

		getline(file, country, '\t');  //country (string)
		getline(file, type, '\t');	   //item type (string)
		getline(file, order_id, '\t'); //order id (string)
		file >> units_sold;			   //units sold (integer)
		file >> profit;
			   //total profit (float)
		getline(file, line, '\n');	   //this is for reading the \n character into dummy variable.
		saleList.insert(saleList.end(),Sales(country, type, order_id, units_sold, profit));
	}
	
	clock_t t;
	t = clock();
	quickSort(saleList, 0, saleList.size() - 1);
	t = clock() - t;
	cout << "Elapsed time of execution is : " << ((float)t) / CLOCKS_PER_SEC << " seconds"<<endl;
	ofstream myfile;
	myfile.open("sorted_by_sorted.txt");
	if (!myfile)
	{
		cerr << "File cannot be opened!";
		exit(1);
	}
	
	myfile << "Country\tItem Type\tOrder ID\tUnits Sold\tTotal Profit\n";
	for (int iter = 0; iter < saleList.size(); iter++)
	{
		myfile << saleList[iter].country << "\t" << saleList[iter].item_type << "\t" << saleList[iter].order_id << "\t" << saleList[iter].unit_sold << "\t" << saleList[iter].profit << endl;
	}


	return 0;
}
