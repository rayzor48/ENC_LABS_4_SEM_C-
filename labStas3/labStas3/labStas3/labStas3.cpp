#include "pch.h"
//как мне позже объяснили, я выбрал не самую оптимальную библиотеку, для работы с большими числами, из-за чего ебался больше чем надо
//потом может перепишу на новой, но пока пусть все будет так, как есть, ибо так оно РАБОТАЕТ
#include "BigInt.hpp"//файл с гита для работы с большими чисами
#include "constructors/constructors.hpp"
#include "functions/conversion.hpp"
#include "functions/math.hpp"
#include "operators/binary_arithmetic.hpp"
#include "operators/io_stream.hpp"
#include "functions/random.hpp"
//#include "random.hpp"//файл с гита для генерации большихи случайных чисел#include "math.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "picosha2.h"//файл с гитхаба, для функций хэширования
#include <locale.h> 

struct Task_miler
{
	BigInt result;
	BigInt mulmod(BigInt a, BigInt b, BigInt mod)
	{
		BigInt x = 0, y = a % mod;
		while (b > 0)
		{
			if (b % 2 == 1)
			{
				x = (x + y) % mod;
			}
			y = (y * 2) % mod;
			b /= 2;
		}
		return x % mod;
	}
	/*
	 * modular exponentiation
	 */
	BigInt modulo(BigInt base, BigInt exponent, BigInt mod)
	{
		BigInt x = 1;
		BigInt y = base;
		while (exponent > 0)
		{
			if (exponent % 2 == 1)
				x = (x * y) % mod;
			y = (y * y) % mod;
			exponent = exponent / 2;
		}
		return x % mod;
	}

	/*
	 * Miller-Rabin primality test, iteration signifies the accuracy
	 */
	bool miler(BigInt p, int iteration)
	{
		//std::cout << "p = " << p << std::endl;
		if (p < 2)
		{
			return false;
		}
		if (p != 2 && p % 2 == 0)
		{
			return false;
		}
		BigInt s = p - 1;
		while (s % 2 == 0)
		{
			s /= 2;
		}
		for (int i = 0; i < iteration; i++)
		{
			BigInt a = rand() % (p - 1) + 1, temp = s;
			BigInt mod = modulo(a, temp, p);
			while (temp != p - 1 && mod != 1 && mod != p - 1)
			{
				mod = mulmod(mod, mod, p);
				temp *= 2;
			}
			if (mod != p - 1 && temp % 2 == 0)
			{
				return false;
			}
		}
		return true;
	}

	Task_miler(BigInt from, int iter)
	{
		for (BigInt i = from; true; i += 2)
		{
			if (miler(i, iter))
			{
				result = i;
				break;
			}
		}
	}
};

BigInt bpow(const BigInt& base, int exp);//для перевода из шестнадцатиричной системы в 10
BigInt HEX_TO_DEC(std::string st);//из 16 в 10
std::string getHash(std::string str);//расчитывает ХэшКод для строки
std::string genSalt(int lenght);//генерирует соль

std::string ToBinary(BigInt b);//перевод из 10 системы в 2

BigInt BinaryToBig(std::string st);//перевод из 2 системы в 10

std::string sdvig(std::string src)//сдвигает число вправо на 1 бит(вместо перегрузки оператора >>)
{
	std::string result;
	result = src.substr(0, src.length() - 1);
	return result;
}

bool chheck(std::string l) {//проверяет, l > 0 если да -> true, иначе -> false
	for (int i = 0; i < l.length(); i++) {
		if (l[i] == '1')
		{
			return true;
		}
	}
	return false;
}//проверяет, l > 0 если да -> true, иначе -> false

BigInt ifNegativ(BigInt a, BigInt b);

BigInt modpow(BigInt base, BigInt exp, BigInt modulus);//возведение в степень по модулю

BigInt xor1(BigInt a, BigInt b);//реализует xor двух BigInt

