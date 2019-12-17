#include <iostream>
#include <time.h>
#include <math.h>

int gen_prostoe_chislo();

double getPRoot(int p);
bool checkRoot(int p, int g);
bool contains(int*& mass, int n, int x);

template <typename T>
T modpow(T base, T exp, T modulus) {
	base %= modulus;
	T result = 1;
	while (exp > 0) {
		if (exp & 1) result = (long int)(result * base) % modulus;
		base = (long int)(base * base) % modulus;
		exp >>= 1;
	}
	return result;
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	int mass[30];

	long int g, p;//
	long int a, b;//секретные числа Алисы и Боба
	long int A, B;//открытые ключи Алисы и Боба
	long int SA, SB;//закрытые ключи Алисы и Боба(Должны совпадать)

	p = gen_prostoe_chislo();
	g = getPRoot(p);

	std::cout << "Шерлок и Ватсон решили уехать в отпуск в тайне от Мориарти, но так как они были в отдалении друг от друга,\n решили использовать алгоритм Диффи — Хеллмана для выбора ключа шифрования" << std::endl;
	std::cout << "Шерлок и Ватсон выбрали " << "p = " << p << " g = " << g << std::endl;
	std::cout << " Мориарти догадался, что шерлок устал от него и решил, во чтобы то ни стало разузнать маршрут своих недругов..." << std::endl << std::endl;

	srand((unsigned)time(0));

	for (int i = 0; i < 30; i++) {
		mass[i] = 1 + rand() % 1541;
	}

	a = mass[rand() % 30];//вычисляем секретные числа 
	b = mass[rand() % 30];

	std::cout << "Шерлок выбрал секретное число " << "a = " << a << std::endl << " в тоже время и Ватсон решил взять в качестве секретного числа свежий номер газеты " << " b = " << b << std::endl << std::endl;

	A = modpow(g, a, p);
	B = modpow(g, b, p);
	std::cout << "После чего они принялись вычислять свои открытые ключи, первым справился Шерлок, его ключ был равен A = " << A << "\n следом за ним, весь в штабелях с вычислениями поспел Ватсон, его ключ был равен B = " << B << std::endl;
	std::cout << "Когда ключи были вычеслены, Ватсон и Шерлок послали их друг-другу,\n как и расчитывал Мориарти, который уже подготовил план по ограблению почтальона, однако, чтобы Шерлок ни о чем не прознал, ему пришлось выслать письма заново..." << std::endl << std::endl;


	SA = modpow(B, a, p);//алиса
	SB = modpow(A, b, p);//алиса//боб

	std::cout << "Наконец получив открытые ключи Сыщики вычислили свои секретные ключи: " << "SA = " << SA << " SB = " << SB << ",\n а Мориарти сидел в окружении кипы бумаг пытаясь взломать их шифр" << std::endl;

	std::cout << std::endl << "Так Ватсон и Шерлок отдохнули и вернулись разоблачать преступную сеть Мориарти !" << std::endl;
}


int gen_prostoe_chislo()
{
	int a;
	static time_t tval = time(0);
	tval += 10;
	srand(tval);
	while (1)
	{
		int z = 0, kol = 0;
		a = 1 + rand() % 1000;
		for (int i = 2; i < a; i++)
		{
			if (a % i == 1)
				continue;
			if (a % i == 0)
			{
				z = 1;
				break;
			}
		}
		if (z == 0)
		{
			break;
		}
	}
	return a;
}

	double getPRoot(int p) {
		for (int i = 0; i < p; i++) {
			if (checkRoot(p, i)) {
				return i;
			}
		}
		return 0;
	}

bool checkRoot(int p, int g) {
	if (g == 0 || g == 1) {
		return false;
	}

	int* mass = new int[p - 1];

	int index = 0, last = 1;

	for (int i = 0; i < p - 1; i++) {
		last = (last * g) % p;
		if (contains(mass, p - 1, last)) {
			return false;
		}

		mass[index++];
	}
	delete[]mass;
	return true;
}


bool contains(int*& mass, int n, int x) {
	for (int i = 0; i < n; i++) {
		if (mass[i] != NULL) {
			if (mass[i] == x) {
				return true;
			}
		}
	}
	return false;
}