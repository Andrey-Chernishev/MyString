#include <iostream>
#include <stdexcept>
using namespace std;

class MyString {
	char* arrChar;
	size_t len;
public:
	const char* GetArrChar() const{
		return arrChar;
	}
	size_t GetLen() const{
		return len;
	}
	char GetChar(int n) const{
		return arrChar[n];
	}
	MyString() {
		len = 1;
		arrChar = new char[len];
		arrChar[0] = '\0';
		cout << "MyString()\n";
	}
	MyString(const char* newArrChar) {
		len = strlen(newArrChar)+1;//
		arrChar = new char[len];
		strcpy_s(arrChar, len, newArrChar);
		cout << "MyString(const char* newArrChar)\n";
	}

	MyString(const MyString& other) {
		cout << "MyString(const MyString& other)\n";
		this->len = other.len;
		this->arrChar = new char[len];
		for (size_t i = 0; i < len-1; i++) {
			this->arrChar[i] = other.arrChar[i];
		}
		this->arrChar[len - 1] = '\0';
	}

	MyString& operator=(const MyString& other) {
		if (this == &other) {
			return *this;
		}
		else {
			char* tmpArrChar = new char[other.len];
			this->len = other.len;
			for (size_t i = 0; i < len - 1; i++) {
				tmpArrChar[i] = other.arrChar[i];
			}
			tmpArrChar[len - 1] = '\0';
			delete[] this->arrChar;
			arrChar = tmpArrChar;
			tmpArrChar = nullptr;
			return *this;
		}
	}

	bool operator==(const MyString& other) const{
		if (this == &other) { return true; }
		else if (this->len != other.len) {
			return false;
		}
		else {
			for (size_t i = 0; i < (this->len - 1); i++) {
				if (this->arrChar[i] != other.arrChar[i]) {
					return false;
				}
			}
			return true;
		}
	}

	bool operator!=(const MyString & other) const{
		return !(operator==(other));
	}

	~MyString() {
		delete[] arrChar;
		arrChar = nullptr;
		cout << "~MyString()\n";
	}
	void print() const {
		cout << arrChar << endl;
	}
//в const объекте MyString может вызваться успешно только const метод, который const-объект не меняет
	char operator[](size_t idx) const{
		if (idx>len - 2) {
			throw out_of_range("Index is uncorrect!");
		}
		else {
			return arrChar[idx];
		}
	}
// в не const объекте мы можем заменить char на другой char, поэтому возвращаем char&
	char& operator[](size_t idx) {
		if (idx>len - 2) {
			throw out_of_range("Index is uncorrect!");
		}
		else {
			return arrChar[idx];
		}
	}

	operator const char*() const{
		return arrChar;
	}
};

MyString operator+(const MyString& str1, const MyString& str2) {
	size_t itogLen = str1.GetLen() + str2.GetLen() - 1;
	char* arrCharItog = new char[itogLen];
	size_t i1 = 0;
	for (; i1 < str1.GetLen() - 1; i1++) {
		arrCharItog[i1] = str1.GetChar(i1);
	}
	for (size_t i2 = 0; i2 < str2.GetLen() - 1; i2++) {
		arrCharItog[i1] = str2.GetChar(i2);
		i1++;
	}
	arrCharItog[itogLen - 1] = '\0';
	MyString itogStr(arrCharItog);
	arrCharItog = nullptr;
	return itogStr;
}

MyString operator+(const char* str1, const MyString& str2) {
	size_t itogLen = strlen(str1) + str2.GetLen();
	char* itogArrChar = new char[itogLen];
	size_t i1 = 0;
	for (; i1 < strlen(str1); i1++) {
		itogArrChar[i1] = str1[i1];
	}
	for (size_t i2 = 0; i2 < (str2.GetLen() - 1); i2++) {
		itogArrChar[i1] = str2.GetChar(i2);
		i1++;
	}
	itogArrChar[itogLen - 1] = '\0';
	MyString itogStr(itogArrChar);
	itogArrChar = nullptr;
	return itogStr;
}

MyString operator+(const MyString& str1, const char* str2) {
	size_t itogSize = str1.GetLen() + strlen(str2);
	char* itogArrChar = new char[itogSize];
	size_t i1 = 0;
	for (; i1 < (str1.GetLen() - 1); i1++) {
		itogArrChar[i1] = str1.GetChar(i1);
	}
	for (size_t i2 = 0; i2 < strlen(str2); i2++) {
		itogArrChar[i1] = str2[i2];
		i1++;
	}
	itogArrChar[itogSize - 1] = '\0';
	MyString itogStr(itogArrChar);
	itogArrChar = nullptr;
	return itogStr;
}

ostream& operator<<(ostream& os, const MyString& mStr) {
	os << mStr.GetArrChar();
	return os;
}

istream& operator>>(istream& is, MyString& mStr) {
	char tmpArr[1024];
	is >> tmpArr;
	mStr = MyString(tmpArr);
	return is;
}

int main() {
	setlocale(LC_ALL,"RU-ru");
	MyString s1("hello");
	MyString s2("world");
	MyString r = s1 + s2;
	r.print();
	return 0;
}