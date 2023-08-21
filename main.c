#include <stdio.h>
#include <stdbool.h>

#include "wave.h"

int main() {
    int exit_code = 0;

    FILE *f = fopen("../tests/fixtures/pcm1644s.wav", "rb"); // FIXME: use args
    if (f == NULL) {
        perror("Could not open file");
        return 1;
    }

    struct mtw_wave_header wh;
    bool result = mtw_wave_read(&wh, f);
    if (!result) {
        exit_code = 1;
        goto out_close_file;
    }

    mtw_wave_print(&wh);
    printf("Valid: %s\n", mtw_wave_valid(&wh) ? "true" : "false");

    if (fseek(f, wh.Subchunk2Size, SEEK_CUR) != 0) {
        perror("Seeking file failed");

        exit_code = 1;
        goto out_close_file;
    }

    if (fgetc(f) != EOF) {
        fprintf(stderr, "WAV file contains more than 2 sections or contains"
                        " garbage at the end");

        exit_code = 1;
        goto out_close_file;
    }

out_close_file:
    fclose(f);
    return exit_code;
}
