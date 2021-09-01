#include <iostream>
#include <fstream>
#include <vector>
//for utf-8
#include <windows.h>

std::vector<std::string> split(const std::string& str, char delim)
{
    std::vector<std::string> tokens;

    size_t start = 0, end = str.find(delim, start);
    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, (end - start)));
        start = end + 1;
        end = str.find(delim, start);
    }

    //Измение в исходном коде
    tokens.push_back(str.substr(start));
    //

    return tokens;
}

enum class CarColor
{
    Yellow,
    Red,
    Black,
    White,
    Blue,
    Green,
    Grey,
    Silver,
    EnumCount
};

enum class EmployeeSex
{
    Male,
    Female,
    EnumCount
};

enum class RecordType
{
    Lecture,
    Practice,
    Laboratory,
    Exam,
    EnumCount
};

struct Car
{
    unsigned number;
    std::string model;
    CarColor color;
    unsigned year;
};

std::vector<Car> sort(std::vector<Car> vCar)
{
    std::vector<Car> newVCar;
    std::vector<Car>::iterator iterMax;
    std::vector<Car>::iterator iter;
    while(!vCar.empty())
    {
        iterMax = vCar.begin();
        iter = iterMax+1;
        while(iter!=vCar.end())
        {
            if((iter->year) > (iterMax->year))
                iterMax = iter;
            iter++;
        }
        newVCar.push_back(*iterMax);
        vCar.erase(iterMax);
    }
    return newVCar;
};

std::ostream& operator<<(std::ostream& os,const Car& c)
{
    return os << c.number << ';' << c.model << ';' << (unsigned)c.color << ';' << c.year << '\n';
};

std::vector<Car> filterCar(std::vector<Car> &vCar,CarColor color,unsigned year)
{
    std::vector<Car> newVCar;
    for(Car &c : vCar)
    {
        if(c.color==CarColor::Green && c.year<(2021-year))
            newVCar.push_back(c);
    }
    return newVCar;
}


using namespace std;

int main()
{
    //utf-8
    SetConsoleOutputCP(65001);

    ifstream fin("DataVar1.txt",ios_base::in);
    if(!fin)
    {
        cout << "Файл не открыт\n";
        system("pause");
        return 1;
    }

    //Чтение
    string str;
    vector<string> stringCar;
    vector<Car> arrayCar;
    int i=0;
    while(!fin.eof())
    {
        getline(fin,str);
        //fin >> str;
        if(str.empty())
            break;
        i++;
        stringCar = split(str,';');
        Car c = {stoul(stringCar[0]),stringCar[1],static_cast<CarColor>(stoi(stringCar[2])),stoul(stringCar[3])};
        arrayCar.push_back(c);
    }
    fin.close();
    cout << i << '\n';

    ofstream fSortOut("DataSort.txt",ios_base::out);
    //Сортировка и вывод
    vector<Car> sortedCar = sort(arrayCar);
    if(fSortOut)
        for(Car &c : sortedCar)
            fSortOut << c;
    fSortOut.close();

    ofstream fFiltOut("DataFilt.txt",ios_base::out);
    //Фильтрация и вывод
    vector<Car> filtredCar = filterCar(sortedCar,CarColor::Green,4);
    if(fFiltOut)
        for(Car &c : filtredCar)
            fFiltOut << c;
    fFiltOut.close();

    system("pause");
    return 0;
}


