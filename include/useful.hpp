#pragma once
#ifndef HPP_JSONPARSER_USEFUL
#define HPP_JSONPARSER_USEFUL


#include <string>
#include <iomanip>
#include <iostream>


template<class T>
inline std::string formatNumber(
    T value,
    int strWidth,
    int varPrecision    1,
    std::string align   = "right",
    bool numberFill     = false
) {
    std::stringstream outStream, _temp;
    int fillZeros = 0;
    if(numberFill && align=="right") {
        _temp << std::fixed;
        _temp << std::setprecision(varPrecision) << value;
        if(static_cast<int>(_temp.str().length()) < strWidth) fillZeros = strWidth - static_cast<int>(_temp.str().length());
    }
    outStream << std::fixed;
    outStream << std::boolalpha;
    if(align=="left") outStream<<std::left;
    else if(align=="right") outStream<<std::right;
    outStream << std::setw(strWidth - fillZeros);
    if(numberFill && align=="right") outStream << std::string(fillZeros, '0');
    // outStream << (align=="left"? std::left : std::right);
    outStream << std::setprecision(varPrecision) << value;

    return outStream.str();
}

template<class T>
inline std::string formatContainer(
    T _container,
    int strWidth,
    int varPrecision,
    std::string align = "right",
    bool numberFill = false,
    char openSymb   = '{',
    char closeSymb  = '}',
    char _sepSymb   = ','
) {
    std::string _out(1, openSymb);
    for(auto itr=_container.begin(); itr!=_container.end(); ++itr) {
        _out += formatNumber(*itr, strWidth, varPrecision, align, numberFill);
        if(itr!=--_container.end()) openSymb += _sepSymb;
    }
    return _out + closeSymb;
}

template<class T>
inline std::string formatVector(
    std::vector<T>  _container,
    int             _strWidth   = 0,
    int             _precision  = 1,
    std::string     _align      = "right",
    bool            _numberFill = false,
    char            _openSymb   = '{',
    char            _closeSymb  = '}',
    char            _sepSymb    = ',',
    size_t          _startIdx   = 0,
    size_t          _endIdx     = std::string::npos
) {
    std::string _out(1, _openSymb);
    size_t endIdx = (_endIdx==std::string::npos? _container.size() : _endIdx);
    for(size_t i=_startIdx; i<endIdx; i++) {
        _out += formatNumber(_container[i], _strWidth, _precision, _align, _numberFill);
        if(i<endIdx-1) _out += _sepSymb;
    }
    return _out + _closeSymb;
}

template<class T>
inline std::string formatContainer1(
    T _container,
    size_t contSize,
    int strWidth,
    int varPrecision,
    std::string align = "right",
    bool numberFill = false,
    char openSymb   = '{',
    char closeSymb  = '}',
    char _sepSymb   = ','
) {
    std::string _out(1, openSymb);
    for(size_t i=0; i<contSize; i++) {
        _out += formatNumber(_container[i], strWidth, varPrecision, align, numberFill);
        if(i<contSize-1) _out += _sepSymb;
    }
    return _out + closeSymb;
}

#endif //HPP_JSONPARSER_USEFUL