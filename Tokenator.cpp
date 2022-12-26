//
// Created by ryans on 9/21/2022.
//

#include "Tokenator.h"

#include <utility>
#include <fstream>
#include "DSVector.h"
#include "DSString.h"

Tokenator::Tokenator(){

}

//this function loads a string and converts to tokens adding the tokens to its vector of tokens
void Tokenator::loadString(DSString &string, int sentiment) {
    currSentiment = sentiment;
    SentimentToken tmp;
    for(size_t i = 0; i < string.getLength(); ++i){
        for(char delim : delims) {
                if (string.at(i) == delim) {
                    SentimentToken temp(string.cut(0, i), currSentiment);
                    //remove extra spaces from tokens
                    //note this does not remove spaces from all tokens, but catches most of the spaces
                    //I suspect that some tweets have non-spaces that appear as spaces within them
                    while (temp.getLength() > 1 && temp.at(0) == ' ' ) {
                        temp.pop_front();
                    }
                    //remove other unwanted characters
                    for(size_t j = 0; j < temp.getLength(); ++j){
                        if(!isalpha(temp.at(j))){
                            temp.pop_mid(j);
                        }
                    }
                    temp.to_Lower();
                    temp.stemWord();
                    if (!checkTokens(temp)) {
                        tokens.push_back(temp);
                    }
                    //remove comma
                    string.pop_front();
                    i = 0;
                }
            }
    }
    //push back final word
    //remove '\n'
    string.pop_back();
    SentimentToken temp2(string, currSentiment);
    if(!checkTokens(temp2))
        tokens.push_back(temp2);
}

bool Tokenator::has_token() const{
    if(tokens.empty()){
        return false;
    }
    return true;
}
//returns a token from the list
SentimentToken Tokenator::get_next_token() {
    return tokens.pop_back();
}

void Tokenator::printit() {
    tokens.printit();
}
//function to print tokens to a file (primarily used for testing)
void Tokenator::outputTokens() {
ofstream f;
f.open("../data/tokens.csv");
for(SentimentToken token : tokens){
    f << token;
    f << ",";
    f << token.getSentiment();
    f<< ",";
    f << token.getOccurances();
    f << '\n';
}
f.close();
}
//checks if token is in both stopwords list, and the current list of tokens and does proper arithmetic
//also removes some edge case tokens
bool Tokenator::checkTokens(const SentimentToken &token) {
    //check for small tokens and remove  these also don't hold much sentiment
    if(token.getLength() <= 2){
        return true;
    }
    //check if word is already stored inside Tokenator and add to occurances and weighted average the sentiment
    for(size_t i = 0; i < tokens.size(); ++i){
        if(token == tokens[i]){
            tokens[i].setSentiment(((tokens[i].getSentiment() * tokens[i].getOccurances()) + currSentiment)/ (tokens[i].getOccurances() + 1));
            tokens[i].setOccurances(tokens[i].getOccurances() + 1);
            return true;
        }
    }

    return false;
}

void Tokenator::sortTokens() {
    std::sort(tokens.begin(), tokens.end(), wayToSort);
}

bool Tokenator::wayToSort(const SentimentToken &lhs, const SentimentToken &rhs) {
    return lhs.getOccurances() > rhs.getOccurances();
}

double Tokenator::testSentiment(DSString &string) {
    //initialized at 1,2 so if no tokens found sentiment will be neutral
    int numTokens=1;
    double sentiment=2;
    for(size_t i = 0; i < string.getLength(); ++i){
        for(char delim : delims) {
            if (string.at(i) == delim) {
                SentimentToken temp(string.cut(0, i), 2);
                //remove extra spaces from tokens
                //note this does not remove spaces from all tokens, but catches most of the spaces
                //I suspect that some tweets have non-spaces that appear as spaces within them
                while (temp.getLength() > 1 && temp.at(0) == ' ' ) {
                    temp.pop_front();
                }
                for(size_t j = 0; j < temp.getLength(); ++j){
                    if(!isalpha(temp.at(j))){
                        temp.pop_mid(j);
                    }
                }
                temp.to_Lower();
                temp.stemWord();
                //check if word is already stored inside Tokenator and add to occurances and weighted average the sentiment
                for(size_t i = 0; i < tokens.size(); ++i){
                    if(temp == tokens[i]){
                        if(tokens[i].getSentiment() < 2){
                            //this 1.07 may be overtraining to data set but making it less negative improved accuracy
                            sentiment += tokens[i].getSentiment();
                            //.727827
                            numTokens++;
                        }else {
                            sentiment += tokens[i].getSentiment();
                            numTokens++;
                        }
                    }
                }
                //remove comma
                string.pop_front();
                i = 0;
            }
        }
    }
    sentiment/=numTokens;
    return sentiment;
}

