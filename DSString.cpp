//
// Created by ryans on 9/15/2022.
//

#include "DSString.h"
#include <cstring>
#include "porter2_stemmer-master/porter2_stemmer.h"


DSString::DSString() {
    data = new char[1];
}

DSString::DSString(const char * ptr) {
this->len = strlen(ptr);
data = new char[len + 1];
for(size_t i = 0; i < len; ++i){
   data[i] = ptr[i];
}
data[len] = '\0';
}

DSString::DSString(const char *data, size_t len): len(len) {
    this->data = new char[len + 1];
    for(size_t i = 0; i < len; ++i){
        this->data[i] = data[i];
    }
    this->data[len] = '\0';
}

//copy constructor
DSString::DSString(const DSString & stringIn): len(stringIn.len) {
    data = new char[len + 1];
    for(size_t i = 0; i < len; ++i){
        this->data[i] = stringIn.data[i];
    }
    data[len] = '\0';
}

DSString::~DSString() {
delete[] data;
}

void DSString::print() const {
    std::cout << data << '\n';
}

DSString &DSString::operator=(const DSString & stringIn) {
    if(&stringIn != this) {
        delete[] data;
        this->len = stringIn.len;
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            data[i] = stringIn.data[i];
        }
        data[len] = '\0';
    }
    return *this;
}

DSString DSString::operator+(const DSString & stringIn) {
    size_t oldLen = len;
    this->len = this->len + stringIn.len;
    char newData[len + 1];
    for(size_t i = 0; i < oldLen; ++i){
        newData[i] = data[i];
    }
    for(size_t i = 0; i < stringIn.len; ++i){
        newData[i+oldLen] = stringIn.data[i];
    }
    newData[len] = '\0';
    delete[] data;
    data = new char[len + 1];
    for(size_t i = 0; i < len + 1; i++){
        data[i] = newData[i];
    }
    return *this;
}

bool DSString::operator==(const DSString & stringIn) const {
    if(len != stringIn.len)
        return false;
    for(size_t i = 0; i < len; ++i){
        if(data[i] != stringIn.data[i]){
            return false;
        }
    }
    return true;
}

bool DSString::operator<(const DSString & stringIn) const {
    if(stringIn.len >= len)
        return false;
    return true;
}

bool DSString::is_empty() const {
    if(len == 0)
        return true;
    return false;
}

void DSString::push_back(char in) {
    //need to initalize at len + 2 because strlen(char[] does not include null terminator)
    char newData[len + 2];
    for(size_t i = 0; i < len; ++i){
        newData[i] = data[i];
    }
    newData[len+1] = '\0';
    newData[len] = in;
    delete[] data;
    data = new char[len + 2];
    for(size_t i = 0; i < len + 2; ++i){
        data[i] = newData[i];
    }
    len++;
}

DSString DSString::operator+(const char * stringIn) {
    size_t oldLen = len;
    size_t lenIn = strlen(stringIn);
    this->len = this->len + lenIn;
    char newData[len + 1];
    for(size_t i = 0; i < len; ++i){
        newData[i] = data[i];
    }
    for(size_t i = 0; i < lenIn; ++i){
        newData[i+oldLen] = stringIn[i];
    }
    newData[len] = '\0';
    delete[] data;
    data = new char[len + 1];
    for(size_t i = 0; i < len; i++){
        data[i] = newData[i];
    }
    data[len] = '\0';
    return *this;
}

DSString DSString::operator+(char * stringIn) {
    size_t oldLen = len;
    size_t lenIn = strlen(stringIn);
    this->len = this->len + lenIn;
    char newData[len + 1];
    for(size_t i = 0; i < len; ++i){
        newData[i] = data[i];
    }
    for(size_t i = 0; i < lenIn; ++i){
        newData[i+oldLen] = stringIn[i];
    }
    newData[len] = '\0';
    delete[] data;
    data = new char[len + 1];
    for(size_t i = 0; i < len; i++){
        data[i] = newData[i];
    }
    data[len] = '\0';
    return *this;
}


