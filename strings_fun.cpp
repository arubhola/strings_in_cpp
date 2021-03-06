#include <iostream>
using namespace std;

typedef char* charPointer;

int stringLength(const charPointer s)
{
	/*
	returns the number of printable characters in s
	*/
	int len = 0;
	while(s[len] != '\0')
		len++;
	return len;
}

int countChars(const charPointer s, const char ch)
{
	/*
	returns the number of times the character ch is found in s
	*/
	int i, count = 0;
	for(i = 0; s[i] != '\0'; i++)
		if(s[i] == ch)
			count++;
	return count;
	
}

int findChar(const charPointer s, const char ch, const int startIndex, const int lastIndex)
{
	/*
	returns the first index where the character ch is found in s starting from 
	startIndex (inclusive) upto lastIndex (exclusive)
		If ch is not found in s in the interval, it returns -1
		This function must first validate both the startIndex and lastIndex.
		That is, if lastIndex > stringLength(s) or startIndex < 0 it must return -1
	*/
	int len = stringLength(s), i;
	if(lastIndex > len || startIndex<0)
		return -1;
	for(i = startIndex; i < lastIndex; i++)
		if(s[i] == ch)	
			return i;
	return -1;				
}

charPointer getCopy(const charPointer s)
{
	/*
	returns a new c-string which is a copy of s
	*/
	int len = stringLength(s), i;
	charPointer s2 = new char[len+1];
	for(i = 0; i<len; i++)
		s2[i] = s[i];
	s2[i] = '\0';
	return s2;
}

void rotateLeft(charPointer s)
{
	char temp;
	int i, len;
	
	len = stringLength(s);

	temp = s[0];

	for(i = 0; i<len-1; i++)
		s[i] = s[i+1];
		
	s[len-1] = temp;
}

void rotateRight(charPointer s)
{
	char temp;
	int i, len;
	
	len = stringLength(s);

	temp = s[len-1];
	
	for(i = len-1; i>0; i--)
		s[i] = s[i-1];

	s[0] = temp;
}

void rotateString(charPointer s, const int r)
{
	/*
	Rotates the characters of s by r units
		If r > 0, rotate the characters of s to the left
		If r < 0, rotate the characters of s to the right
		Please note the value of r can be any integer even larger than the length of s
		For example,
			"asmara" rotated to the left by 0 becomes "asmara"
			"asmara" rotated to the left by 1 becomes "smaraa"
			"asmara" rotated to the left by 2 becomes "maraas"
			"asmara" rotated to the left by 3 becomes "araasm"
			"asmara" rotated to the left by 4 becomes "raasma" 
			"asmara" rotated to the left by 5 becomes "aasmar" 
			"asmara" rotated to the left by 6 becomes "asmara" 
			"asmara" rotated to the left by 7 becomes "smaraa" 
			"asmara" rotated to the left by 8 becomes "maraas"

		similarly
			"asmara" rotated to the right by 0 becomes "asmara"
			"asmara" rotated to the right by 1 becomes "aasmar"
			"asmara" rotated to the right by 2 becomes "raasma"
			"asmara" rotated to the right by 3 becomes "araasm"
			"asmara" rotated to the right by 4 becomes "maraas" 
			"asmara" rotated to the right by 5 becomes "smaraa" 
			"asmara" rotated to the right by 6 becomes "asmara" 
			"asmara" rotated to the right by 7 becomes "aasmar" 
			"asmara" rotated to the right by 8 becomes "raasma" 

			and etc… 
	*/
	int i;

	if(r>0)
	{
		for(i = 0; i<r; i++)
			rotateLeft(s);

	}
	else if(r<0)
	{
		int p = -r;
		for(i = 0; i<p; i++)
			rotateRight(s);	
	}
}

void append(charPointer &s, const char ch)
{
	/*
	Appends the character ch to the c-string s.
		That is ch is added to the end of s making sure the resulting s is a valid c-string
		The parameter s is assumed to be a dynamic array (NOT a static array)
	*/

	int len = stringLength(s), i;
	charPointer s2 = new char[len+2];
	
	for(i = 0; i < len; i++)
		s2[i] = s[i];
	
	s2[len] = ch;
	s2[len+1] = '\0';

	delete []s;

	s = s2;
}

void append(charPointer &s1, const charPointer s2)
{
	/*
	Appends all the characters of s2 to s1
		The parameter s1 is assumed to be a dynamic array (NOT a static array)
	*/
	int len2 = stringLength(s2), i;
	for(i = 0; i<len2 ; i++)
		append(s1, s2[i]);
}

void removeAll(charPointer &s, const char ch)
{
	/*
	Removes all the occurrences of the character ch from the c-string s
		The parameter s is assumed to be a dynamic array (NOT a static array)
	*/
	int len = stringLength(s), i, j;
	int count = countChars(s, ch);
	charPointer s2 = new char[len+1-count];

	for(i = 0, j = 0; i<len; i++)
		if(s[i] != ch)
		{
			s2[j] = s[i];
			j++;
		}
	s2[j] = '\0';

	delete []s;
	s = s2;
	
}

