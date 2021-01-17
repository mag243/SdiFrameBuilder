// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* Frame.cpp *#*#*#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include "SdiFrameBuilder.h"

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Frame implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Frame -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
Frame::Frame(VideoStandard Std, PixelFormat Fmt)
{
    FrameBuf = IFrameBuffer::Make(Std, Fmt);
}
Frame::Frame(VideoStandard Std, PixelFormat Fmt, size_t Size)
{
    FrameBuf = IFrameBuffer::Make(Std, Fmt, Size);
}
Frame::Frame(VideoStandard Std, PixelFormat Fmt, uint8_t* Data, size_t Size)
{
    FrameBuf = IFrameBuffer::Make(Std, Fmt, Data, Size);
}
Frame::Frame(FrameBuffer&& FrmBuf) : FrameBuf(std::move(FrmBuf))
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Clone -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void Frame::Clone(const Frame& OthFrame)
{
    Clone(OthFrame.FrameBuf);
}
void Frame::Clone(const FrameBuffer& OthBuf)
{
    FrameBuf = IFrameBuffer::Make(OthBuf->Standard(), OthBuf->PxFmt(), OthBuf->Size());
    std::memcpy(FrameBuf->Data(), OthBuf->Data(), OthBuf->Size());
}


// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Commit -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void Frame::Commit()
{
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Data -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
uint8_t* Frame::Data() const
{
    if (FrameBuf == nullptr)
        return nullptr;
    return FrameBuf->Data();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Size -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t Frame::Size() const
{
    if (FrameBuf==nullptr || FrameBuf->Data()==nullptr)
        return 0;
    return FrameBuf->Size();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Swap -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame::Swap(FrameBuffer& NewFrmBuf)
{
    FrameBuf.swap(NewFrmBuf);
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Anc_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void Frame::Anc_Get(void)
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Audio_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame::Audio_Get(void)
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Video_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame::Video_Get(Video& V) const
{
    FrameProperties  FP(FrameBuf->Standard());

    V.Lines.clear();

    V.PxFmt = FrameBuf->PxFmt();
    V.Width = FP.VideoWidth;
    V.Height = FP.VideoHeight;
    V.LineSizeInBytes = FP.LineSizeInBytes(FrameBuf->PxFmt());

    for (const auto& Fld : FP.Fields)
    {
        uint8_t* Line = FrameBuf->Data() + (V.LineSizeInBytes * (Fld.FirstLineVideo-1));
        Line += FP.LineSizeInBytes_Hanc(FrameBuf->PxFmt());
        for (size_t l=Fld.FirstLineVideo; l<=Fld.LastLineVideo; l++)
        {
            V.Lines.push_back(Line);
            Line += V.LineSizeInBytes;
            assert(Line < (FrameBuf->Data() + FrameBuf->Size()));
        }
    }
}

};  // namespace DtSdi