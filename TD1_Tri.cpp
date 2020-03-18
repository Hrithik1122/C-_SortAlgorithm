// TD1_Tri.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <iostream>
#include <vector>

void display_vector(const std::vector<int>& to_display);

void bubble_sort(std::vector<int>& to_sort);
void bubble_sort_optimized(std::vector<int>& to_sort);
void selection_sort(std::vector<int>& to_sort);
void insertion_sort(std::vector<int>& to_sort);
std::vector<int> merge_sort(std::vector<int>& to_sort);
void quick_sort_rec(std::vector<int>& to_sort, int start, int end);
inline void quick_sort(std::vector<int>& to_sort);
int ind_min(const std::vector<int>& v, const int& i);
int partition(std::vector<int>& v, int start, int end);
std::vector<int> merge(std::vector<int>& v1, std::vector<int>& v2);
std::vector<int> get_from_to(std::vector<int>& v, unsigned int start, unsigned int end);

int main()
{
	std::vector<int> vector_to_sort = { -5,2,4,1,8,3,8,9,1,10 };
	std::vector<int> sorted_vector;

	quick_sort(vector_to_sort);

	display_vector(vector_to_sort);
}


void bubble_sort(std::vector<int>& to_sort)
{
	//For the i-iteration we loop the n-(i+1) value and swap if two following value are not sorted
	for (unsigned int i = 1; i < to_sort.size(); ++i)
	{
		for (unsigned int k = 0; k < to_sort.size() - i; ++k)
		{
			if (to_sort[k] > to_sort[k + 1])
			{
				int value = to_sort[k];
				to_sort[k] = to_sort[k + 1];
				to_sort[k + 1] = value;
			}
		}
	}
	//Time complexity : O(n^2) where n is the size of the vector in any case
}


void bubble_sort_optimized(std::vector<int>& to_sort)
{
	unsigned int i = 1;
	bool sorted = false;
	while (i < to_sort.size() && !sorted)
	{
		sorted = true;
		for (unsigned int k = 0; k < to_sort.size() - i; ++k)
		{

			if (to_sort[k] > to_sort[k + 1])
			{
				int value = to_sort[k];
				to_sort[k] = to_sort[k + 1];
				to_sort[k + 1] = value;
				sorted = false;
			}
		}
	}
	//Time complexity : O(n^2) where n is the size of the vector in the worse case, in the best case O(n)
}



void selection_sort(std::vector<int>& to_sort)
{
	//For the i-iteration we find the index superior or egal to i of the minimal value in the vector and we put it in at the i-place
	for (unsigned int i = 0; i < to_sort.size(); ++i)
	{
		int ind_swap = ind_min(to_sort, i);
		int temp = to_sort[i];
		to_sort[i] = to_sort[ind_swap];
		to_sort[ind_swap] = temp;
	}
	//Time complexity : O(n^2) where n is the size of the vector in the worst case, in the best case O(n)
}


void insertion_sort(std::vector<int>& to_sort)
{
	//For the i-iteration we suppose the vector to be sort for the i-1 first value we insert the i-value into the i-1 value to keep it sort
	for (unsigned int i = 1; i < to_sort.size(); ++i)
	{
		int value = to_sort[i];
		int k = i;
		while (k > 0 && to_sort[k - 1] > value)
		{
			to_sort[k] = to_sort[k - 1];
			k--;
		}
		to_sort[k] = value;

	}
	//Time complexity : O(n^2) where n is the size of the vector in the worst case, in the best case O(n)
}

int ind_min(const std::vector<int>& v, const int& i)
{
	int min = v[i];
	int ind_min = i;

	for (unsigned int k = i + 1; k < v.size(); ++k)
	{
		if (v[k] < min)
		{
			min = v[k];
			ind_min = k;
		}
	}

	return ind_min;
}



std::vector<int> merge_sort(std::vector<int>& to_sort)
{
	if (to_sort.size() <= 1)
	{
		return to_sort;
	}
	else
	{
		unsigned int mid = to_sort.size() / 2;
		std::vector<int> left;
		std::vector<int> right;
		left.reserve(mid);
		right.reserve(to_sort.size() - mid);
		
		left = get_from_to(to_sort, 0, mid);
		right = get_from_to(to_sort, mid, (unsigned int) to_sort.size());

		left = merge_sort(left);
		right = merge_sort(right);

		return merge(left, right);
	}
	//Time complexity : O(n*ln(n)) where n is the size of the vector
}

std::vector<int> merge(std::vector<int>& v1, std::vector<int>& v2)
{
	unsigned int n1 = v1.size();
	unsigned int n2 = v2.size();
	unsigned int i1 = 0;
	unsigned int i2 = 0;

	std::vector<int> merged;

	while (i1 < n1 and i2 < n2)
	{
		if (v1[i1] < v2[i2])
		{
			merged.push_back(v1[i1]);
			++i1;
		}
		else
		{
			merged.push_back(v2[i2]);
			++i2;
		}
	}

	while (i1 < n1)
	{
		merged.push_back(v1[i1]);
		++i1;
	}
	while (i2 < n2)
	{
		merged.push_back(v2[i2]);
		++i2;
	}
	return merged;
}

std::vector<int> get_from_to(std::vector<int>& v, unsigned int start, unsigned int end)
{

	if (start == end)
	{
		std::cout << "get_from_to ERROR start index = end index";
		return std::vector<int>();
	}
	std::vector<int> extrated;
	extrated.reserve(end - start - 1);
	for (unsigned int k = start; k < end; ++k)
	{
		extrated.push_back(v[k]);
	}
	return extrated;
}


void quick_sort_rec(std::vector<int>& to_sort, int start, int end)
{
	if (start == end)
	{
		return;
	}
	else
	{
		int p = partition(to_sort, start, end);
		quick_sort_rec(to_sort, start, p);
		quick_sort_rec(to_sort, p + 1, end);
	}
}

inline void quick_sort(std::vector<int>& to_sort)
{
	quick_sort_rec(to_sort, 0, to_sort.size());
}

int partition(std::vector<int>& v, int start, int end)
{
	int value = v[start];
	int p = start;
	for (int k = start + 1; k < end; ++k)
	{
		if (v[k] < value)
		{
			v[p] = v[k];
			v[k] = v[p + 1];
			v[p + 1] = value;
		}
	}
	return p;
}


void display_vector(const std::vector<int>& to_display)
{
	for (unsigned int i = 0; i < to_display.size() -1 ; ++i)
	{
		std::cout << to_display[i] << ", ";
	}
	std::cout << to_display[to_display.size() - 1] << '\n';
}