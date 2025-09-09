#ifndef AUDIO_UTIL_H
#define AUDIO_UTIL_H

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>

/*
Current idea for playing audio:
Each separate "stream" of audio (different sounds/files) gets its own process. Each process currently
loaded is 


*/


// Interface representing a specific file containing sound data which FFMPeg can 
// decode into PCM samples. Used to index every audio file the project will use
struct AudioFile{
    AVFormatContext* format_context;
    int stream_index;

    AVCodecContext* codec_context;
    SwrContext* resampler;

};
struct AudioProcess{

};


struct AudioFile* AudioFile_from_file(const char* filename);
void AudioFile_destruct(struct AudioFile* to_destroy);
int AudioFile_queue_samples(const struct AudioFile* file, unsigned int samples_to_queue, struct AudioProcess* init);


// Essentially meant to represent one file which is currently being played. 
// Holds information like which file it is and APID (audio process ID)

#include "audio_util.c"
#endif