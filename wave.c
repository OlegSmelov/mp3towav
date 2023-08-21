#include <endian.h>

#include "wave.h"

bool mtw_wave_read(struct mtw_wave_header *wh, FILE *f) {
    size_t n = fread(wh, sizeof(struct mtw_wave_header), 1, f);
    if (n != 1) {
        perror("Read error");
        return false;
    }

    wh->ChunkID = be32toh(wh->ChunkID);
    wh->ChunkSize = le32toh(wh->ChunkSize);
    wh->Format = be32toh(wh->Format);

    wh->Subchunk1ID = be32toh(wh->Subchunk1ID);
    wh->Subchunk1Size = le32toh(wh->Subchunk1Size);
    wh->AudioFormat = le16toh(wh->AudioFormat);
    wh->NumChannels = le16toh(wh->NumChannels);
    wh->SampleRate = le32toh(wh->SampleRate);
    wh->ByteRate = le32toh(wh->ByteRate);
    wh->BlockAlign = le16toh(wh->BlockAlign);
    wh->BitsPerSample = le16toh(wh->BitsPerSample);

    wh->Subchunk2ID = be32toh(wh->Subchunk2ID);
    wh->Subchunk2Size = le32toh(wh->Subchunk2Size);

    return true;
}

void mtw_wave_print(struct mtw_wave_header *wh) {
    printf("ChunkID: 0x%08x\n", wh->ChunkID);
    printf("ChunkSize: %d\n", wh->ChunkSize);
    printf("Format: 0x%08x\n", wh->Format);

    printf("Subchunk1ID: 0x%08x\n", wh->Subchunk1ID);
    printf("Subchunk1Size: %d\n", wh->Subchunk1Size);
    printf("AudioFormat: %d\n", wh->AudioFormat);
    printf("NumChannels: %d\n", wh->NumChannels);
    printf("SampleRate: %d\n", wh->SampleRate);
    printf("ByteRate: %d\n", wh->ByteRate);
    printf("BlockAlign: %d\n", wh->BlockAlign);
    printf("BitsPerSample: %d\n", wh->BitsPerSample);

    printf("Subchunk2ID: 0x%08x\n", wh->Subchunk2ID);
    printf("Subchunk2Size: %d\n", wh->Subchunk2Size);
}

bool mtw_wave_valid(struct mtw_wave_header *wh) {
    // TODO: verify bitrates etc.
    // TODO: verify that it's PCM
    return (wh->ChunkID == 0x52494646) &&
        (wh->Format == 0x57415645) &&
        (wh->Subchunk1ID == 0x666d7420) &&
        (wh->Subchunk2ID == 0x64617461);
}

bool mtw_read_samples(struct mtw_wave_header *wh) {

}