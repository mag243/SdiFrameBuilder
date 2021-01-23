// *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* FrameBuilder.h *#*#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

#pragma once

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <stdint.h>
#include <vector>
#include "SymbolPtr.h"
#include "SdiFrameBuilder.h"

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class FrameBuilderImpl +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
class FrameBuilderImpl_Hd
{
    // Operations
public:
    inline void Blank(SymbolPtr16b_Hd&, size_t NumSymbols, const SymbolPtr::SymbolStream);
    void Init(const FrameProperties&);
    inline void InsertEav(SymbolPtr16b_Hd&, int LineNum);
    inline void InsertSav(SymbolPtr16b_Hd&, int LineNum);
protected:
    inline uint16_t GetXyzWord(int LineNum, bool IsEav) const;
    inline static uint16_t ComputeXyzWord(int LineNum, const FrameProperties&, bool IsEav);
    inline uint16_t ComputeXyzWord(int LineNum, bool IsEav) const;
    inline void InsertPreample(SymbolPtr16b_Hd&);

    // Data / Attributes
protected:
    FrameProperties FrameProps;     // Frame properties
    std::vector<std::pair<uint16_t, uint16_t>> XyzWords;  
                                    // Pre-computed XYZ status words per line. 
                                    // Note: first holds XYZ for EAV, and second for SAV.

    // Constructor / Destructor
public:
    FrameBuilderImpl_Hd(const FrameProperties&);
    virtual ~FrameBuilderImpl_Hd() = default;
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+ FrameBuilderImpl_Hd - Inline implementation +=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::Blank -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
inline void FrameBuilderImpl_Hd::Blank(
           SymbolPtr16b_Hd& Syms, size_t NumSymbols, const SymbolPtr::SymbolStream Stream)
{
    const uint16_t BLANK_SYMBOL = Stream==SymbolPtr::SymbolStream::CHROM_0 ? 0x80 : 0x200;
    for (size_t n=0; n<NumSymbols; n++)
        *Syms++ = BLANK_SYMBOL;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::InsertEav -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
inline void FrameBuilderImpl_Hd::InsertEav(SymbolPtr16b_Hd& Syms, int LineNum)
{
    InsertPreample(Syms);
    // Insert status word
    *Syms++ = GetXyzWord(LineNum, true);
    // Insert line number (LN0 + LN1)
    *Syms++ = ((LineNum&0x40)==0 ? 0x200 : 0x000) | ((LineNum&0x07F)<<2);
    *Syms++ = 0x200 | ((LineNum>>5)&0x3C);
    // Insert CRC (just a place holder, hardware will compute actual CRC)
    *Syms++ = 0x200;
    *Syms++ = 0x200;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::InsertSav -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
inline void FrameBuilderImpl_Hd::InsertSav(SymbolPtr16b_Hd& Syms, int LineNum)
{
    InsertPreample(Syms);
    // Insert status word
    *Syms++ = GetXyzWord(LineNum, false);
}

// -.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::InsertPreample -.-.-.-.-.-.-.-.-.-.-.-.-
//
inline void FrameBuilderImpl_Hd::InsertPreample(SymbolPtr16b_Hd& Syms)
{
    // Insert a preamble
    *Syms++ = 0x3FF;
    *Syms++ = 0x000;
    *Syms++ = 0x000;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::GetXyzWord -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
inline uint16_t FrameBuilderImpl_Hd::GetXyzWord(int LineNum, bool IsEav) const
{
    assert(LineNum>=1 && LineNum<=XyzWords.size());
    const size_t Index = static_cast<size_t>(LineNum)-1;
    return IsEav ? XyzWords[Index].first : XyzWords[Index].second;
}

// -.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::ComputeXyzWord -.-.-.-.-.-.-.-.-.-.-.-.-
//
inline uint16_t FrameBuilderImpl_Hd::ComputeXyzWord(
                                       int LineNum, const FrameProperties& FP, bool IsEav)
{
    // Init status word (b9='1', b1='0', b0='0')
    uint16_t  Xyz = 0x200;
    
    // Set field bit (b8)
    Xyz |= (FP.Line2Field(LineNum) == 2) ? 0x100 : 0x000;

    // Set V-sync flag (b7)
    Xyz |= FP.IsVanc(LineNum) ? 0x080 : 0x000;
    
    // Set H-sync flag (b6)
    Xyz |= IsEav ? 0x040 : 0x000;

    // Set protection bit 3 (b5): b6 ^ b7
    Xyz |= (Xyz & 0x040)>>1 ^ (Xyz & 0x080)>>2;
    // Set protection bit 2 (b4): b6 ^ b8
    Xyz |= (Xyz & 0x040)>>2 ^ (Xyz & 0x100)>>4;
    // Set protection bit 1 (b3): b7 ^ b8
    Xyz |= (Xyz & 0x080)>>4 ^ (Xyz & 0x100)>>5;
    // Set protection bit 0 (b2): b6 ^ b7 ^ b8
    Xyz |= (Xyz & 0x040)>>4 ^ (Xyz & 0x080)>>5 ^ (Xyz & 0x100)>>6;

    return Xyz;
}
inline uint16_t FrameBuilderImpl_Hd::ComputeXyzWord(int LineNum, bool IsEav) const
{
    return ComputeXyzWord(LineNum, FrameProps, IsEav);
}


}; // namespace DtSdi
