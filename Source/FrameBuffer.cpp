// *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* FrameBuffer.cpp *#*#*#*#*#*#*#*#*#* (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include "SdiFrameBuilder.h"

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+ IFrameBuffer implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- IFrameBuffer::Make -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
FrameBuffer IFrameBuffer::Make(VideoStandard Std, PixelFormat Fmt)
{
    FrameProperties  FP(Std);
    return Make(Std, Fmt, FP.SizeInBytes(Fmt));
}
FrameBuffer IFrameBuffer::Make(VideoStandard Std, PixelFormat Fmt, size_t Size)
{
    return std::make_unique<FrameBufferImpl>(Std, Fmt, Size);
}
FrameBuffer IFrameBuffer::Make(
                           VideoStandard Std, PixelFormat Fmt, uint8_t* Data, size_t Size)
{
    return std::make_unique<FrameBufferImpl_FromExternal>(Std, Fmt, Data, Size);
}

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+ FrameBufferImpl implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// .-.-.-.-.-.-.-.-.-.-.-.-.- FrameBufferImpl::FrameBufferImpl -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
FrameBufferImpl::FrameBufferImpl(VideoStandard Std, PixelFormat Fmt, size_t FrameSize)
    : IFrameBuffer(Std, Fmt)
{
    TheBuf.resize(FrameSize);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBufferImpl::Data -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
uint8_t* FrameBufferImpl::Data()
{
    return TheBuf.data();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameBufferImpl::Size -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
size_t FrameBufferImpl::Size() const
{
    return TheBuf.size();
}

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+ FrameBufferImpl_FromExternal implementation +=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// -.-.-.-.-.-.- FrameBufferImpl_FromExternal::FrameBufferImpl_FromExternal -.-.-.-.-.-.-.
//
FrameBufferImpl_FromExternal::FrameBufferImpl_FromExternal(
                           VideoStandard Std, PixelFormat Fmt, uint8_t* Data, size_t Size)
    : IFrameBuffer(Std, Fmt),
      FrameData(Data),
      FrameSize(Size)
{
    
}

// -.-.-.-.-.-.-.-.-.-.-.-.- FrameBufferImpl_FromExternal::Data -.-.-.-.-.-.-.-.-.-.-.-.-.
//
uint8_t* FrameBufferImpl_FromExternal::Data()
{
    return FrameData;
}

// -.-.-.-.-.-.-.-.-.-.-.-.- FrameBufferImpl_FromExternal::Size -.-.-.-.-.-.-.-.-.-.-.-.-.
//
size_t FrameBufferImpl_FromExternal::Size() const
{
    return FrameSize;
}

};  // namespace DtSdi
