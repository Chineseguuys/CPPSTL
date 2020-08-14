#include <iostream>



struct Double_ref
{
    double __d;
};


struct fraction
{
    unsigned int _Denomi;
    unsigned int _Molecu;

    fraction(unsigned int __d, unsigned int __m)
        : _Denomi(__d), _Molecu(__m) {}
    
    operator double() 
    {return static_cast<double>(_Molecu) / static_cast<double>(_Denomi);}

    operator Double_ref()
    {
        Double_ref __t;
        __t.__d = double(*this);    // unsing operator double() 
        return __t;
    }
};



int main()
{
    fraction ans(4, 3);
    Double_ref d_ref = Double_ref(ans);
    std::cout << double(ans) << '\n';
    std::cout << d_ref.__d << '\n';
    return 0;
}