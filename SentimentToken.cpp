//
// Created by ryans on 9/21/2022.
//

#include "SentimentToken.h"
#include <cstring>

SentimentToken::SentimentToken() = default;

SentimentToken::SentimentToken(const DSString& string, int sent) : DSString(string), sentiment(sent){

}

double SentimentToken::getSentiment() const {
    return sentiment;
}

void SentimentToken::setSentiment(double sentiment) {
    SentimentToken::sentiment = sentiment;
}

SentimentToken::~SentimentToken() = default;

void SentimentToken::print() const{
    std::cout << this->data;
}

//note the sentiment == and != operators do not care about sentiment only if the word matches because this is the application needed
bool SentimentToken::operator==(const SentimentToken &rhs) const {
    if(this->getLength() != rhs.getLength()){
        return false;
    }
    for(size_t i = 0; i < this->getLength(); ++i){
        if(this->data[i] != rhs.data[i]){
            return false;
        }
    }
    return true;
}

bool SentimentToken::operator!=(const SentimentToken &rhs) const {
    if(this->getLength() != rhs.getLength()){
        return true;
    }
    for(size_t i = 0; i < this->getLength(); ++i){
        if(this->data[i] != rhs.data[i]){
            return true;
        }
    }
    return false;
}

int SentimentToken::getOccurances() const {
    return occurances;
}

void SentimentToken::setOccurances(int occurances) {
    SentimentToken::occurances = occurances;
}

DSString SentimentToken::getWord() const{
    DSString str(data);
    return str;
}




