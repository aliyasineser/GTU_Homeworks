#include <cstdlib>
#include <iostream>

using namespace std;

// Prototypes
template <class T>
T getMax(const T arr[], int size);
template <class T>
T getSecondMax(const T arr[], int size, void* max);

int main(int argc, char** argv) {

	int a[] = { 2,6,47,1,2 ,74,65,2,93,154 };

	int x = getSecondMax(a, 10, NULL);
	cout << x << endl;

	return 0;
}

// This function designed by Hasan Men, you can check his profile at:
// https://github.com/hmenn
/*
* Recursive function that gives the object with maximum value
* Requires : Comparison overloads for type T
*/
template <class T>
T getMax(const T arr[], int size) {

	// if size < 1, need exception like IndexOutOfBound

	if (size == 1) {
		return arr[0];
	}

	--size;
	T temp = getMax(&arr[1], size);
	return arr[0]>temp ? arr[0] : temp;
}

// This function designed by Ali Yasin Eser, you can check his profile at:
// https://github.com/aliyasineser
/*
* Recursive function that gives the object with second maximum value
* If size is one gives the only object in the array
* Requires : Comparison overloads for type T
*/
template <class T>
T getSecondMax(const T arr[], int size, void* max) {

	T secondMax;
	int flag = 0; // If there is a max, flag will stay zero. 
	if (max == NULL) { // Oops, this is the first step of the recursion!
					   // Allocate space for max and assign it. Change the flag, we need to know that
					   // we are in the step that we allocated space for max.
		max = new T();
		*((T*)(max)) = getMax(arr, size);
		flag = 1;
	}
	// Size can be smaller than 1, you can use exception for that situation. Or you can change the type and 
	// return null so user can understand that he/she typed wrong or there is a problem.
	if (size == 1) { // We have only one max. If u want return an exception or return max , your choice
		if (flag == 1) delete max;
		return arr[0];
	}
	else { // You can combine the else and if parts. It is more readable for me. 
		secondMax = arr[0];
		T potential = getSecondMax(&arr[1], size - 1, max); // secondMax of array[1,...,n] except array[0]
															// Update of secondMax with comparison between array[0] and secondMax of array[1,...,n] 
		if (potential < *((T*)max) && secondMax < potential)
			secondMax = potential;
	}
	// If i'm in first step, i need to delete the allocated space. Because I'm done.
	if (flag == 1) delete max;

	return secondMax; // return the second Maximum
}
