// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower (bf.GetLength()), BitField(bf){}

TSet::operator TBitField()
{
    TBitField temp(this->BitField);
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((Elem < 0) || (Elem > MaxPower))
    {
        throw("error ");
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if ((Elem < 0) || (Elem > MaxPower))
    {
        throw("error");
    }
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if ((Elem < 0) || (Elem > MaxPower))
    {
        throw("error");
    }
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.GetMaxPower();
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int len;
    if (MaxPower > s.MaxPower)
        len = MaxPower;
    else
        len = s.MaxPower;
    TSet temp(len);
    temp.BitField = BitField | s.BitField;
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem > MaxPower)
    {
        throw("error");
    }
    TSet temp(*this);
    temp.BitField.SetBit(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem > MaxPower)
    {
        throw("error");
    }
    TSet temp(*this);
    temp.BitField.ClrBit(Elem);
    return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int len;
    if (MaxPower > s.MaxPower)
        len = MaxPower;
    else
        len = s.MaxPower;
    TSet temp(len);
    temp.BitField = BitField & s.BitField;
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(MaxPower);
    temp.BitField = ~BitField;
    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int elem;
    while (istr >> elem) {
        if (elem >= s.MaxPower)
            throw runtime_error("error");
        s.InsElem(elem);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.MaxPower; ++i)
    {
        if (s.BitField.GetBit(i))
            ostr << i;
        if (i + 1 < s.MaxPower) ostr << " ";

    }
    return ostr;
}
