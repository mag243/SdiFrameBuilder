// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* FrameBuilder.cpp *#*#*#*#*#*#*#*#*#* (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include "SdiFrameBuilder.h"
#include "SymbolPtr.h"

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
    const PixelFormat PxFmt = F.PxFmt_Get();
    const int LineNumSymbols = FP.LineNumSymbols();

    SymbolPtr16b_Hd PtrChrom(reinterpret_cast<uint16_t*>(F.Data()), 
                                      LineNumSymbols/2, SymbolPtr::Stream::CHROMINANCE_0);
    SymbolPtr16b_Hd PtrLuma(reinterpret_cast<uint16_t*>(F.Data()), 
                                      LineNumSymbols/2, SymbolPtr::Stream::LUMAMINANCE_0);

    const int LineSavOffset = (FP.LineNumSymEav + FP.LineNumSymHanc)/2;

    for (size_t l=0; l<FP.NumLines(); l++)
    {
        // Add EAV
        PtrChrom[0] = 0x3FF;
        PtrChrom[1] = 0x000;
        PtrChrom[2] = 0x000;

        PtrLuma[0] = 0x3FF;
        PtrLuma[1] = 0x000;
        PtrLuma[2] = 0x000;
                
        // Add SAV
        PtrChrom[LineSavOffset] = 0x3FF;
        PtrChrom[LineSavOffset+1] = 0x000;
        PtrChrom[LineSavOffset+2] = 0x000;

        PtrLuma[LineSavOffset] = 0x3FF;
        PtrLuma[LineSavOffset+1] = 0x000;
        PtrLuma[LineSavOffset+2] = 0x000;

        PtrChrom += LineNumSymbols/2;
        PtrLuma += LineNumSymbols/2;
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

};  // namespace DtSdi