#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void print_arr(vector<int>& arr, int first, int last)
{
	for (int i = first; i <= last; i++)
	{
		string if_eol = (i == last) ? "\n" : ", ";

		cout << arr[i] << if_eol;
	}
}

void func(vector<int>& arr, int first, int last)
{
    int m = 0;
    int k = first;

    while (k < last)
    {
        if (arr[k] > arr [k+1])
        {
            // swap arr[k] and arr[k+1]
            // as a result, odd-indexed values are greater ones in the pairs
            int temp = arr[k];
            arr[k] = arr[k+1];
            arr[k+1] = temp;
        }
        k += 2;
    }

    k = first + 1;
    vector<int> tempArr;

    while (k <= last)
    {
        // copy the odd-indexed values to tempArr
        tempArr.push_back(arr[k]);
        m += 1;
        k += 2;
    }

    int x = first;
    k = first;

    while (k <= last)
    {
        // copy the even-indexed values to the first half of the arr
        arr[x] = arr[k];
        x += 1;
        k += 2;
    }

    k = 0;

    while (k < m)
    {
        // copy the values from tempArr to the second half of the arr
        arr[x] = tempArr[k];
        x += 1;
        k += 1;
    }
}

void merge(vector<int>& arr, int first, int mid, int smid, int last)
{
    int i = first;
    int j = smid;   // smid is for mid+1
    int k = 0;
    vector<int> temp;

    while (i <= mid && j <= last)
    {
        if (arr[i] < arr[j])
        {
            temp.push_back(arr[i++]);
            k += 1;
        }
        else
        {
            temp.push_back(arr[j++]);
            k += 1;
        }
    }

    while (i <= mid)
    {
        temp.push_back(arr[i++]); 
        k += 1;
    }

    while (j <= last)
    {
        temp.push_back(arr[j++]);
        k += 1;
    }
    
    i = first;
    j = 0;

    while (i <= last)
    {
        arr[i++] = temp[j++];
    }
    
}

int getMinMaxIndex(vector<int>&arr,int first, int last, bool isMin)
{
    if (last <= first)
    {
        return last;
    }
    
    int mid = (first + last) / 2;
    int a = getMinMaxIndex(arr, first,mid, isMin);
    int b = getMinMaxIndex(arr, mid+1, last, isMin);
    if((isMin && arr[a] < arr[b])||(!isMin && arr[a] > arr[b]))
    {
        return a;
    }
    else
    {
        return b;
    }
}

void min_max_sort(vector<int>& arr, int first, int last)
{
    for(int i = first, j = last; i < j; i++, j--) // iterative approach
    {
        int min_index = getMinMaxIndex(arr,i,j,true); // get min index
        int max_index = getMinMaxIndex(arr,i,j,false); // get max index

        cout << "Min: " << arr[min_index] << " Max: " << arr[max_index] << endl;

        // swap min and first
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
        
        temp = arr[max_index];
        arr[max_index] = arr[j];
        arr[j] = temp;

    }

}



void ems_sort(vector<int>& arr, int first, int last)
{
    int n = last - first + 1;
    if (n <= 1) 
    {
        return;
    }
    else
    {

        print_arr(arr, first, last);
        func(arr, first, last);
        int mid = (first + last) / 2;

        cout << "Min_max unsorted: ";
        print_arr(arr, first, mid);
        min_max_sort(arr, first, mid);
        cout << "Min_max sorted: ";
        print_arr(arr, first,mid);


        ems_sort(arr, mid+1, last);
        merge(arr, first, mid, mid+1,last);
    }
}

int main(int argc, char *argv[])
{

	vector<int> all_values;


	try {
		
		string filename = argv[1];

		ifstream myfile(filename);

		
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				int number = stoi(line);
				all_values.push_back(number);
			}
            
			ems_sort(all_values, 0, all_values.size() - 1);
			print_arr(all_values, 0, all_values.size() - 1);
		}
		else
		{
			cout << "File is not available." << endl;
			throw;
		}

	}
	catch (const ifstream::failure& e)
	{
		cerr << "Exception opening the file!" << endl;
		return -1;
	}
	catch (...)
	{
		cerr << "Something's wrong!" << endl;
		return -1;
    }
	return 0;
}