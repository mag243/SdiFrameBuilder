// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* FrameBuilder.cpp *#*#*#*#*#*#*#*#*#* (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include "SdiFrameBuilder.h"
#include "FrameBuilder.h"

using namespace std;

namespace DtSdi
{

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilder::Anc_Add -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void FrameBuilder::Anc_Add(void)
{
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilder::Audio_Add -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void FrameBuilder::Audio_Add(void)
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilder::Frame_Init -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void FrameBuilder::Frame_Init(Frame& F)
{
    const FrameProperties FP = F.Props_Get();
    FrameBuilderImpl_Hd  Impl(FP);

    static const vector<SymbolPtr::SymbolStream> SymbolStreams = 
    {
        SymbolPtr::SymbolStream::CHROM_0,
        SymbolPtr::SymbolStream::LUMA_0,
    };
    static const size_t NUM_STREAMS = SymbolStreams.size();

    for (const auto& S : SymbolStreams)
    {
        SymbolPtr16b_Hd Syms(reinterpret_cast<uint16_t*>(F.Data()), FP.NumSymbols_Get(), S);
        for (int l=0; l<static_cast<int>(FP.NumLines_Get()); l++)
        {
            Impl.InsertEav(Syms, l+1);
            Impl.Blank(Syms, FP.LineNumSymHanc/NUM_STREAMS, S);
            Impl.InsertSav(Syms, l+1);
            Impl.Blank(Syms, FP.LineNumSymVanc/NUM_STREAMS, S);
        }
    }
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilder::Video_Add -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void FrameBuilder::Video_Add(void)
{
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilder::Make -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void FrameBuilder::Make(Frame& F)
{
}

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+ FrameBuilderImpl_Hd implementation +=+=+=+=+=+=+=+=+=+=+=+=+=
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// .-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::FrameBuilderImpl_Hd -.-.-.-.-.-.-.-.-.-.-.-
//
FrameBuilderImpl_Hd::FrameBuilderImpl_Hd(const FrameProperties& FP) : FrameProps(FP) 
{
    Init(FP);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBuilderImpl_Hd::Init -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void FrameBuilderImpl_Hd::Init(const FrameProperties& FP)
{
    XyzWords.clear();
    for (int Line=1; Line<=static_cast<int>(FP.NumLines_Get()); Line++)
    {
        XyzWords.emplace_back(ComputeXyzWord(Line, FP, true), 
                                                         ComputeXyzWord(Line, FP, false));
    }
    // Store properties
    FrameProps = FP;
}


};  // namespace DtSdi