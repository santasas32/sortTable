#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void readFile(ifstream& fin, char bortNumber[255], char reisNumber[255], char markFA[255], char time[255]); //прототипы функций

void bubbleSort(int k, int NumberArr[255]);

int srez(char reisNumber[255]);

void checkData(char bortNumber[255], char reisNumber[255], char time[255], int errorsReturn[255]);

int getCharLen(char charArr[255]);

int getIntLen(int intArr[255]);

void echoPrintTable(ifstream& fin, char bortNumber[255],char reisNumber[255],char markFA[255],char time[255],int k, int arrNumberErrStr[255], int lengthArrNumberErrStr);

void sortPrintTable(ifstream& fin, char bortNumber[255], char reisNumber[255], char markFA[255], char time[255], int nek, int noErrNumberArr[255]);

int main()
{
    setlocale(LC_ALL, "rus");

    ifstream fin;                 //подключение
    fin.open("text.txt");         //файла

    char bortNumber[255];
    char reisNumber[255];
    int errorsReturn[255];
    int fullErrorsReturn[255];
    int number;                         //
    int numberArr[255];                 //инициализация 
    int noErrNumberArr[255];            //переменных
    char markFA[255];                   //
    char time[255];
    int k = 0;
    int nek = 0;
    int numberErrStr = 0;
    int arrNumberErrStr[255];
    int errorNum = 0;
    int lengthArrNumberErrStr = 0;

    while (fin.peek() != ' ') {                                 //цикл пока файл не кончится
        
        readFile(fin, bortNumber, reisNumber, markFA, time);    //считываем строку из файла

        number = srez(reisNumber);                              //обрезаем и переводим в целочисленный тип нужные нам для сортировки данные
        numberErrStr++;                             //переменная-счётчик кол-ва строк с ошибками
         
        checkData(bortNumber, reisNumber, time, errorsReturn);  //проверка исходных данных

        for (int i = 0; i <= getIntLen(errorsReturn); i++) {    //цикл вывода ошибок на экран
            errorNum = errorsReturn[i];
            if (errorNum != 0) {
                cout << "Некорректные исходные данные в строке " << numberErrStr << "\n";
                cout << "Ошибка ";
                switch (errorNum)
                {
                case 1:cout << "формата времени!\n"; break;
                case 2:cout << "формата бортового номера!\n"; break;
                case 3:cout << "цифровой части бортового номера!\n"; break;
                case 4:cout << "формата номера рейса!\n"; break;
                case 5:cout << "цифровой части номера рейса!\n"; break;
                case 6:cout << "длины номера рейса(некорректная форма или цифровая часть)!\n"; break;
                default: cout << "неизвестная ошибка!\n"; break;
                }
            }
        }

        if (errorsReturn[0] != 0) {                                 //
            arrNumberErrStr[lengthArrNumberErrStr] = numberErrStr;  //заполнение массива строк, в которых есть ошибки
            lengthArrNumberErrStr++;                                //
        }
        else {
            noErrNumberArr[nek] = number;       //заполнение массива строк, 
            nek++;                              //в которых нет ошибок
        }

        k++;        //счётчик строк с ошибками

    }
    fin.close();    //закрываем файл

    echoPrintTable(fin, bortNumber, reisNumber, markFA, time, k, arrNumberErrStr, lengthArrNumberErrStr);   //печатаем исходную таблицу с выделением строк, в которых некорректные данные
    
    bubbleSort(nek, noErrNumberArr);    //сортируем массив цифровых частей номеров рейсов
    
    cout << "\n\n\nОтсортированная по цифровой части номера рейса таблица: \n";
    sortPrintTable(fin, bortNumber, reisNumber, markFA, time, nek, noErrNumberArr);     //выводим готовую таблицу
}

void readFile(ifstream& fin, char bortNumber[255], char reisNumber[255], char markFA[255], char time[255]) {
    fin >> bortNumber;
    fin >> reisNumber;  //считывааем данные
    fin >> markFA;      //из файла в каждую переменную
    fin >> time;
}

void bubbleSort(int nek, int noErrNumberArr[255]) {
    int temp;           //временная переменная
    int max_index;      //максимальный индекс
    while (nek != 0) {  //цикл пока "длина" массива не будет равна нулю
        max_index = 0;
        for (int i = 1; i < nek; i++) { //цикл по всей длинне
            if (noErrNumberArr[i - 1] > noErrNumberArr[i]) { //условие для выдвижения максимального элемента в конец
                temp = noErrNumberArr[i - 1];
                noErrNumberArr[i - 1] = noErrNumberArr[i];
                noErrNumberArr[i] = temp;
                max_index = i;
            }
        }
        nek = max_index;
    }
}

int srez(char reisNumber[255]) {
    int number;
    number = ((reisNumber[4] - 48) * 1000) + ((reisNumber[5] - 48) * 100) + ((reisNumber[6] - 48) * 10) + (reisNumber[7] - 48);
    return number;
}

