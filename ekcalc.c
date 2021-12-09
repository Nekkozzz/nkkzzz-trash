#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct answer {  // создание структуры answer и объявление типа данных Answer
    double value;
    double error;
    int count;
} Answer;

long long factorial(int n) { // функция нахождения факториала
	return (n < 2) ? 1 : n * factorial(n - 1);  // тернарый оператор 
}

Answer sinTalor(double x, int N, double eps, double* etalon) {  // нахождение синуса по ряду тейлора
	int i;
    Answer result;
    result.value = 0;
    *etalon = sin(x);
	for (i = 0; i < N; i++) {
		result.value += pow(-1, i) * pow(x, 2 * i + 1) / (double)factorial(2 * i + 1);
		if (fabs(*etalon - result.value) < eps) break;
	}
    result.error = fabs(*etalon - result.value);
    result.count = i;
	return result;
}

Answer cosTalor(double x, int N, double eps, double* etalon) {  // нахождение косинуса по ряду тейлора
	int i;
    Answer result;
    result.value = 0;
    *etalon = cos(x);
	for (i = 0; i < N; i++) {
		result.value += pow(-1, i) * pow(x, 2 * i) / (double)factorial(2 * i);
		if (fabs(*etalon - result.value) < eps) break;
	}
	result.error = fabs(*etalon - result.value);
    result.count = i;
	return result;
}

Answer expTalor(double x, int N, double eps, double* etalon) {  // нахождение экспоненты по ряду тейлора
	int i;
    Answer result;
    result.value = 0;
    *etalon = exp(x);
	for (i = 0; i < N; i++) {
		result.value += pow(x, i) / (long double) factorial(i);
		if (fabs(*etalon - result.value) < eps) break;
	}
	result.error = fabs(*etalon - result.value);
    result.count = i;
	return result;
}

Answer cscTalor(double x, int N, double eps, double* etalon) {   // нахождение косеканса по ряду тейлора ( 1 / sin(x) )
	int i;
    Answer result;
    result.value = 0;
    *etalon = sin(x);
	for (i = 0; i < N; i++) {
		result.value += pow(-1, i) * pow(x, 2 * i + 1) / (double)factorial(2 * i + 1);
		if (fabs(*etalon - result.value) < eps) break;
	}
    *etalon = 1 / *etalon;
    result.value = 1 / result.value; 
    result.error = fabs(*etalon - result.value);
    result.count = i;
	return result;
}

void functions(Answer* answer, double x, int func, int n, double* etalon, double eps) {  // функция с функциями
	switch (func) {
	case 1:
		*answer = sinTalor(x, n, eps, etalon);
		break;
	case 2:
		*answer = cosTalor(x, n, eps, etalon);
		break;
	case 3:
		*answer = expTalor(x, n, eps, etalon);
		break;
    case 4:
        *answer = cscTalor(x, n, eps, etalon);
        break;
	default:
		break;
	}
}

int main() {
    Answer answer;
    double etalon;
    double eps = 0.000001;

    void (*funcs)(Answer*, double, int, int, double*, double);  // указатель на функцию с функциями
    funcs = functions;

    printf("Mode 1 (single) 2 (multi): ");  // выбор режима работы
    int mode;
    while (1) {
        scanf("%d", &mode);
        if (mode != 1 && mode != 2) printf("1 or 2: ");
        else break;
    }
    printf("Func 1 (sin) 2 (cos) 3 (exp) 4 (csc): ");  // выбор функции
    int func;
    while (1) {
        scanf("%d", &func);
        if (func < 1 || func > 4) printf("1 2 3 or 4: ");
        else break;
    }
    printf("x from -1 to 1: ");  // выбор точки
    double x;
    while (1) {
        scanf("%lf", &x);
        if (x < -1 || x > 1) printf("from -1 to 1: ");
        else break;
    }
    switch (mode) {  // режимы работы
    case 1:  // одиночный
        printf("n form 1 to 100: ");  // выбор максимального количества слагаемых
        int n;
        while (1) {
            scanf("%d", &n);
            if (n < 1 || n > 100) printf("from 1 to 100: ");
            else break;
        }
        funcs(&answer, x, func, n, &etalon, eps);  // вызов функции с функциями
        printf("etalon: %.12lf\nfunction: %.12lf\nerror: %.12lf\ncount: %d",   // вывод ответа
                etalon, answer.value, answer.error, answer.count);
        break;
    case 2:  // таблица
        printf("amount of experiments from 1 to 999: ");  // количество экспериментов (строк таблицы)
        int nexp;
        while (1) {
            scanf("%d", &nexp);
            if (nexp < 1 || nexp > 999) printf("from 1 to 999: ");
            else break;
        }
        printf("    | %-15s| %-15s| %-15s| %-s |\n", "etalon", "function", "error", "count");
        for (int i = 0; i < nexp; i++) {   // вывод таблицы (красивый)
            n = i + 1;
            eps = 1;
            funcs(&answer, x, func, n, &etalon, eps);
            printf("%3d | %.12lf | %.12lf | %.12lf | %-5d |\n",
                    i+1, etalon, answer.value, answer.error, answer.count);
        }
        break;
    }
}