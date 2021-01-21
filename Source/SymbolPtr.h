// *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* SymbolPtr.h *#*#*#*#*#*#*#*#*#*#* (C) 2021 DekTec
//

#pragma once

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include <stdint.h>
#include <memory>


namespace DtSdi
{

class SymbolPtr
{
    // Types
public:
    // .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- enum class Stream -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    //
    enum class Stream : size_t
    {
        SD_CHROMLUM     = 0,
        CHROMINANCE_0   = 0,
        LUMAMINANCE_0   = 1,
        CHROMINANCE_1   = 2,
        LUMAMINANCE_1   = 3,
        CHROMINANCE_2   = 4,
        LUMAMINANCE_2   = 5,
        CHROMINANCE_3   = 6,
        LUMAMINANCE_3   = 7,
    };

    // Operations
public:
    virtual void Seek(int Offset) = 0;
    virtual size_t Size() const = 0;
};


// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class SymbolPtr16b +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
template <const size_t NumStreams_T=1>
class SymbolPtr16b : public SymbolPtr
{
    // Operations
public:
    inline void Seek(int Offset) override
    {
        assert(Ptr!=nullptr && Ptr>=Start && Ptr<=End);
        assert(NumStreams_T==1 || NumStreams_T==2 || NumStreams_T==8);
        const int Delta = (Offset * NumStreams_T);
        Ptr += Delta;
        assert(Ptr!=nullptr && Ptr>=Start && Ptr<=(End+NumStreams_T));
    }
    inline size_t Size() const override
    {
        return static_cast<size_t>(End - Start) / NumStreams_T;
    }
    inline uint16_t& operator[](size_t Offset) const
    {
        Offset *= NumStreams_T;
        return PtrFirstSymbol[Offset];
    }
    inline uint16_t& operator*(void)
    {
        assert(Ptr!=nullptr && Ptr>=Start && Ptr<End);
        return *Ptr;
    }
    inline SymbolPtr16b& operator+=(int Delta)
    {
        Seek(Delta);
        return *this;
    }
    inline SymbolPtr16b& operator++()
    {
        Seek(1);
        return *this;
    }
    inline SymbolPtr16b operator++(int)
    {
        SymbolPtr16b  Temp = *this;
        ++*this;
        return Temp;
    }
    inline SymbolPtr16b& operator-=(int Delta)
    {
        Seek(-Delta);
        return *this;
    }
    inline SymbolPtr16b operator--(int)
    {
        Seek(-1);
        return *this;
    }
    inline SymbolPtr16b& operator--()
    {
        SymbolPtr16b Temp = *this;
        --*this;
        return Temp;
    }

    // Data / Attributes
protected:
    uint16_t *Start=nullptr, *End=nullptr;  // Start+end of buffer
    uint16_t *Ptr=nullptr;      // Current byte position
    uint16_t *PtrFirstSymbol=nullptr; 

    // Constructor / Destructor
public:
    SymbolPtr16b(uint16_t* Start, size_t NumSymbols, 
                                                const Stream Stream=Stream::CHROMINANCE_0)
    {
        assert(Start!=nullptr && NumSymbols>0);
        this->Start = Start;
        End = Start + (NumSymbols * NumStreams_T);
        assert(static_cast<size_t>(Stream) < NumStreams_T);
        Ptr = Start + static_cast<size_t>(Stream);
        PtrFirstSymbol = Ptr;
    }
};
using SymbolPtr16b_Sd = SymbolPtr16b<1>;
using SymbolPtr16b_Hd = SymbolPtr16b<2>;
using SymbolPtr16b_Uhd = SymbolPtr16b<8>;

};  // namespace DtSdi