//
// Created by ryans on 9/21/2022.
//
// the tokenator class creates an object which takes in RyanStrings (tweet text), and parses into sentiment tokens
#ifndef ASSIGNMENT2_SENTIMENT_TOKENATOR_H
#define ASSIGNMENT2_SENTIMENT_TOKENATOR_H


#include "DSString.h"
#include "DSVector.h"
#include "SentimentToken.h"

class Tokenator {
private:
    int currSentiment = 1;
    DSVector<char> delims = {' ','\n',',','.','?','\"', ';', ':','#'};

    bool checkTokens(const SentimentToken &);
    static bool wayToSort(const SentimentToken &lhs, const SentimentToken &rhs);

public:
    DSVector<SentimentToken> stopwords;
    DSVector<SentimentToken> tokens;
    explicit Tokenator();
    void loadString(DSString &string, int sentiment);
    [[nodiscard]] bool has_token() const;
    SentimentToken get_next_token();
    void printit();
    void outputTokens();
    void sortTokens();
    double testSentiment(DSString &string);




};


#endif //ASSIGNMENT2_SENTIMENT_TOKENATOR_H
