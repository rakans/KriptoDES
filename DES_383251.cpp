#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
string sBox(string text){
	string _template[] = {"0010", "1110", "1100", "1011", "0100", "0010", "0001", "1100", "0111", "0100", "1010", "0111", "1011", "1101", "0110", "0001", "1000", "0101", "0101", "0000", "0011", "1111", "1111", "1010", "1101", "0011", "0000", "1001", "1110", "1000", "1001", "0110",
							"0100", "1011", "0010", "1000", "0001", "1100", "1011", "0111", "1010", "0001", "1101", "1110", "0111", "0010", "1000", "1101", "1111", "0110", "1001", "1111", "1100", "0000", "0101", "1001", "0110", "1010", "0011", "0100", "0000", "0101", "1110", "0011"};
	string x = "";
	int idx = 0;
	while(idx<text.length()){
		int temp = 0, n = idx+6;
		while(idx<n) temp = temp*2+(text[idx++]-'0');
		x+=_template[temp];
	}
	return x;
}
string permutation(string text){
	int _template[] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
	string x = "";
	for(int i=0; i<32; i++) x+=text[_template[i]-1];
	return x;
}
void xorTK(string &text1, string text2){
	for(int i=0; i<text1.length(); i++) text1[i] = text1[i]!=text2[i] ? '1' : '0';
}
string expansion(string text){
	int _template[] = {31, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
	string x = "";
	for(int i=0; i<48; i++) x+=text[_template[i]-1];
	return x;
}
string initialPermutation(string plainText){
	int _template[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
	string x = "";
	for(int i=0; i<64; i++) x+=plainText[_template[i]-1];
	return x;
}
string inverseInitialPermutation(string cipherText){
	int _template[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 63, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
	string x = "";
	for(int i=0; i<64; i++) x+=cipherText[_template[i]-1];
	return x;
}

void leftShift(string &key, int LS){
	string tmp;
	tmp.append(key, 0, LS);
	key.insert(28, tmp);
	key.erase(0, LS);
	tmp.append(key, 28, LS);
	key+=tmp;
	key.erase(28, LS);
}
string PC2(string key){
	int _template[] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
	string x = "";
	for(int i=0; i<48; i++) x+=key[_template[i]-1];
	return x;
}
string PC1(string externalKey){
	int _template[] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
	string x = "";
	for(int i=0; i<56; i++) x += externalKey[_template[i]-1];
	return x;
}
string generateKey(string &key, int LS){
	leftShift(key, LS);
	return PC2(key);
}
void encryptDES(string &text, string &key, int LS){
	string key_tmp = generateKey(key, LS);
	string left, right;
	left.append(text, 0, 32);
	text.erase(0, 32);
	right = text;
	right = expansion(right);
	xorTK(right, key_tmp);
	right = permutation(sBox(right));
	xorTK(right, left);
	text += right;
}

void randomInput(string &plainText, string &externalKey){
	srand(time(NULL));
	for(int i=0; i<64; i++){
		plainText+= rand()%2+'0';
		externalKey+= rand()%2+'0';
	}
	cout<<"Plaintext = "<<plainText<<"\nExternal Key = "<<externalKey<<endl;
}
void exampleInput(string &plainText, string &externalKey){
	plainText = "1100110011001100010101010101010111001011100011000111000011100001";
	externalKey = "1010101010100011001100110011001100110011001100110011101010101010";
}
void manualInput(string &plainText, string &externalKey){
	cin>>plainText;
	cin>>externalKey;
}

int main(){
	string plainText = "";
	string externalKey = "";
	int scheduleLS[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	//exampleInput(plainText, externalKey);
	manualInput(plainText, externalKey);
	//randomInput(plainText, externalKey);
	string key = PC1(externalKey);
	string cipherText = initialPermutation(plainText);
	for(int i=0; i<16; i++) encryptDES(cipherText, key, scheduleLS[i]);
	cout<<"Ciphertext = "<<cipherText<<endl;
}
