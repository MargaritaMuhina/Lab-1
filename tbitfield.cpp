// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw "error";
    }
    BitLen = len;
    if (len % sizeof(TELEM) == 0) {
        MemLen = len / sizeof(TELEM);
    }
    else {
        MemLen = (len / sizeof(TELEM))+1;
        
    }
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
    
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (size_t i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

}

TBitField::~TBitField()
{
    delete[] pMem;
    BitLen = 0;
    MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{   
    if (n<0 || n>BitLen) {
        throw "error";
    }
    return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n >= BitLen))
        throw "error";

    return 1 << (n %( sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen))
        throw "error";
    pMem[GetMemIndex(n)] |= GetMemMask(n);
    
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
        throw "error";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen))
        throw "error";
    return pMem[GetMemIndex(n)] & GetMemMask(n);
    
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int r = 1;
    if (BitLen != bf.BitLen) 
        r= 0;
    else for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
        {
            r = 0; break;
        }
    return r;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    int r = 0;
    if (BitLen != bf.BitLen) 
        r = 1;
    else for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
        {
            r = 1; break;
        }
    return r;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = bf.BitLen;
    if (BitLen > len) 
        len = BitLen;
    TBitField temp(len);
    for (int i = 0; i < MemLen; i++) 
        temp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++) 
        temp.pMem[i] |= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    /*int len;
    if (BitLen > bf.BitLen)
        len = BitLen;
    else
        len = bf.BitLen;
    TBitField tmp(len);
    for (int i = 0; i < MemLen; i++)
        tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        tmp.pMem[i] &= bf.pMem[i];
    return tmp;*/

    int len;
    if (BitLen > bf.BitLen)
        len = BitLen;
    else
        len = bf.BitLen;
    TBitField tmp(len);
    for (int i = 0; i < BitLen; i++) {
        
            if (GetBit(i) == bf.GetBit(i) && GetBit(i) ){
                tmp.SetBit(i);
            }
            else {
                tmp.ClrBit(i);
            }
        
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (int i = 0; i < tmp.BitLen; i++)
        if (GetBit(i) == 0) 
            tmp.SetBit(i);
        else 
            tmp.ClrBit(i);
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string temp;
    istr >> temp;
    if (temp.size() != bf.GetLength())
        throw " ";
    for (int i = 0; i < bf.GetLength(); i++) {
        if (temp[i] == '0')
            bf.ClrBit(i);
        else if (temp[i] == '1')
            bf.SetBit(i);
        else
            throw " ";
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++) {
        if (bf.GetBit(i)) 
            ostr << '1';
        else ostr << '0';
    }
    return ostr;
}
