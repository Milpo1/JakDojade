#pragma once
#include <iostream>
#define STR_BLOCK_SIZE 8

class String
{
private:
	int blocks;
public:
	char* str; 
	int length;
	String();
	String(char* str);
	String(const String& other);
	~String();
	int getLength() const;
	void clear();
	int calculateLength() const;
	void allocate(int length);
	void setStr(const char* str);
	void cutSpaces();
	char* getStr() const;
	bool isNumber();
	//Checks if the string contains an alphanumeric character
	bool hasAChar();
	bool operator==(const String& right);
	String& operator=(const String& right);
	String& operator+(const String& right);
	String& operator+(const char* right);
	String& operator+(char right);
};
std::ostream& operator<<(std::ostream& os, const String& string);