int main()
{
	setlocale(LC_CTYPE, "rus");

	BigInt N("324334253245324532456367346279");//константа N
	/*BigInt N;//поиск случайного N, работает, но долго ищет

	Task_miler task(big_random(15), 5);//генерация простого 30 значного числа
	N = task.result;//присваиваем найденное N
	N = N * 2 + 1;
	*/

	std::cout << std::endl << "N = " << N  << std::endl;
	BigInt g = 2;//ищем первородный корень по модулю N
	
	//std::string for_hash = ;//strcat(strcpy(for_hash, N.to_string;), string2);

	BigInt k = HEX_TO_DEC(getHash(N.to_string() + g.to_string()));// % (N*N *N * 100);

	std::cout << std::endl << "k = " << k << std::endl;

	BigInt v, x;
	BigInt a, A, A1, b, B;
	BigInt u;
	BigInt S1, S2, K1, K2;
	std::string AB, S1s, S2s;

	std::string name = "Nastya";
	std::string password = "pass";
	std::string salt = "123242315123";//genSalt()

	x = HEX_TO_DEC(getHash(salt + password));
	std::cout << "x = " << x << std::endl;

	v = modpow(g, x, N);
	std::cout << std::endl << "v = " << v << std::endl;

	a = big_random(15);

	std::cout << "a = " << a << std::endl;
	A = modpow(g, a, N);
	std::cout << "A = " << A << std::endl;

	b = big_random(15);
	BigInt kv = k * (modpow(g, x, N));
	B = (kv + modpow(g, b, N)) % N;

	std::cout << "b = " << b << std::endl;
	std::cout << "B = " << B << std::endl;
	
	AB = A.to_string() + B.to_string();
	u = HEX_TO_DEC(getHash(AB));
	std::cout << "u = " << u << std::endl;
	
	x = HEX_TO_DEC(getHash(salt + "pass"));//раскоментировать, если будет проверка на другом "пароле"
	BigInt buf1 = (B - k * modpow(g, x, N));
	BigInt buf2 = (a + u * x);
	BigInt buf3 = A * modpow(v, u, N);

	//S = ((B - k*(g^x % N)) ^ (a + u*x)) % N
	S1 = modpow(buf1, buf2, N);
	S1s = S1.to_string();
	K1 = HEX_TO_DEC(S1s);
	
	//S = ((A*(v^u % N)) ^ b) % N
	S2 = modpow(buf3, b, N);
	S2s = S2.to_string();
	K2 = HEX_TO_DEC(S2s);

	std::cout << "S1 = " << S1 << std::endl;
	std::cout << "S2 = " << S2 << std::endl;
	std::cout << "K1 = " << K1 << std::endl;
	std::cout << "K2 = " << K2 << std::endl;

	//M = H(H(N) XOR H(g), H(I), s, A, B, K)
	BigInt HM, HN, HMxorHG, HG, HI,M1, M2;
	HN = HEX_TO_DEC(getHash(N.to_string()));
	HG = HEX_TO_DEC(getHash(g.to_string()));
	HI = HEX_TO_DEC(getHash(name));
	HMxorHG = xor1(HN, HG);
	M1 = HEX_TO_DEC(getHash(HMxorHG.to_string() + HI.to_string() + salt + A.to_string() + B.to_string() + K1.to_string()));
	M2 = HEX_TO_DEC(getHash(HMxorHG.to_string() + HI.to_string() + salt + A.to_string() + B.to_string() + K2.to_string()));

	if (M1 != M2) {
		std::cout << "Server: Ya tebya ne znayu!" << std::endl;
	}
	else {
		std::cout << "Server: Ya tebya znayu!" << std::endl;
	}

	std::cout << "M1 = " << M1 << std::endl;
	std::cout << "M2 = " << M2 << std::endl;

	BigInt R1, R2;
	R1 = HEX_TO_DEC(getHash(A.to_string() + M1.to_string() + K1.to_string()));
	R2 = HEX_TO_DEC(getHash(A.to_string() + M2.to_string() + K2.to_string()));

	if (R1 != R2) {
		std::cout << "Client: I ya tebya ne znayu!" << std::endl;
	}
	else {
		std::cout << "Client: I ya tebya znayu!" << std::endl;
	}

	std::cout << "R1 = " << R1 << std::endl;
	std::cout << "R2 = " << R2 << std::endl;
}

std::string getHash(std::string str) {

	//std::string src_str = "asdfasdf, adasfasdgas";

	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(str.begin(), str.end(), hash.begin(), hash.end());

	std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());

	return hex_str;
}

