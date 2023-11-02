#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char** argv) {

    if (argc != 3) {
        printf("usage: ./Copier src_path dst_path\n");
        exit(-1);
    }

    FILE* src = fopen(argv[1], "r");
    fseek(src, 0, SEEK_END);
    size_t src_size = ftell(src);
    fseek(src, 0, SEEK_SET);

    FILE* dst = fopen(argv[2], "w");

    if (src == NULL) {
        printf("Error opening %s", argv[1]);
        exit(-1);
    } else if (dst == NULL) {
        printf("Error opening %s", argv[2]);
        exit(-1);
    }
    
    char* buffer = malloc(sizeof(char) * src_size);
    char* progress = "==========";
    char* empty = "----------";
    int progressAmnt = 0;
    double numread;
    double percentage = 0;

    printf("[*]Copying %s to %s\n", argv[1], argv[2]);
    while (percentage < 100) {
        numread = fread(buffer, sizeof(char), 128, src);
        fwrite(buffer, numread, sizeof(char), dst);
        fseek(dst, 0, SEEK_END);
        percentage = (double)ftell(dst) / src_size * 100;
        progressAmnt = (int)(percentage / 10);
        printf("\r[*]<%.*s%.*s> (%.1f%%)", progressAmnt, progress, 10 - progressAmnt, empty, percentage);
    }
    printf("\n");

    fclose(src);
    fclose(dst);
    free(buffer);

    exit(0);
}