#ifndef AUDIO_UTIL_C
#define AUDIO_UTIL_C

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include "audio_util.h"

struct AudioFile* AudioFile_from_file(const char* filename){
    AVFormatContext *format_context = avformat_alloc_context();
    
    // Initialize the input file and turn it into format_context
    if(avformat_open_input(&format_context, filename, NULL, NULL) != 0) {
        fprintf(stderr, "Could not open video file: %s\n", filename);
        return NULL;
    }

    // Ensure that stream information is available
    if (avformat_find_stream_info(format_context, NULL) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        avformat_close_input(&format_context);
        return NULL;
    }

    // Find the first audio stream
    int stream_index = -1;
    for (int i = 0; i < format_context->nb_streams; i++) {
        if (format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            stream_index = i;
            break;
        }
    }

    if (stream_index == -1) {
        fprintf(stderr, "Could not find audio stream in the input file\n");
        avformat_close_input(&format_context);
        return NULL;
    }

    AVCodecParameters* codec_params = format_context->streams[stream_index]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codec_params->codec_id);

    if (!codec){
        fprintf(stderr, "Error: could not find codec for file");
        avformat_close_input(&format_context);
        return NULL;
    }

    AVCodecContext* codec_context = avcodec_alloc_context3(codec);

    if (avcodec_parameters_to_context(codec_context, codec_params) < 0){
        fprintf(stderr, "Error: could not open codec.");
        avformat_close_input(&format_context);
        avcodec_free_context(&codec_context);
        return NULL;
    }
    AVChannelLayout* layout = malloc(sizeof(AVChannelLayout));
    if (!layout){
        fprintf(stderr, "Error: allocating channel layout struct failed");
        avformat_close_input(&format_context);
        avcodec_free_context(&codec_context);
        return NULL;
    }
    if (av_channel_layout_from_string(layout, "stereo") != 0){
        fprintf(stderr, "Error: creating channel layout struct failed");
        avformat_close_input(&format_context);
        avcodec_free_context(&codec_context);
        free(layout);
        return NULL;
    }
    SwrContext* resampler = swr_alloc();
    if (!resampler){
        fprintf(stderr, "Error: could not allocate resampler");
        avformat_close_input(&format_context);
        avcodec_free_context(&codec_context);
        free(layout);
        return NULL;
    }
    swr_alloc_set_opts2(
        &resampler, 
        layout, AV_SAMPLE_FMT_S16, 44100,
        &codec_context->ch_layout, codec_context->sample_fmt, codec_context->sample_rate,
        0, NULL
    );
    
    struct AudioFile* return_val = malloc(sizeof(struct AudioFile));
    if (!return_val){
        return NULL;
    }
    return_val->format_context = format_context;
    return_val->stream_index = stream_index;
    return_val->codec_context = codec_context;
    return_val->resampler = resampler;
    return return_val;
}

void AudioFile_destruct(struct AudioFile* to_destroy){
    avformat_close_input(&to_destroy->format_context);
    avcodec_free_context(&to_destroy->codec_context);
    swr_free(&to_destroy->resampler);
    free(to_destroy);
}

#endif