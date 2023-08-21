#include <stdio.h>
#include <assert.h>

#include "../wave.h"

FILE *open_fixture() {
    FILE *f = fopen("../tests/fixtures/pcm1644s.wav", "rb");
    assert(f);

    return f;
}

void test_wave_header_size() {
    assert(sizeof(struct mtw_wave_header) == 44);
}

void test_wave_file() {
    FILE *f = open_fixture();

    struct mtw_wave_header wh;
    bool result = mtw_wave_read(&wh, f);
    assert(result);

    assert(wh.ChunkID == 0x52494646);
    assert(wh.Format == 0x57415645);
    assert(wh.Subchunk1ID == 0x666d7420);
    assert(wh.Subchunk2ID == 0x64617461);
    assert(wh.Subchunk2Size == 1179636);

    assert(mtw_wave_valid(&wh));
}

int main() {
    test_wave_header_size();
    test_wave_file();

    return 0;
}