BigInt HEX_TO_DEC(std::string st)
{
	int i,  p;
	BigInt k;
	BigInt s = 0;
	p = st.length() - 1;
	for (i = 0; st[i] != '\0'; i++)
	{
		switch (toupper(st[i]))
		{
		case 'A': k = 10; break;
		case 'B': k = 11; break;
		case 'C': k = 12; break;
		case 'D': k = 13; break;
		case 'E': k = 14; break;
		case 'F': k = 15; break;
		case '1': k = 1; break;
		case '2': k = 2; break;
		case '3': k = 3; break;
		case '4': k = 4; break;
		case '5': k = 5; break;
		case '6': k = 6; break;
		case '7': k = 7; break;
		case '8': k = 8; break;
		case '9': k = 9; break;
		case '0': k = 0; break;
		}
		s = s + k * bpow(16, p);
		p--;
	}
	//std::cout << s;
	return s;
}

int rrand(int range_min, int range_max)
{
	return rand() % (range_max - range_min + 1) + range_min;
}

std::string genSalt(int length) {

	std::string base = "0123456789";//abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789
	std::string result(length, '*');

	result[0] = base[rrand(1, result.size() - 1)];

	for (int i = 1; i < length - 1; i++)
	{
		result[i] = base[rrand(0, base.size() - 1)];
	}
	result.back() = '3';

	return result;
}

BigInt bpow(const BigInt& base, int exp) {
	if (exp < 0) {
		if (base == 0)
			throw std::logic_error("Cannot divide by zero");
		return abs(base) == 1 ? base : 0;
	}
	if (exp == 0) {
		if (base == 0)
			throw std::logic_error("Zero cannot be raised to zero");
		return 1;
	}

	BigInt result = base, result_odd = 1;
	while (exp > 1) {
		if (exp % 2)
			result_odd *= result;
		result *= result;
		exp /= 2;
	}

	return result * result_odd;
}

BigInt ifNegativ(BigInt a, BigInt b) {
	BigInt count;
	if (a < 0) {
		count = a / b;
		a = a + b * count;
	}

	while (a < 0) {
		a = a + b;
	}
	return a;
}

BigInt modpow(BigInt base, BigInt exp, BigInt modulus) {
	//base %= modulus;

	//std::cout << " base =  " << base << std::endl;
	BigInt result = 1;
	std::string bin = ToBinary(exp);
	while (chheck(bin)) {
		//bin = ToBinary(exp);
		//std::cout << " bin =  " << bin << std::endl;
		if (bin[bin.length() - 1] == '1') {
			result = (result * base) % modulus;
			//std::cout << " (result * base) % modulus =  " << result << std::endl;
		}
		//std::cout << " bin.length(); " << bin.length() << std::endl;
		base = pow(base, 2) % modulus;
		//std::cout << " (base * base) % modulus =  " << base << std::endl;
		//std::cout << " exp  " << exp << std::endl;
		bin = sdvig(bin);
		//exp = BinaryToBig(bin);
	}

	result = ifNegativ(result, modulus);//если основание отрицательное, то делаем его положительным
	return result;
}

BigInt BinaryToBig(std::string st) {

	int i, p;
	BigInt k;
	BigInt s = 0;
	p = st.length() - 1;
	for (i = 0; st[i] != '\0'; i++)
	{
		if (st[i] == '1') {

			s = s + pow(2, p);
		}
		p--;
	}
	return s;
}

std::string ToBinary(BigInt b)
{
	std::string result = "";

	while (b != 1) {

		if (b % 2 == 1) {
			result = "1" + result;
		}
		else {
			result = "0" + result;
		}

		b = b / 2;
	}

	result = "1" + result;

	while (result.length() % 4 != 0) {
		result = "0" + result;
	}
	return result;
}

BigInt xor1(BigInt a, BigInt b) {
	std::string buf1, buf2, buf3;
	buf1 = ToBinary(a);
	buf2 = ToBinary(b);
	if (buf1.length() != buf2.length()) {
		if (buf1.length() < buf2.length()) {
			buf1 = "0" + buf1;
		}
		else {
			buf2 = "0" + buf2;
		}
	}

	for (int i = buf2.length() - 1; i >= 0; i--) {
		if (buf1[i] != buf2[i]) {
			buf3 += "1";
		}
		else {
			buf3 += "0";
		}
	}

	//std::cout << buf1 << std::endl;
	//std::cout << buf2 << std::endl;
	//std::cout << buf3 << std::endl;

	BigInt result = BinaryToBig(buf3);
	return result;
}