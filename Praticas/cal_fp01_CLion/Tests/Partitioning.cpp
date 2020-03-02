/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
    if(k == 1 || k == n){
        return 1;
    }
    else{
        return s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
    }
}

int s_dynamic(int n,int k)
{
	int len = n - k + 1;
	int values[len];

	for(int i = 0; i < len; i++){
	    values[i] = 1;
	}

	for(int i = 2; i <= k; i++){
	    for(int j = 1; j < len; j++){
	        values[j] += i * values[j - 1];
	    }
	}
	return values[len - 1];
}


int b_recursive(int n)
{
    int sum = 0;
    for(int k = 1; k <= n; k++){
        sum += s_recursive(n, k);
    }
    return sum;
}

int b_dynamic(int n)
{
	int values[n + 1];

	for(int i = 1; i <= n; i++){
	    values[i] = 1;
	    for(int k = i - 1; k > 1; k--){
	        values[k] = values[k - 1] + k * values[k];
	    }
	}

	int sum = 0;
	for(int k = 1; k <= n; k++){
	    sum += values[k];
	}
	return sum;
}


