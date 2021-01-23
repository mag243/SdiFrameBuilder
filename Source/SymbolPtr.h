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
    // -.-.-.-.-.-.-.-.-.-.-.-.-.-.- enum class SymbolStream -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
    //
    enum class SymbolStream : size_t
    {
        ALL      = 0,
        CHROM_0  = 0,
        LUMA_0   = 1,
        CHROM_1  = 2,
        LUMA_1   = 3,
        CHROM_2  = 4,
        LUMA_2   = 5,
        CHROM_3  = 6,
        LUMA_3   = 7,
    };

    // Operations
public:
    virtual void Seek(int64_t Offset) = 0;
    virtual size_t NumSymbols_Get() const = 0;
    virtual size_t NumSymbolsStream_Get() const = 0;
};


// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class SymbolPtr16b +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
template <const size_t NUM_STREAMS_T=1>
class SymbolPtr16b : public SymbolPtr
{
    // Operations
public:
    inline void Seek(int64_t Offset) override
    {
        // Move position
        const size_t SymbolOffset = PositionToSymbolOffset(Pos);
        Pos = std::min(SymbolOffsetToPosition(SymbolOffset+Offset), NumSymbols-1);
    }
    inline size_t NumSymbols_Get() const override
    {
        return NumSymbols;
    }
    inline size_t NumSymbolsStream_Get() const override
    {
        size_t NumSymbolsOfStream = (NumSymbols / NUM_STREAMS_T);
        if ((NumSymbols%NUM_STREAMS_T)>OffsetToFirst)
            NumSymbolsOfStream += 1;
        return NumSymbolsOfStream;
    }
    inline size_t PositionToSymbolOffset(const size_t Position) const
    {
        assert(Position >= OffsetToFirst);
        assert(NUM_STREAMS_T==1 || NUM_STREAMS_T==2 || NUM_STREAMS_T==8);
        const size_t SymbolOffset = (Position-OffsetToFirst) / NUM_STREAMS_T;
        return SymbolOffset;
    }
    inline size_t SymbolOffsetToPosition(const size_t SymbolOffset) const
    {
        assert(NUM_STREAMS_T==1 || NUM_STREAMS_T==2 || NUM_STREAMS_T==8);
        assert(SymbolOffset <= NumSymbolsStream_Get());
        const size_t Position = ((SymbolOffset*NUM_STREAMS_T) + OffsetToFirst);
        return Position;
    }
    inline uint16_t& operator[](size_t Offset) const
    {
        return Syms[SymbolOffsetToPosition(Offset)];
    }
    inline uint16_t& operator*(void)
    {
        assert(Syms != nullptr);
        return Syms[Pos];
    }
    inline SymbolPtr16b& operator+=(int64_t Delta)
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
    inline SymbolPtr16b& operator-=(int64_t Delta)
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
    uint16_t* Syms=nullptr; // Points to buffer with interleaved symbols (all streams)
    size_t NumSymbols=0;    // Size of buffer in number of symbols
    size_t Pos=0;           // Current position in buffer
    size_t OffsetToFirst=0; // Offset to first symbol of the stream type

    // Constructor / Destructor
public:
    SymbolPtr16b(uint16_t* Syms, size_t NumSymbols, 
                                          const SymbolStream Stream=SymbolStream::CHROM_0)
        : Syms(Syms),
          NumSymbols(NumSymbols)
    {
        assert(Syms!=nullptr && NumSymbols>0);
        assert((NumSymbols%NUM_STREAMS_T) == 0);
        assert(static_cast<size_t>(Stream) < NUM_STREAMS_T);
        // Move to position of first symbol 
        Pos = OffsetToFirst = static_cast<size_t>(Stream);
    }
};
using SymbolPtr16b_Sd = SymbolPtr16b<1>;
using SymbolPtr16b_Hd = SymbolPtr16b<2>;
using SymbolPtr16b_Uhd = SymbolPtr16b<8>;

};  // namespace DtSdi