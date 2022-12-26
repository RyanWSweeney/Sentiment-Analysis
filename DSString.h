//
// Created by ryans on 9/15/2022.
//

#ifndef ASSIGNMENT2_SENTIMENT_DSSTRING_H
#define ASSIGNMENT2_SENTIMENT_DSSTRING_H

#include <iostream>

class DSString
{

private:
    // a pointer to a character array containing the string
    size_t len;      // the length of the string

protected:
    char *data;
public:
    /**
     * Make sure you implement the rule of 3 and use proper memory management.
     * To help you get started, you can implement the following:
     **/

    DSString();

    explicit DSString(const char *);

    DSString(const char *data, size_t len);
    // constructor that converts a cstring

    // rule of 3
    DSString(const DSString &);  // copy constructor
    ~DSString();  // destructor
    DSString &operator=(const DSString &);

    // you can also implement the move versions for the big 5 (C+11)

    // implement some useful methods

    /**
     * Overloaded non-modifying string concat
     */
    DSString operator+(const DSString &);
    DSString operator+(const char[]);
    DSString operator+(char[]);

    /**
     * Standard relational operators to compare and order your strings.
     * Feel free to add additional.
     **/
    bool operator==(const DSString &) const;
    bool operator<(const DSString &) const;

    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString substring(size_t start, size_t numChars) const;
    //note I never implemented this function, because I implemented cut function which achieves same purpose except it takes in a start and end index

    /**
     * the c_str function returns a pointer a null-terminated c-string holding the
     * contents of this object. It would be smart to always have an extra `\0`
     * at the end of the string in DSString so you can just return a pointer to the
     * objects.
     **/
    [[nodiscard]] const char *c_str() const;

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument. `DSString&`
     * could be const, but then we would have to implement a const interator in
     * DSVector.
     **/
    friend std::ostream &operator<<(std::ostream &, const DSString &);

    // You are free to add more functionality to the class.  For example,
    // you may want to add a find(...) function that will search for a
    // substring within a string or a function that breaks a string into words.

    //prints the data of the string
    void print() const;
    //returns a bool true if string is empty
    [[nodiscard]] bool is_empty() const;
    //pushes a character to the back of the string
    void push_back(char in);
    //removes the last character of the string
    //note I didn't need this value to be returned but the function can be easily modified to return this value
    void pop_back();
    //removes the front char from the string
    //note I didn't need this value to be returned but the function can be easily modified to return this value
    void pop_front();
    //pushes a char to the front of the string
    void push_front(char in);
    //removes a character from a specific index
    void pop_mid(size_t index);
    //my implementation of substring because I wanted to use 2 indexes instead of an index and length
    DSString cut(size_t start, size_t end);
    //returns the length of the string
    size_t getLength() const;
    //returns a character at a position
    char at(size_t pos);
    //clears the string of data
    void clear();
    //function that implements porter2stemmer to the string
    void stemWord();
    //function that lowercases the string
    void to_Lower();
};

#endif