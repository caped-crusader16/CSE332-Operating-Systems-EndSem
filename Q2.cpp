//AU1940041 Deepang Desai

#include<bits/stdc++.h>
using namespace std;

int size;

vector<pair<int, int>> arr[100000];

map<int, int> mp;

void Buddy(int mem)
{
	
	int n = ceil(log(mem) / log(2));
	
	size = n + 1;
	for(int i = 0; i <= n; i++)
		arr[i].clear();

	arr[n].push_back(make_pair(0, mem - 1));
}


void allocate(int s)
{

	int x = ceil(log(s) / log(2));
	
	if (arr[x].size() > 0)
	{
		pair<int, int> temp = arr[x][0];

		arr[x].erase(arr[x].begin());
		
		cout << "Memory successfully allocated \n" ;

		mp[temp.first] = temp.second -temp.first + 1;
	}
	else
	{
		int i;
		
		for(i = x + 1; i < size; i++)
		{
			
			if (arr[i].size() != 0)
				break;
		}

		if (i == size)
		{
			cout << "Sorry, failed to allocate memory\n";
		}
		
		else
		{
			pair<int, int> temp;
			temp = arr[i][0];

			arr[i].erase(arr[i].begin());
			i--;
			
			for(;i >= x; i--)
			{
				
				pair<int, int> pair1, pair2;
				pair1 = make_pair(temp.first,temp.first +(temp.second -temp.first) / 2);
				pair2 = make_pair(temp.first +(temp.second -temp.first + 1) / 2,temp.second);
								
				arr[i].push_back(pair1);

				arr[i].push_back(pair2);
				temp = arr[i][0];

				arr[i].erase(arr[i].begin());
			}
			
			cout << "Memory suceesfully allocated \n";
				
			mp[temp.first] = temp.second -temp.first + 1;
		}
	}
}

void deallocate(int id)
{
	
	if(mp.find(id) == mp.end())
	{
		cout << "Sorry, invalid free request\n";
		return;
	}
	
	int n = ceil(log(mp[id]) / log(2));
	
	int i, b_num, b_add;

	arr[n].push_back(make_pair(id,id + pow(2, n) - 1));
	cout << "Memory freed succesfully\n" ;

	b_num = id / mp[id];

	if (b_num % 2 != 0)
		b_add = id - pow(2, n);
	else
		b_add = id + pow(2, n);
		
	for(i = 0; i < arr[n].size(); i++)
	{
		
		if (arr[n][i].first == b_add)
		{
			
			if (b_num % 2 == 0)
			{
				arr[n + 1].push_back(make_pair(id,id + 2 * (pow(2, n) - 1)));
					
				cout << "Coalescing of buddies done succesfully\n";
					
			}
			else
			{
				arr[n + 1].push_back(make_pair(
					b_add, b_add +
					2 * (pow(2, n))));
					
				cout << "Coalescing of buddies done succesfully \n";
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
	
	Buddy(1024);
	allocate(64);
	allocate(128);
	allocate(255);
	allocate(256);
	deallocate(128);
	deallocate(16);
	deallocate(32);

	return 0;
}


