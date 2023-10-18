#include <iostream>
#include <fstream>
#include <ios>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

typedef int* pint;

//Введення розміру масиву з перевіркою від 0 до макс. розміру
int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0;
    do {
        cout << " Input size Array ( 0< 1 < " << sizeMax << " ) ";
        cin >> size;
    } while (size <= 0 || size >= sizeMax);
    return size;
}

//Заповнення масиву вручну
int ConsoleInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> A[i];
    }
    return size;
}

//Заповнення масиву випадковими числами з введеням розміру масива вручну
int RndInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1 = 0, r2 = 0;
    srand(size);

    for (int i = 0; i < size; i++) {
        r1 = rand();
        r2 = rand();
        A[i] = 100.0 * r1;
        A[i] = A[i] / (1.0 + r2);
        cout << A[i] << "   ";
    }
    return size;
}

//Заповнення динамічного масиву руками
int ConsoleInputDynamicArrayNew(int sizeMax, pint& pA)
{
    int size = ConsoleInputSizeArray(sizeMax);
    pA = new int[size];
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> pA[i];
    }
    return size;
}

//Заповнення вектора руками
void ConsoleInputVector(int sizeMax, vector<double>& A)
{
    int size = ConsoleInputSizeArray(sizeMax);
    double d;
    for (int i = 0; i < size; i++) {
        cout << " Array[ " << i << "] "; cin >> d; A.push_back(d);
    }
    return;
}

//Заповнення вектору випадковими числами з введеням розміру масива вручну
vector<int> RndInputVector(int sizeMax) {
    srand(time(NULL));
    vector<int> arr;
    int size = ConsoleInputSizeArray(sizeMax);
    for (int i = 0; i < size; i++) {
        arr.push_back(rand() % 20 - 10);
    }
    return arr;
}

//Запис масиву в файл
void WriteArrayTextFile(int n, int* arr, const char* fileName)
{
    ofstream fout(fileName);
    if (fout.fail()) return;
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout.close();
}

//Зчитування масиву з файлу
int ReadArrayTextFile(int n, double* arr, const char* fileName)
{
    int size;
    ifstream fin(fileName);
    if (fin.fail()) return 0;
    fin >> size;
    if (size <= 0) return 0;
    if (size > n) size = n;
    for (int i = 0; i < n; i++)
        fin >> arr[i];
    fin.close();
    return size;
}

//Запис в бін файл
void WriteArrayBinFile(int n, double* arr, const char* fileName)
{
    //ios_base
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;
    bfout.write((const char*)&n, sizeof(int));
    std::streamsize  cn = static_cast<std::streamsize>(n) * sizeof(double);
    bfout.write((const char*)arr, cn);
    bfout.close();
}

//Читання бін файлу
int ReadArrayBinFile(int n, double* arr, const char* fileName)
{
    int size = 0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) return 0;
    bfin.read((char*)&size, sizeof(int));
    if (size <= 0) return 0;
    if (size > n) size = n;
    bfin.read((char*)arr, static_cast<std::streamsize>(size) * sizeof(double));
    bfin.close();
    // ssdhs
    return size;
}

//Вивід меню завдань
void ShowMainMenu()
{
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";
    cout << "    5.  Exit  \n";
}

//17. Задано одновимірний масив А розміру N. Обчислити різницю суми додатних та суми від’ємних елементів масиву
void Task1() {
    int N = 1000, psum = 0, msum = 0;
    vector<int> A = RndInputVector(N);
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
        if (A[i] > 0) {
            psum += A[i];
        }
        else {
            msum += A[i];
        }
    }
    cout << endl << "Difference:  " << psum - msum << endl;
    system("pause");
}

/*Зауваження. При розв’язуванні використати змінну(або декілька змінних) типу
вказівник, яка би вказувала поточний елемент масиву(або на деякий елемент масиву), що
розглядається (у приклад 5 змінна – вказівник pC вказує на поточний елемент масиву C).
Заданий одномірний масив цілих чисел А розміру N.
17. Знайти значення максимального елемента серед елементів, кратних k1 і
розташованих до першого від’ємного елемента.*/
void Task2() {
    int size_max = 1000, k1;
    pint pA;
    int N = ConsoleInputDynamicArrayNew(size_max, pA);
    cout << "k1: " << endl;
    cin >> k1;
    double maxElement = -numeric_limits<double>::infinity(); // Початкове значення максимального елемента
    for (int i = 0; i < N; i++) {
        if (pA[i] % k1 == 0) {
            // Якщо елемент кратний k1, порівнюємо його з поточним максимумом
            if (pA[i] > maxElement) {
                maxElement = pA[i]; // Оновлюємо максимальний елемент
            }
        }
        else if (pA[i] < 0) {
            break; // Виходимо з циклу, якщо знайдено від'ємний елемент
        }
    }
    if (maxElement == -numeric_limits<double>::infinity()) {
        cout << "There are no multiple elements in the array " << k1 << "." << endl;
    }
    else {
        cout << "Max element: " << maxElement << endl;
    }

    WriteArrayTextFile(N, pA, "array.txt");//запис масиву в файл
    system("pause");
}

/*17. Задано масив цілих чисел
A(n), n <= 400 , які можуть повторюватися. Розробити
програму, яка відбирає з кожної групи рівних чисел по одному, і утворює новий масив
B(n) та друкує його по сім чисел у рядку*/
void Task3() {
    int size_max = 401, k = 0;
    vector<int> A = RndInputVector(size_max);
    vector<int> B;

    // Вивід масиву A
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl << endl;

    // Перевірка та створення вектора B
    for (int i = 0; i < A.size() - 1; i++) {
        if (A[i] == A[i + 1]) {
            k++;
        }
        if (A[i] != A[i + 1] && k >= 1) {
            B.push_back(A[i]);
            k = 0;
        }
    }

    // Вивід масиву B по 7 чисел у рядку
    for (int i = 0; i < B.size(); i++) {
        cout << B[i] << " ";
        if ((i + 1) % 7 == 0) {
            cout << endl;
        }
    }
    cout << endl << endl;
    A.clear();
    B.clear();
    system("pause");
}

//Вибір завданя
void TaskSelect()
{
    char ch = '5';
    do {
        system("cls");
        ShowMainMenu();
        ch = getchar();
        getchar();
        switch (ch) {
        case '1': cout << " Task 1:\n "; Task1(); break;
        case '2': cout << " Task 2:\n "; Task2(); break;
        case '3': cout << " Task 3:\n "; Task3(); break;
        case '5': return;
        }
        cout << " Press any key and enter\n";
        ch = getchar();
    } while (ch != 27); //27 = escape

}


int main()
{
    TaskSelect();
    return 1;
}