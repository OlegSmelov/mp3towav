#ifndef MP3TOWAV_WAVE_H
#define MP3TOWAV_WAVE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* Documented at http://soundfile.sapp.org/doc/WaveFormat/ */
struct __attribute__((__packed__)) mtw_wave_header {
    uint32_t ChunkID;
    uint32_t ChunkSize; /* signed? */
    uint32_t Format; /* "WAVE" */

    /* Format subchunk */
    uint32_t Subchunk1ID; /* "fmt " */
    uint32_t Subchunk1Size; /* 16 for PCM */
    uint16_t AudioFormat; /* PCM = 1, other values indicate compression */
    uint16_t NumChannels; /* Mono = 1, Stereo = 2 */
    uint32_t SampleRate; /* 8000, 44100, etc. */
    uint32_t ByteRate; /* == SampleRate * NumChannels * BitsPerSample/8 */
    uint16_t BlockAlign; /* == NumChannels * BitsPerSample/8 */
    uint16_t BitsPerSample; /* 8 bits = 8, 16 bits = 16, etc. */
    /* Extra fields possible here, they don't exist for PCM */

    /* Data subchunk */
    uint32_t Subchunk2ID; /* "data" */
    uint32_t Subchunk2Size; /* == NumSamples * NumChannels * BitsPerSample/8 */

    /* Data comes after header */
};

bool mtw_wave_read(struct mtw_wave_header *wh, FILE *f);
void mtw_wave_print(struct mtw_wave_header *wh);
bool mtw_wave_valid(struct mtw_wave_header *wh);

#endif //MP3TOWAV_WAVE_H
