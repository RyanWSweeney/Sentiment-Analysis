#include <iostream>
#include <algorithm>

#include "SentimentModel.h"
#include "DSString.h"
#include "Tokenator.h"
#include  <cstring>

using namespace std;

int main(int argC, char * argV[])
{
    if(argC != 6){
        cout << "invalid number of arguments" << "\n";
    }else{
        SentimentModel model1(argV);
        model1.trainModel();
        model1.evaluate();
        model1.calcAccuracy();
    }
    return 0;
}