void DSString::pop_back() {
    if(len < 1){
//        std::cerr << "pop_back data from string with less than 1 chars can result in unpredictable behavior so this feature is not implemented\n";
//        std::cerr << "popping from: " << data << "\n";
    }else {
        data[len - 1] = '\0';
        len--;
    }
}

size_t DSString::getLength() const{
    return len;
}

void DSString::pop_front() {
    if(len <= 1){
//        std::cerr << "pop_front data from string with less than 2 chars can result in unpredictable behavior so this feature is not implemented\n";
//        std::cerr << "popping from: " << data << "\n";
    }else {
        char newData[len];
        for (size_t i = 0; i < len - 1; ++i) {
            newData[i] = data[i + 1];
        }
        //data[imax + 1] should have been a null terminator but we will guarentee it anyways
        newData[len-1] = '\0';
        delete[] data;
        len--;
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            data[i] = newData[i];
        }
        data[len] = '\0';
    }
}

void DSString::push_front(char in) {
    char newData[len + 2];
    newData[0] = in;
    for(size_t i = 0; i < len; ++i){
        newData[i+1] = data[i];
    }
    newData[len+1] = '\0';
    delete[] data;
    data = new char[len + 2];
    for(size_t i = 0; i < len + 2; ++i){
        data[i] = newData[i];
    }
    len ++;
}

DSString DSString::cut(size_t start, size_t end) {
    //check if trying to cut beyond index
    if(end > len){
        throw std::out_of_range ("too large end");
    }
    //intialize return data
    size_t newlen = end-start;
    char returnData[newlen+1];
    for(size_t i = 0; i < newlen; ++i){
        returnData[i] = data[i + start];
    }
    returnData[newlen] = '\0';
    //generate string of returndata
    DSString returnString(returnData);

    //save remaining characters into serperate array
    char newData[len - (end - start) + 1];

    for(size_t i = 0; i < start; ++i){
        newData[i] = data[i];
    }
    for(size_t i = 0; i + end < len; ++i){
        newData[i + start] = data[i + end];
    }
    newData[len - (end - start)] = '\0';
    //delete original array and copy characters back from newdata
    delete[] data;
    len = len - (end - start);
    data = new char[len + 1];
    for(size_t i = 0; i < len; ++i){
        data[i] = newData[i];
    }
    data[len] = '\0';
    //return cut out data as string
    return returnString;
}

char DSString::at(size_t pos) {
    //todo add index check
    if(pos > len){
        throw std::out_of_range ("out of bound for .at() call");
    }
    return data[pos];
}

std::ostream &operator<<(std::ostream & os, const DSString & string) {
    for(size_t i = 0; i < string.len; ++i){
        os << string.data[i];
    }
    return os;
}

void DSString::clear() {
    data[0] = '\0';
    len = 0;
}

void DSString::stemWord() {
    //note professor said since the stemming library requires a std::string it was appropriate in this case
    std::string wordToStem;
    wordToStem = data;
    Porter2Stemmer::trim(wordToStem);
    Porter2Stemmer::stem(wordToStem);
    const char * temp = wordToStem.c_str();
    for(size_t i = 0; i < strlen(temp); ++i){
        data[i] = temp[i];
    }
    len = strlen(temp);
}

void DSString::pop_mid(size_t index) {
//check if trying to cut beyond index
    if(index >= len){
        throw std::out_of_range ("too large index");
    }
    //intialize return data
    //generate string of returndata

    //save remaining characters into serperate array
    auto * newData = new char[len];

    for(size_t i = 0; i < index; ++i){
        newData[i] = data[i];
    }
    for(size_t i = index + 1; i < len; ++i){
        newData[i - 1] = data[i];
    }
    newData[len-1] = '\0';
    //delete original array and copy characters back from newdata
    delete[] data;
    len--;
    data = new char[len + 1];
    for(size_t i = 0; i < len; ++i){
        data[i] = newData[i];
    }
    data[len] = '\0';
    delete[] newData;
}

void DSString::to_Lower() {
    for(size_t i = 0; i < len;++i){
        data[i] = tolower(data[i]);
    }
}

const char *DSString::c_str() const {
    return data;
}
