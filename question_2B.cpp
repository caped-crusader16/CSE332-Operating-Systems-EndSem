#include<bits/stdc++.h>
using namespace std;

int size;


vector<pair<int, int>> arr[100000];


map<int, int> mp;

void Buddy(int s)
{
	
	int n = ceil(log(s) / log(2));
	
	size = n + 1;
	for(int i = 0; i <= n; i++)
		arr[i].clear();

	arr[n].push_back(make_pair(0, s - 1));
}

void Allocate(int s)
{
	

	int x = ceil(log(s) / log(2));
	
	// Block available
	if (arr[x].size() > 0)
	{
		pair<int, int> temp = arr[x][0];


		arr[x].erase(arr[x].begin());
		
		cout << "Memory from " << temp.first
			<< " to " << temp.second
			<< " Allocated" << "\n";

	
		mp[temp.first] = temp.second -
						temp.first + 1;
	}
	else
	{
		int i;

		for(i = x + 1; i < size; i++)
		{
			
			// Find block size greater
			// than request
			if (arr[i].size() != 0)
				break;
		}


		if (i == size)
		{
			cout << "Sorry, failed to Allocate memory\n";
		}
		
		// If found
		else
		{
			pair<int, int> temp;
			temp = arr[i][0];

	
			arr[i].erase(arr[i].begin());
			i--;
			
			for(;i >= x; i--)
			{

				pair<int, int> pair1, pair2;
				pair1 = make_pair(temp.first,
								temp.first +
								(temp.second -
								temp.first) / 2);
				pair2 = make_pair(temp.first +
								(temp.second -
								temp.first + 1) / 2,
								temp.second);
								
				arr[i].push_back(pair1);

		
				arr[i].push_back(pair2);
				temp = arr[i][0];

			
				arr[i].erase(arr[i].begin());
			}
			
			cout << "Memory from " << temp.first
				<< " to " << temp.second
				<< " Allocate" << "\n";
				
			mp[temp.first] = temp.second -
							temp.first + 1;
		}
	}
}

void Deallocate(int id)
{
	

	if(mp.find(id) == mp.end())
	{
		cout << "Sorry, the command cant be executed due to invalid request\n";
		return;
	}
	

	int n = ceil(log(mp[id]) / log(2));
	
	int i, buddyNum, buddyAddress;


	arr[n].push_back(make_pair(id,
							id + pow(2, n) - 1));
	cout << "Memory block from " << id
		<< " to "<< id + pow(2, n) - 1
		<< " freed\n";


	buddyNum = id / mp[id];

	if (buddyNum % 2 != 0)
		buddyAddress = id - pow(2, n);
	else
		buddyAddress = id + pow(2, n);
		

	for(i = 0; i < arr[n].size(); i++)
	{
		
	
		if (arr[n][i].first == buddyAddress)
		{
			
		
			if (buddyNum % 2 == 0)
			{
				arr[n + 1].push_back(make_pair(id,
				id + 2 * (pow(2, n) - 1)));
					
				cout << "Joining of the blocks starting at "
					<< id << " and " << buddyAddress
					<< " was done by Varun" << "\n";
			}
			else
			{
				arr[n + 1].push_back(make_pair(
					buddyAddress, buddyAddress +
					2 * (pow(2, n))));
					
				cout << "Joining of blocks starting at "
					<< buddyAddress << " and "
					<< id << " was done by Varun" << "\n";
			}
			arr[n].erase(arr[n].begin() + i);
			arr[n].erase(arr[n].begin() +
			arr[n].size() - 1);
			break;
		}
	}


	mp.erase(id);
}

int main()
{
	Buddy(128);
	Allocate(16);
	Allocate(32);
	Allocate(32);
	Deallocate(0);
	Deallocate(9);
	Deallocate(32);
	Deallocate(16);

	return 0;
}
