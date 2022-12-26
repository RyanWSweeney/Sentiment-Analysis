//
// Created by ryans on 8/31/2022.
//

#include "SentimentModel.h"
#include "DSString.h"
#include "DSVector.h"
#include "Tokenator.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

SentimentModel::SentimentModel(char * args[]){
    trainPath = args[1];
    testSetPath = args[2];
    testSetPathAnswers = args[3];
    classifierResults = args[4];
    accuracyResults = args[5];
}

void SentimentModel::trainModel() {
    std::ifstream f(trainPath);
    auto *temp = new char[500];
    if(f.is_open()){
        std::cout << "File opened successfully! \n \t Performing training\n";
        //ignore first line of file
        f.getline(temp,500);
        while(!f.eof()){
            //getnext line
            f.getline(temp,500);
            DSString temp2(temp);
            if(!temp2.is_empty()){
                //save sentiment as an integer
                currSent = temp2.at(0) - '0';
                //remove sentiment field from string
                temp2.cut(0,2);
                int numFieldsRmv = 0;
                for(size_t i = 0; i < temp2.getLength() && numFieldsRmv <5; ++i){
                    if(temp2.at(i)==','){
                        temp2.cut(0,i + 1);
                        numFieldsRmv++;
                        i=0;
                    }
                }
                tokenator.loadString(temp2, currSent);
            }
        }
    }else {
        cout << "Failed to open file\n";
    }
    delete[] temp;
    tokenator.sortTokens();
    //tokens can be outputted to a file using below function
//    tokenator.outputTokens();
}

void SentimentModel::evaluate() {
    std::ifstream f(testSetPath);
    std::ofstream p(classifierResults);
    auto *temp = new char[500];
    double sentiment;
    if(f.is_open()){
        std::cout << "File opened successfully! \n \t Performing evaluation of testing set\n";
        //ignore first line of file
        f.getline(temp,500);
        while(!f.eof()){
            //getnext line
            f.getline(temp,500);
            DSString temp2(temp);
            if(!temp2.is_empty()){
                //remove sentiment field from string
                DSString id(temp2.cut(0,10));
                int numFieldsRmv = 0;
                for(size_t i = 0; i < temp2.getLength() && numFieldsRmv <4; ++i){
                    if(temp2.at(i)==','){
                        //note cuts to i + 1 to also remove the comma
                        //my cut function is written so first arg is inclusive second is exclusive
                        temp2.cut(0,i + 1);
                        numFieldsRmv++;
                        i=0;
                    }
                }
                sentiment = tokenator.testSentiment(temp2);
                //this assumes that all tweets with no matching tokens are positive because it has to pick 1 of the 2
                if(sentiment >= 2){
                    sentiment = 4;
                }else if(sentiment < 2){
                    sentiment = 0;
                }else{
                    cerr << "invalid sentiment -- this error should never appear if it does there is an error in code\n";
                }
                //outputs sentiments to file
                p << sentiment;
                p <<',';
                p<<id;
                p<<"\n";
            }
        }
    }else {
        cout << "Failed to open file\n";
    }
    delete[] temp;
    p.close();
}

double SentimentModel::calcAccuracy() {
    double numCorrect = 0;
    double totaltweets = 0;
    int sentiment1, sentiment2;
    //since I never save the sentiment values to a vector I need to re-read from file
    //one way to make this program more speed efficient would be to keep this data stored in memory
    std::ifstream f(classifierResults);
    std::ifstream p(testSetPathAnswers);
    std::ofstream  l(accuracyResults);
    auto *temp = new char[20];
    auto *temp2 = new char[20];
    if(f.is_open() && p.is_open() && l.is_open()){
        cout << "File opened successfully\n\t Performing accuracy calculations\n";
        //push a newline character to file to later replace with accuracy
        l << "\n";
        //ignore first line of answer key file
        p.getline(temp, 30);
        while(!f.eof() && !p.eof()){
            f.getline(temp, 20);
            p.getline(temp2, 20);
            DSString tmp1(temp);
            DSString tmp2(temp2);
            sentiment1 = tmp1.at(0) - '0';
            sentiment2 = tmp2.at(0) - '0';
            if(tmp1.getLength() > 1 && tmp2.getLength() > 1) {
                tmp1.cut(0, 1);
                tmp2.cut(0, 1);
                tmp2.pop_back();
            }
            if(tmp1 == tmp2) {
                if (sentiment2 == sentiment1) {
                    numCorrect++;
                }else{
                    l << sentiment2 <<',' <<sentiment1 <<tmp1<<'\n';
                }
            }else{
                cout << "tweet id's do not match\n";
                cout << "tmp1: " << tmp1 << " tmp2: " << tmp2 << "\n";
            }
            totaltweets++;
        }
    }else{
        cerr <<"failed to open a file";
    }
    delete[] temp;
    delete[] temp2;
    f.close();
    p.close();
    l.close();
    //reopen file to append accuracy at top of file
    fstream q(accuracyResults);
    //truncate decimal for output
    double accuracy = numCorrect/totaltweets*100;
    cout << "Success! Accuracy: " << accuracy << '\n';
    if(q.is_open()) {
        q << std::fixed << setprecision(3) << accuracy << "         ";
        q.close();
    }else{
        cout <<"Could not open file to prepend accuracy";
    }
    return numCorrect/totaltweets;
}

SentimentModel::~SentimentModel() = default;


