// *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* SdiFrameReader.cpp *#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <iostream>
#include <fstream>
#include <vector>
#include "SdiFrameBuilder.h"
#include "SymbolPtr.h"

using namespace std;
using namespace DtSdi;

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- main -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
int main()
{
    const VideoStandard VidStd = VideoStandard::STD_1080I50;
    const PixelFormat PxFmt = PixelFormat::UYVY422_16B;

    vector<uint8_t> ExternalBuf(4*1024*1024);

    FrameBuffer FrameBuf = IFrameBuffer::Make(VidStd, PxFmt, 4*1024*1024);
    FrameBuffer FrameBuf_External = IFrameBuffer::Make(VidStd, PxFmt,
                                                  ExternalBuf.data(), ExternalBuf.size());

    Frame F(VidStd, PxFmt);
    auto ptr = F.Data();
    auto size = F.Size();
    

    Frame F2(VidStd, PxFmt, 4*1024*1024);

    Frame F3(VidStd, PxFmt, ExternalBuf.data(), ExternalBuf.size());

    Frame F4(std::move(FrameBuf_External));

    Video V;
    F.Video_Get(V);

    FrameBuilder  Builder;
    Builder.Frame_Init(F);

    //std::ofstream OutFile;
    //OutFile.open(".\\Export\\sdi_frame.hex", std::ios_base::out | std::ios_base::binary);
    //OutFile.clear();
    //OutFile.write(reinterpret_cast<char*>(F.Data()), F.Size());
    //OutFile.close();
    return 0;
}