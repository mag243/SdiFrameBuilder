// *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* Helpers.cpp *#*#*#*#*#*#*#*#*#*#* (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include <numeric>
#include "SdiFrameBuilder.h"

using namespace std;

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Fraction implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

Fraction::Fraction(int N, int D) : Num(N), Den(D)
{
    Normalize();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Fraction::Normalize -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Fraction::Normalize()
{
    // Normalize
    if (Den == 0)
        return;
    
    const int CommonDiv = std::gcd(Num, Den);
    Num/=CommonDiv; Den/=CommonDiv;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Fraction::ToDouble -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
double Fraction::ToDouble() const
{
    return (Den==0) ? 0.0 : (double(Num)/double(Den));
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Fraction::operator== -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool Fraction::operator==(const Fraction& Oth) const
{
    if (this == &Oth)
        return true;

    // First normalize and than compare
    const Fraction NormThis(*this), NormOth(Oth);
    return (NormThis.Num==NormOth.Num && NormThis.Den==NormOth.Den);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Fraction::operator!= -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool Fraction::operator!=(const Fraction& Oth) const
{
    return !(*this == Oth);
}



};  // namespace DtSdi
