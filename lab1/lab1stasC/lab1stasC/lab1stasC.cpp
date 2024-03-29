
#include "pch.h"

#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
using namespace std;

struct map
{
	char simbvol;
	double frequency = 0;
};

void sortP(map*& arr, int size);
string readChapters(string name);
void writeChapters(string name, string text);
string code(string text, int shift);
int getNewCode(int code, int shift);
void createTableSimbvols(map*& tableSimbvols, int n, string text);
int getReversShift(map*& tableSimbvols1, map*& tableSimbvols2, int n);
 
int main()
{
	setlocale(LC_CTYPE, "rus");
	string name1 = "C:\\Users\\Mi\\Desktop\\RTU-MIREA\\lab1\\lab1stasC\\glavaOne.txt";
	string name2 = "C:\\Users\\Mi\\Desktop\\RTU-MIREA\\lab1\\lab1stasC\\glava1enc.txt";
	string name3 = "C:\\Users\\Mi\\Desktop\\RTU-MIREA\\lab1\\lab1stasC\\glava1dec.txt";
	string name4 = "C:\\Users\\Mi\\Desktop\\RTU-MIREA\\lab1\\lab1stasC\\voyna-i-mir-tom-1.txt";
	
	string textOfFirstChapter, textEnc, textDec, textAll;//текст первой главы, зашифрованный текст, расшифрованный текст и весь текст соответственно
	
	textOfFirstChapter = readChapters(name1);
	textEnc = code(textOfFirstChapter, 1);

	writeChapters(name2, textEnc);//записываем в файл 
	
	textAll = readChapters(name4);//читаем весь файл
	map *chapterOne = new map[64], *allChapters = new map[64];//создаем 2 массива текстур на 64 символа(32 заглавные буквы + 32 строчные)
	
	createTableSimbvols(chapterOne, 64, textEnc);//собираем таблицу частоты символов по зашифрованной главе
	createTableSimbvols(allChapters, 64, textAll);//собираем по всему тексту
	
	textDec = code(textEnc, getReversShift(chapterOne, allChapters, 64));//расшифровываем текст путем сдвига в обратную сторону
	writeChapters(name3, textDec);//записываем расшифрованный текст
	cout << "Счастливый конец после 7 часов ада.\nДенис, проставь позязя =^.^=\n";
	delete[]chapterOne;
	delete[]allChapters;
}

string readChapters(string name) {
	string text, line;

	ifstream in(name);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			text = text + line;
		}
	}
	in.close();   
	return text;
}

void writeChapters(string name, string text) {

	ofstream out(name.c_str()); //поток для записи
	if (!out)
	{
		cout << "That's no-no!\n";
	}
	else {
		cout << "Красава!\n";
		out << text ;
	}
	out.close(); 
}

void createTableSimbvols(map*& tableSimbvols, int n, string text) {//создам таблицы частоты символов
	double len = 0;
	for (int i = 0; i < text.length(); i++) {//пробегаемся по всем русским символам и заносим их количество в массив
		if ((int)text[i] < -1 && (int)text[i] > -65) {

			tableSimbvols[(int)text[i] + 64].frequency += 1;
			len++;//увеличиваем общее кол-во символов
		}
	}

	for (int i = 0; i < 64; i++) {
		tableSimbvols[i].simbvol = (char)i - 64;//присваиваем имена символов в заглавие структуры
		tableSimbvols[i].frequency = tableSimbvols[i].frequency / len;//делим кол-во конкретных символов на общее кол-во символов
	}
}

int getReversShift(map*& tableSimbvols1, map*& tableSimbvols2, int n) {//ищем обратный сдвиг
	sortP(tableSimbvols1, n);
	sortP(tableSimbvols2, n);

	return (int)tableSimbvols2[0].simbvol - (int)tableSimbvols1[0].simbvol;//вычитаем коды символов(первых, ибо мы отсортировали массивы), чтобы узнать насколько те сдвинулись
}

void sortP(map*& arr, int size)
{
	map temp;

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j].frequency < arr[j + 1].frequency) {
				// меняем элементы местами
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

string code(string text, int shift) {//шифруем текст

	string newText = "";
	char buf;
	for (int i = 0; i < text.length(); i++)//Читаем строку по символам и сдвигаем каждый из них
	{
		buf = (char)getNewCode((int)text[i], shift);
		newText = newText + buf;
	}

	return newText;
}

int getNewCode(int code, int shift) {//сдвиг буквы, если сдвиг = 2, то а = в
	
	shift = shift % 32;//защита от дебилов, чтобы не было сдвига больше алфавита
	int newCode = code;//если символ не русский, то возвращается тот же символ
	if(code > -65 && code < 0){
		newCode = newCode + shift;//если символ русский - прибавляем сдвиг

		if (code > -33) {
			
			if (newCode > -1) {
				newCode -= 32;
			}
			else if(code < -32){
				newCode += 32;
			}
		}
		else if (code < -32) {
			
			if (newCode >= -32) {
				newCode -= 32;
			}
			else if (code < -64) {
				newCode += 32;
			}	
		}
	}
	return newCode;//возвращаем новый символ
}