charPointer zigzagMerge(const charPointer s1, const charPointer s2)
{
	/*
	Creates and returns a new c-string by merging (combining) s1 and s2 in zigzag form. 
		That is 
			first character of the new c-string is the first character of s1
			second character of the new c-string is the first character of s2
			third character of the new c-string is the second character of s1
			fourth character of the new c-string is the second character of s2
			fifth character of the new c-string is the third character of s1
			sixth character of the new c-string is the third character of s2
			etc
		When either s1 or s2 reaches to its end, the remaining characters of the other are 
		appended to the new c-string
		For example, the zigzagMerge of "abc" and "defgh" will be "adbecfgh"
	*/
	int len1 = stringLength(s1);
	int len2 = stringLength(s2);
	int i ,j, k, len3;
	len3 = len1 + len2;

	charPointer s3 = new char[len3+1];

	if(len1 >len2)
	{
		for(k = 0, i = 0, j= 0; j<len2 ; k++, i++, j++)
		{
			s3[k] = s1[i];
			k++;
			s3[k] = s2[j];
		}
		
		for(i, k; i<len1, k<len3; i++, k++)
			s3[k] = s1[i];
	}
	else if(len1<len2)
	{
		for(k = 0, i = 0, j= 0; i<len1 ; k++, i++, j++)
		{
			s3[k] = s1[i];
			k++;
			s3[k] = s2[j];
		}
		
		for(j, k; j<len2, k<len3; j++, k++)
			s3[k] = s2[j];
	}
	else
	{
		for(k = 0, i = 0, j= 0; k<len3, i<len1, j<len2; k++, i++, j++)
		{
			s3[k] = s1[i];
			k++;
			s3[k] = s2[j];
		}
	}
	s3[len3] = '\0';
	return s3;
}

bool isAnagram(const charPointer s1, const charPointer s2)
{
	int len1 = stringLength(s1);
	int len2 = stringLength(s2);

	int i, count;

	if (len1 != len2)
		return false;
	
	for(i = 0; i<len2; i++)
	{
		count = countChars(s1, s2[i]);
		if(count < 1)
			return false;
	}

	return true;
}

charPointer getSubString(const charPointer s, const int startIndex, const int len)
{
	/*
	returns a new c-string consisting of len characters of s starting from startIndex.
		If s has fewer characters starting from the startIndex upto its last character, 
		then the returned c-string must consist only the available characters. In this case, 
the returned c-string will have less than len characters.
	*/
	int len1 = stringLength(s), copyLen, i, j;

	if((len1 - startIndex) >= len)
		copyLen = len;
	else
		copyLen = len1 - startIndex;

	charPointer s2 = new char[copyLen +1];
	
	for(i = startIndex, j = 0; j<copyLen ; i++, j++)
		s2[j] = s[i];

	s2[copyLen] = '\0';
	return s2;
}

bool isEqual(const charPointer s1, const charPointer s2)
{
	/*
	returns true if the c-string s1 is equal to the c-string s2
		Definition: Two c-strings s1 and s2 are equal if they have the same length
		and characters of s1 and s2 at corresponding indexes are the same.
	*/
	int len1 = stringLength(s1);
	int len2 = stringLength(s2);
	
	if(len1 != len2)
		return false;
	
	for(int i = 0; i<len1; i++)
		if(s1[i] != s2[i])
			return false;

	return true;
}

bool isSubString(const charPointer s1, const charPointer s2)
{
	/*
	returns true is s1 is a substring of s2 otherwise returns false
		Definition: s1 is a substring of s2 if s1 is found in s2. 
		That is all characters of s1 are found TOGETHER in s2 in the SAME ORDER as they appear in s1
		Example "set" is a substring of "massachussettes" But "ets" is not substring of 
		"massachussettes"
	*/
	int len1 = stringLength(s1);
	int len2 = stringLength(s2), i;

	if(len1 > len2)
		return false;

	charPointer s3;

	for(i = 0; i<=(len2-len1); i++)
	{
		s3 = getSubString(s2, i, len1);
		if(isEqual(s1, s3))
			return true;
	}

	return false;	
}

int countWords(const charPointer s)
{
	/*
	Given a c-string that contains some words separated by spaces, this function
	returns the number of words in the c-string.
		Here, a word means some characters with no any space among them.
		Example: The c-string "What    a     nice           problem " has FOUR words.
		     1. What      2. a       3. nice      4. problem
		Your function then must return 4

		For simplicity,
		1. Assume words are separated by spaces only (i.e. no tab or end of line characters)
		2. Assume that there are no spaces at the beginning of the c-string
		3. But a word can be separated from another word by one or more spaces
		4. Assume there is no any punctuation mark in the c-string.
	*/
	
	int len = stringLength(s), i, count = 0;

	for(i = 0; i<len; i++)
	{
		if((s[i+1] == ' ' || s[i+1] == '\0') && s[i]!= ' ')
			count++;
	}
	return count;
}

