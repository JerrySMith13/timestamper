#ifndef VIDEO_UTIL_H
#define VIDEO_UTIL_H

struct VideoFile{
    AVFormatContext* format_context;
    int stream_index;

    AVCodecContext* codec_context;
};

#include "video_util.c"


#endif