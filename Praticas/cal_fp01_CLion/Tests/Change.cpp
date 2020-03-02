/*
 * Change.cpp
 */

#include <sstream>
#include "Change.h"
#include "vector"

string calcChange(int m, int numCoins, int *coinValues){
    int INF = m + 1;
    int minCoins[m + 1];
    int lastCoin[m + 1] = {0};

    minCoins[0] = 0;
    for(int k = 1; k <= m; k++)
        minCoins[k] = INF;

    for(int i = 1; i <= numCoins; i++){
        for(int k = coinValues[i - 1]; k <= m; k++){
            if(minCoins[k - coinValues[i - 1]] + 1 < minCoins[k]){
                minCoins[k] = 1 + minCoins[k - coinValues[i - 1]];
                lastCoin[k] = coinValues[i - 1];
            }
        }
    }

    if(minCoins[m] == INF)
        return "-";
    ostringstream oss;
    for(int k = m; k > 0; k -= lastCoin[k])
        oss << lastCoin[k] << ";";
    return oss.str();

}