int main()
{
	/*
	This main program is designed to test the functions you need to implement.
	You should NOT remove any line of code from this main program.
	But you may add more test code in the main program if you like.
	*/

	//Test stringLength function
	cout << endl;
	char s1[] = "mas$sachus#settes";
	cout << s1 << " has " << stringLength(s1) << " characters" << endl;

	//Test countChars function
	cout << endl;
	char ch = 's';
	int c = countChars(s1, ch);
	cout << ch << " appears " << c << " times in " << s1 << endl;

	//Test findChar function
	cout << endl;
	int index = findChar(s1, ch, 10, 14);
	if (index == -1)
		cout << ch << " is not found in " << s1 << " between indexes [10, 14)" << endl;
	else
		cout << ch << " is found at index " << index << " in " << s1 << " between indexes [10, 14)" << endl;

	//Test getCopy function
	cout << endl;
	charPointer s2 = getCopy(s1);
	cout << "A copy of " << s1 << " is " << s2 << endl;

	//Test rotateString function
	cout << endl;
	rotateString(s2, 2);
	cout << s1 << " rotated 2 units to the left becomes " << s2 << endl;
	charPointer s3 = getCopy(s1);
	rotateString(s3, -19);
	cout << s1 << " rotated 19 units to the right becomes " << s3 << endl;

	//Test append function (appending a character to c-string)
	cout << endl;
	charPointer s4 = new char[1];
	s4[0] = '\0';
	cout << "Given the c-string " << s4 << endl;
	ch = 'a';
	append(s4, ch);
	cout << "\tAppending " << ch << " results to " << s4 << endl;
	ch = 'b';
	append(s4, ch);
	cout << "\tAppending " << ch << " results to " << s4 << endl;

	//Test append function (appending a c-string to a c-string)
	cout << endl;
	cout << "Appending " << s1 << " to " << s4 << ", we get ";
	append(s4, s1);
	cout << s4 << endl;

	//Test removeAll function
	cout << endl;
	ch = 'e';
	cout << "Removing all occurences of " << ch << " from " << s4 << ", we get ";
	removeAll(s4, ch);
	cout << s4 << endl;
	ch = 't';
	cout << "Removing all occurences of " << ch << " from " << s4 << ", we get ";
	removeAll(s4, ch);
	cout << s4 << endl;
	ch = 's';
	cout << "Removing all occurences of " << ch << " from " << s4 << ", we get ";
	removeAll(s4, ch);
	cout << s4 << endl;

	//Test zigzagMerge function
	cout << endl;
	charPointer s5 = zigzagMerge(s1, s4);
	cout << "The zigzag merge of " << s1 << " and " << s4 << " is " << s5 << endl;

	//Test isAnagram function
	cout << endl;
	bool flag = isAnagram(s1, s2);
	if (flag)
		cout << s1 << " and " << s2 << " are anagrams" << endl;
	else
		cout << s1 << " and " << s2 << " are not anagrams" << endl;

	//Test getSubString function
	cout << endl;
	charPointer s6 = getSubString(s3, 3, 5);
	cout << "The substring of " << s3 << " starting from index 3 and with 5 characters is " << s6 << endl;
	charPointer s7 = getSubString(s3, 12, 10);
	cout << "The substring of " << s3 << " starting from index 12 and with 10 characters is " << s7 << endl;

	//Test isEqual function
	cout << endl;
	char s8[] = "Yonas";
	char s9[] = "Yonas";
	char s10[] = "YonaS";
	if (isEqual(s8, s9) == true)
		cout << s8 << " and " << s9 << " are equal." << endl;
	else
		cout << s8 << " and " << s9 << " are not equal." << endl;
	if (isEqual(s8, s10) == true)
		cout << s8 << " and " << s10 << " are equal." << endl;
	else
		cout << s8 << " and " << s10 << " are not equal." << endl;

	//Test isSubString function
	cout << endl;
	flag = isSubString(s1, s4);
	if (flag == true)
		cout << s1 << " is a substring of " << s4 << endl;
	else
		cout << s1 << " is not a substring of " << s4 << endl;
	char s11[] = "abort";
	char s12[] = "abcabodefaborhuhabortabunny";
	flag = isSubString(s11, s12);
	if (flag == true)
		cout << s11 << " is a substring of " << s12 << endl;
	else
		cout << s11 << " is not a substring of " << s12 << endl;

	//Test countWords function
	cout << endl;
	char s13[] = "";
	c = countWords(s13);
	cout << "There are " << c << " words in " << s13 << endl;
	char s14[] = "Test";
	c = countWords(s14);
	cout << "There are " << c << " words in " << s14 << endl;
	char s15[] = "Nice       one";
	c = countWords(s15);
	cout << "There are " << c << " words in " << s15 << endl;
	char s16[] = "This      is a nice     assignment and    hopefully an interesting    as well     ";
	c = countWords(s16);
	cout << "There are " << c << " words in " << s16 << endl;

	//Delete dynamically allocated memories
	delete[] s2;	
	delete[] s3;	
	delete[] s4;
	delete[] s5;	
	delete[] s6;	
	delete[] s7;

	system("Pause");
	return 0;
} 
