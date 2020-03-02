/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <sstream>
#include <iostream>

string calcSum(int* sequence, int size){
	int sum[size];
	int index[size];

	for(int i = 0; i < size; i++){
	    int val = 0;
	    for(int j = i; j < size; j++){
	        val += sequence[j];
	        if(i == 0 || val < sum[j - i]){
	            sum[j - i] = val;
	            index[j - i] = i;
	        }
	    }
	}
	ostringstream oss;
	for(int i = 0; i < size; i++){
	    oss << sum[i] << "," << index[i] << ";";
	}
	return oss.str();
}

void testPerformanceCalcSum()
{
    srand(time(NULL)); //generates random seed
    int seq[1+1000];
    cout << "size; time" << endl;
    for (int size = 10; size <= 500; size += 10) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int k = 0; k < 1000; k++) {
            for (int i = 0; i <size; i++)
                seq[i]= rand() % (10 * size) + 1;
            string res = calcSum(seq, size);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(finish -

                                                                   start).count();

        cout << size << ";" << elapsed << endl;
    }
}

