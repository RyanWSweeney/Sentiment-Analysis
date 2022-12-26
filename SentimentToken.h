//
// Created by ryans on 9/21/2022.
//

#ifndef ASSIGNMENT2_SENTIMENT_SENTIMENTTOKEN_H
#define ASSIGNMENT2_SENTIMENT_SENTIMENTTOKEN_H


#include "DSString.h"
#include "Tokenator.h"

class SentimentToken : public DSString{
private:
    double sentiment = 2;
    int occurances = 1;
public:
    SentimentToken();
    explicit SentimentToken(const DSString& string, int sent);
    double getSentiment() const;
    void setSentiment(double sentiment);

    int getOccurances() const;

    void setOccurances(int occurances);

    DSString getWord() const;

    void print() const;

    bool operator!=(const SentimentToken &rhs) const;

    ~SentimentToken();

    bool operator==(const SentimentToken &rhs) const;

};


#endif //ASSIGNMENT2_SENTIMENT_SENTIMENTTOKEN_H
