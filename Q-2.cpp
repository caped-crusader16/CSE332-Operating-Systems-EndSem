/*Krina Khakhariya
AU1940208*/

/*Question 2(b) 
Describe the Buddy’s Algorithm for Memory Allocation and
Deallocation along with an example and implement it in C or C++.*/

#include<bits/stdc++.h>
using namespace std;

// size of vector
int size;

vector<pair<int, int>> arr[100000];

map<int, int> mp;

void Buddy_mem(int s)
{
	int n = ceil(log(s) / log(2));
	
	size = n + 1;
	for(int i = 0; i <= n; i++)
		arr[i].clear();

	arr[n].push_back(make_pair(0, s - 1));
}

void allocate_space(int s)
{
	int x = ceil(log(s) / log(2));
	if (arr[x].size() > 0)
	{
		pair<int, int> temp = arr[x][0];
		arr[x].erase(arr[x].begin());
		
		cout << "Memory from " << temp.first
			<< " to " << temp.second
			<< " allocated till here" << "\n";
		mp[temp.first] = temp.second -
						temp.first + 1;
	}
	else
	{
		int i;
		for(i = x + 1; i < size; i++)
		{
			// Finding block size greater than given request
			if (arr[i].size() != 0)
				break;
		}
		// If no such block is found i.e., no memory block available
		if (i == size)
		{
			cout << "Oops! Allocated memory failed.\n";
		}
		else
		{
			pair<int, int> temp;
			temp = arr[i][0];

			// Remove first block to splitting it into halves
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
				<< " allocate" << "\n";
				
			mp[temp.first] = temp.second -
							temp.first + 1;
		}
	}
}

void deallocate_space(int id)
{
	//If address is not found as such
	if(mp.find(id) == mp.end())
	{
		cout << "Oops! Your free request is invalid\n";
		return;
	}
	
	// Searching the size of block
	int n = ceil(log(mp[id]) / log(2));
	int i, num_buddy, add_buddy;
	arr[n].push_back(make_pair(id,
							id + pow(2, n) - 1));
	cout << "Memory is getting block from " << id
		<< " to "<< id + pow(2, n) - 1
		<< " freed\n";

	// Calculate buddy number
	num_buddy = id / mp[id];

	if (num_buddy % 2 != 0)
		add_buddy = id - pow(2, n);
	else
		add_buddy = id + pow(2, n);
		
	for(i = 0; i < arr[n].size(); i++)
	{
		if (arr[n][i].first == add_buddy)
		{
			//Merging the buddies
			if (num_buddy % 2 == 0)
			{
				arr[n + 1].push_back(make_pair(id,
				id + 2 * (pow(2, n) - 1)));
					
				cout << "Coalescing of blocks starting from here "
					<< id << " and " << add_buddy
					<< " was done" << "\n";
			}
			else
			{
				arr[n + 1].push_back(make_pair(
					add_buddy, add_buddy +
					2 * (pow(2, n))));
					
				cout << "Coalescing of blocks starting at "
					<< add_buddy << " and "
					<< id << " was done" << "\n";
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
	Buddy_mem(128);
	allocate_space(16);
	allocate_space(16);
	allocate_space(16);
	allocate_space(16);
	deallocate_space(0);
	deallocate_space(9);
	deallocate_space(32);
	deallocate_space(16);

	return 0;
}


