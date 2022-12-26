//
// Created by ryans on 8/31/2022.
//

#ifndef ASSIGNMENT_2_DONT_BE_SENTIMENTAL_SENTIMENTMODEL_H
#define ASSIGNMENT_2_DONT_BE_SENTIMENTAL_SENTIMENTMODEL_H
#include "DSVector.h"
#include "Tokenator.h"

class SentimentModel {
private:
    DSVector<SentimentToken> stopwords;
    int currSent;
    char * trainPath;
    char * testSetPath;
    char * testSetPathAnswers;
    char * classifierResults;
    char * accuracyResults;
public:

    Tokenator tokenator;

    SentimentModel();

    SentimentModel(char * x[]);
    ~SentimentModel();




    //takes in a path to training set expecting format : Sentiment,id,Date,Query,User,Tweet
    void trainModel(/*need to implement path to training set with command line args*/);

    void evaluate(/*need to implement path to testing set with command line args*/);

    double calcAccuracy();

};


#endif //ASSIGNMENT_2_DONT_BE_SENTIMENTAL_SENTIMENTMODEL_H