void checkData(char bortNumber[255], char reisNumber[255], char time[255], int errorsReturn[255]) {
    int i = 0;
    if ((((time[0] - 48) * 10) + (time[1] - 48)) > 24 || (time[2] != ':') || ((((time[3] - 48) * 10) + (time[4] - 48)) >= 60)){
        errorsReturn[i] = 1;
        i++;
    }
    if (bortNumber[0] != 'Б' || bortNumber[1] != '-') {
        errorsReturn[i] = 2;
        i++;
    }
    for (int j = getCharLen(bortNumber)-3; j < getCharLen(bortNumber); j++) {
        if (not(isdigit(bortNumber[j]))) {
            errorsReturn[i] = 3;
            i++;
        }
    }
    /*if (getCharLen(bortNumber) != 6) {
        errorsReturn[i] = 3;
        i++;
    }*/
    if (reisNumber[0] != 'Р' || reisNumber[1] != 'Е' || reisNumber[2] != 'Й' || reisNumber[3] != 'С') {
        errorsReturn[i] = 4;
        i++;
    }
    int k = 0;
    for (int j = getCharLen(reisNumber)-3; j < getCharLen(reisNumber); j++) {
        k++;
        if (not(isdigit(reisNumber[j])) || k > 4) {
            errorsReturn[i] = 5;
            i++;
        }
    }
    /*if (getCharLen(reisNumber) != 8) {
        errorsReturn[i] = 6;
        i++;
    }*/
    if (getCharLen(time) != 5) {
        errorsReturn[i] = 1;
        i++;
    }
    errorsReturn[i] = 0;
   
}

int getCharLen(char charArr[255]) {
    int i, count;
    char symb;
    i = 0;
    count = 0;
    symb = charArr[i];
    while (symb != '\0') {
        i++;
        count++;
        symb = charArr[i];
    }
    return count;
}

int getIntLen(int intArr[255]) {
    int i, count;
    char symb;
    i = 0;
    count = 0;
    symb = intArr[i];
    while (symb != '\0') {
        i++;
        count++;
        symb = intArr[i];
    }
    return count;
}

void echoPrintTable(ifstream& fin, char bortNumber[255], char reisNumber[255], char markFA[255], char time[255], int k, int arrNumberErrStr[255], int lengthArrNumberErrStr) {
    cout << "\nИсходная таблица : \n";
    fin.open("text.txt");
    readFile(fin, bortNumber, reisNumber, markFA, time);
    cout << "--------------------------------------------------------------------\n"
            "| № | бортовой номер | номер рейса | марка ЛА | время входа в зону |\n"
            "--------------------------------------------------------------------\n";
    int i = 0;
    int ci = i;
    while (i != k) {
        bool flag = true;
        for (int j = 0; j < lengthArrNumberErrStr; j++) {
            if (i + 1 == arrNumberErrStr[j]) {
                flag = false;
                cout << "\033[3;43;37m| " << i + 1 << " |" << setw(11) << bortNumber << setw(6) << "|" << setw(11) << reisNumber << "  |" << setw(9) << markFA << setw(2) << "|" << setw(12) << time << setw(14) << "|\033[0m\n";
                readFile(fin, bortNumber, reisNumber, markFA, time);

                if (i == k) {
                    break;
                }
            }
        }
        if (flag == true) {
            if (i + 1 != arrNumberErrStr[-1]) {
                cout << "| " << i + 1 << " |" << setw(11) << bortNumber << setw(6) << "|" << setw(11) << reisNumber << "  |" << setw(9) << markFA << setw(2) << "|" << setw(12) << time << setw(10) << "|\n";
                readFile(fin, bortNumber, reisNumber, markFA, time);

                if (i == k) {
                    break;
                }
            }
        }
        i++;
    }
    cout << "--------------------------------------------------------------------\n";
    fin.close();
}

void sortPrintTable(ifstream& fin, char bortNumber[255], char reisNumber[255], char markFA[255], char time[255], int nek, int noErrNumberArr[255]) {
    cout << "--------------------------------------------------------------------\n"
        "| № | бортовой номер | номер рейса | марка ЛА | время входа в зону |\n"
        "--------------------------------------------------------------------\n";

    fin.open("text.txt");
    int f = 0;
    reisNumber[0] = '-1';
    while (f != nek) {

        if (srez(reisNumber) == noErrNumberArr[f]) {
            cout << "| " << f + 1 << " |" << setw(11) << bortNumber << setw(6) << "|" << setw(11) << reisNumber << "  |" << setw(9) << markFA << setw(2) << "|" << setw(12) << time << setw(10) << "|\n";
            f++;
            fin.close();
            fin.open("text.txt");
        }

        readFile(fin, bortNumber, reisNumber, markFA, time);

    }

    cout << "--------------------------------------------------------------------\n";

}