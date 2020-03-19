// TD1_Tri.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<chrono>
#include <algorithm>

void display_vector(const std::vector<int>& to_display);

std::vector<int> bubble_sort(std::vector<int> to_sort);
std::vector<int> bubble_sort_optimized(std::vector<int> to_sort);
std::vector<int> selection_sort(std::vector<int> to_sort);
std::vector<int> insertion_sort(std::vector<int> to_sort);
std::vector<int> merge_sort(const std::vector<int>& to_sort);
void quick_sort_rec(std::vector<int>& to_sort, int start, int end);
std::vector<int> quick_sort(std::vector<int> to_sort);
int ind_min(const std::vector<int>& v, const int& i);
int partition(std::vector<int>& v, int start, int end);
std::vector<int> merge(const std::vector<int>& v1, const std::vector<int>& v2);
std::vector<int> get_from_to(const std::vector<int>& v, std::vector<int>::size_type start, std::vector<int>::size_type end);
std::vector<int> create_rand_vector(int size, time_t seed);

bool vectors_are_equal(std::vector<int> sorted, std::vector<int> control)
{
	if (sorted.size() != control.size())
	{
		return false;
	}

	for (int i = 0; i < control.size(); i++)
	{
		if (sorted[i] != control[i])
		{
			return false;
		}
	}

	return true;
}

template<typename Lambda>
void testing(int nb_test, std::vector<int> control, std::vector<int> to_sort, std::string function_name, Lambda function)
{
	std::vector<int> vector_sorted;

	double total_time = 0;

	for (auto k = 0; k < nb_test; ++k)
	{
		auto start = std::chrono::high_resolution_clock::now();
		vector_sorted = function(to_sort);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_elapsed = finish - start;
		auto duration = time_elapsed.count();
		total_time += duration;
	}
	std::cout << function_name << " Test " << ((vectors_are_equal(vector_sorted, control)) ? "Passed" : "Failed") << "\n";
	std::cout << "Elapsed time on average for the " << function_name << " : " << total_time / 100 << '\n';
}

int main()
{
	time_t seed = time(NULL);
	std::cout << "Seed used to generate the random vector : " << seed << '\n';

	int vector_size = 1;

	do {
		std::cout << "Enter the size of testing vector : ";
		std::cin >> vector_size;
		std::cout << '\n';
	} while (vector_size < 1);

	std::vector<int> vector_to_sort;
	vector_to_sort = create_rand_vector(vector_size, seed); //Create a random vector with a size of 1000

	std::vector<int> control(vector_to_sort);
	std::sort(control.begin(), control.end());

	int nb_test = 1;

	do {
		std::cout << "Enter the number of test for each sorting algorithm : ";
		std::cin >> nb_test;
		std::cout << '\n';
	} while (nb_test < 1);

	testing(nb_test, control, vector_to_sort, "Bubble sort", bubble_sort);
	testing(nb_test, control, vector_to_sort, "Optimized bubble sort", bubble_sort_optimized);
	testing(nb_test, control, vector_to_sort, "Selection sort", selection_sort);
	testing(nb_test, control, vector_to_sort, "Insertion sort", insertion_sort);
	testing(nb_test, control, vector_to_sort, "Merge sort", merge_sort);
	testing(nb_test, control, vector_to_sort, "Quick sort", quick_sort);
}

std::vector<int> bubble_sort(std::vector<int> to_sort)
{
	//For the i-iteration we loop the n-(i+1) value and swap if two following value are not sorted
	std::vector<int>::size_type size = to_sort.size();
	for (auto i = size - 1; i > 0; --i)
	{
		for (auto k = 0; k < i; ++k)
		{
			if (to_sort[k] > to_sort[k + 1])
			{
				int value = to_sort[k];
				to_sort[k] = to_sort[k + 1];
				to_sort[k + 1] = value;
			}
		}
	}
	return to_sort; //Time complexity : O(n^2) where n is the size of the vector in any case
}

std::vector<int> bubble_sort_optimized(std::vector<int> to_sort)
{
	std::vector<int>::size_type size = to_sort.size();
	auto i = 1;
	bool sorted = false;
	while (i < size && !sorted)
	{
		sorted = true;
		for (auto k = 0; k < size - i; ++k)
		{
			if (to_sort[k] > to_sort[k + 1])
			{
				int value = to_sort[k];
				to_sort[k] = to_sort[k + 1];
				to_sort[k + 1] = value;
				sorted = false;
			}
		}
		++i;
	}
	return to_sort; //Time complexity : O(n^2) where n is the size of the vector in the worse case, in the best case O(n)
}

std::vector<int> selection_sort(std::vector<int> to_sort)
{
	//For the i-iteration we find the index superior or egal to i of the minimal value in the vector and we put it in at the i-place
	std::vector<int>::size_type size = to_sort.size();
	for (auto i = 0; i < size; ++i)
	{
		int ind_swap = ind_min(to_sort, i);
		int temp = to_sort[i];
		to_sort[i] = to_sort[ind_swap];
		to_sort[ind_swap] = temp;
	}
	return to_sort; //Time complexity : O(n^2) where n is the size of the vector in the worst case, in the best case O(n)
}

std::vector<int> insertion_sort(std::vector<int> to_sort)
{
	//For the i-iteration we suppose the vector to be sort for the i-1 first value we insert the i-value into the i-1 value to keep it sort
	std::vector<int>::size_type size = to_sort.size();
	for (auto i = 1; i < size; ++i)
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
	return to_sort; //Time complexity : O(n^2) where n is the size of the vector in the worst case, in the best case O(n)
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

std::vector<int> merge_sort(const std::vector<int>& to_sort)
{
	if (to_sort.size() <= 1)
	{
		return to_sort;
	}
	else
	{
		std::vector<int>::size_type size = to_sort.size();
		std::vector<int>::size_type mid = size / 2;
		std::vector<int> left;
		std::vector<int> right;
		left.reserve(mid);
		right.reserve(size - mid);

		left = get_from_to(to_sort, (std::vector<int>::size_type) 0, mid);
		right = get_from_to(to_sort, mid, size);

		left = merge_sort(left);
		right = merge_sort(right);

		return merge(left, right);
	}
	//Time complexity : O(n*log(n)) where n is the size of the vector
}

std::vector<int> merge(const std::vector<int>& v1, const std::vector<int>& v2)
{
	std::vector<int>::size_type n1 = v1.size();
	std::vector<int>::size_type n2 = v2.size();
	auto i1 = 0;
	auto i2 = 0;

	std::vector<int> merged;

	while (i1 < n1 && i2 < n2)
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

std::vector<int> get_from_to(const std::vector<int>& v, std::vector<int>::size_type start, std::vector<int>::size_type end)
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

std::vector<int> quick_sort(std::vector<int> to_sort)
{
	quick_sort_rec(to_sort, 0, to_sort.size());
	return to_sort;
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
			++p;
		}
	}
	return p;
}

std::vector<int> create_rand_vector(int size, time_t seed)
{
	srand(seed);
	std::vector<int> random_vector;
	for (auto i = 0; i < size; ++i)
	{
		random_vector.push_back(rand() % 1000 + 1);
	}
	return random_vector;
}

void display_vector(const std::vector<int>& to_display)
{
	for (unsigned int i = 0; i < to_display.size() - 1; ++i)
	{
		std::cout << to_display[i] << ", ";
	}
	std::cout << to_display[to_display.size() - 1] << '\n';
}