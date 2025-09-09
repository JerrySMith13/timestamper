#include <stdio.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

#include "audio_util.h"
#include "video_util.h"


int main(int argc, char *argv[]) {

    if (argc != 2){
        fprintf(stderr, "Usage: %s <filename>", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    avformat_network_init();

    struct AudioFile* audio_file = AudioFile_from_file(filename);
    AudioFile_destruct(audio_file);

    avformat_network_deinit();
}
