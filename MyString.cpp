#include "MyString.h"
#define MIN_ASCII '!'
#define MAX_ASCII '~'
#define ZERO '0'
#define NINE '9'
#define EOS '\0'

bool String::isNumber()
{
	if (this->str == nullptr) return 0;
	int l = 0;
	while (this->str[l] != EOS)
	{
		if (this->str[l] >= ZERO && this->str[l++] <= NINE) {}
		else return false;
	}
	return true;
}
bool String::hasAChar()
{
	if (this->str == nullptr) return 0;
	int l = 0;
	while (this->str[l] != EOS)
	{
		if (this->str[l] >= MIN_ASCII && this->str[l++] <= MAX_ASCII) return true;
	}
	return false;
}
void String::clear()
{
	if (this->str != nullptr) delete[] str;
	this->str = nullptr;
	this->blocks = 0;
}
int String::calculateLength() const
{
	if (this == nullptr) return 0;
	if (this->str == nullptr) return 0;
	int l = 0;
	while (this->str[l++] != EOS) {}
	return l;
}
int String::getLength() const
{
	return this->length;
}
void String::allocate(int length)
{
	if (length < 0) return;
	this->blocks = (length - 1) / STR_BLOCK_SIZE + 1;
	this->length = length;
	if (this->str != nullptr)
	{
		char* temp = new char[this->blocks * STR_BLOCK_SIZE];
		for (int i = 0; i < length; i++)
		{
			temp[i] = this->str[i];
			if (str[i] == EOS) break;
		}
		delete[] this->str;
		this->str = temp;
		return;
	}
	this->str = new char[this->blocks * STR_BLOCK_SIZE];
}
String::String()
{
	this->str = nullptr;
	this->blocks = 0;
}
String::String(const String& other)
{
	this->str = nullptr;
	this->blocks = other.blocks;
	int l = other.blocks * STR_BLOCK_SIZE;
	this->str = new char[l];
	for (int i = 0; i < l; i++)
		this->str[i] = other.str[i];
}
String::String(char* str)
{
	this->str = nullptr;
	this->blocks = 0;
	this->setStr(str);
}
String& String::operator=(const String& right)
{
	std::swap(str, ((String&)right).str);
	this->blocks = right.blocks;
	this->length = right.length;
	return *this;
}
void String::setStr(const char* str)
{
	int l;
	if (str != nullptr)
	{
		l = 0;
		while (str[l++] != EOS) {}
		this->allocate(l);
		for (int i = 0; i < l; i++)
			this->str[i] = str[i];
	}
}
char* String::getStr() const
{
	return this->str;
}
bool String::operator==(const String& right)
{
	if (this->str == nullptr || right.str == nullptr) return false;
	int thisLength = this->getLength();
	int rightLength = right.getLength();
	if (thisLength != rightLength && this->length != -1 && right.length != -1) return false;
	for (int i = 0; i < thisLength; i++)
	{
		if (this->str[i] != right.str[i]) return false;
	}
	return true;
}
String& String::operator+(const String& right)
{
	if (this->str == nullptr)
	{
		this->setStr(right.str);
		return *this;
	}
	int a = this->getLength(), b = right.getLength();
	if (a + b - 1 < this->blocks * STR_BLOCK_SIZE)
	{
		for (int i = 0; i < b; i++)
		{
			this->str[i + a - 1] = right.str[i];
		}
		this->length = a + b - 1;
		return *this;
	}

	this->allocate(a + b - 1);
	for (int i = 0; i < b; i++)
	{
		this->str[a - 1 + i] = right.str[i];
	}
	return *this;
}
String& String::operator+(const char* right)
{
	if (this->str == nullptr)
	{
		this->setStr(right);
		return *this;
	}
	int a = this->getLength(), b = 0;
	while (right[b++] != EOS) {}
	if (a + b - 1 < this->blocks * STR_BLOCK_SIZE)
	{
		for (int i = 0; i < b; i++)
		{
			this->str[i + a - 1] = right[i];
		}
		this->length = a + b - 1;
		return *this;
	}

	this->allocate(a + b - 1);
	for (int i = 0; i < b; i++)
	{
		this->str[a - 1 + i] = right[i];
	}
	return *this;
}
String& String::operator+(char right)
{
	char toAppend[] = { right,'\0' };
	return *this + toAppend;
}
void String::cutSpaces()
{
	if (this == nullptr || this->str == nullptr)
	{
		return;
	}
	int l = this->getLength() - 1;
	for (; l >= 0; l--)
	{
		if (this->str[l] == ' ') this->str[l] = EOS;
		else if (this->str[l] != '\0') return;
	}

}
String::~String()
{
	if (str != nullptr)
	{
		delete[] str;
	}
}
std::ostream& operator<<(std::ostream& os, const String& string) {
	return os << string.getStr();
}