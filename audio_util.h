#ifndef AUDIO_UTIL_H
#define AUDIO_UTIL_H

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>

struct AudioFile{
    AVFormatContext* format_context;
    int stream_index;

    AVCodecContext* codec_context;
    SwrContext* resampler;

};

struct AudioFile* AudioFile_from_file(const char* filename);
void AudioFile_destruct(struct AudioFile* to_destroy);

#include "audio_util.c"
#endif