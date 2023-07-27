[ikun.py](ikun.py) 把[ikun_basketball.mp4](ikun_basketball.mp4)转成单色128x64分辨率bin文件[ikun_basketball.bin](ikun_basketball.bin),每帧1kb(128x64比特)  

用quicklz压缩,生成[ikun_basketball_compressed.bin](ikun_basketball_compressed.bin)
```c
#include <stdio.h>
#include <malloc.h>
#include "quicklz.h"

#define MAX_BUF_SIZE (1*1024)


int stream_compress(FILE *ifile, FILE *ofile) {
    char *read_buffer, *write_buffer;
    size_t d, c, compressed_size;
    qlz_state_compress state_compress = {0};

    read_buffer = (char *) malloc(MAX_BUF_SIZE);

    compressed_size = MAX_BUF_SIZE + 1024; //是有可能越压越大的
    write_buffer = (char *) malloc(compressed_size);

    while ((d = fread(read_buffer, 1, MAX_BUF_SIZE, ifile)) != 0) {
        c = qlz_compress(read_buffer, write_buffer, d, &state_compress);
        printf("%ld,", ftell(ofile));
        fwrite(write_buffer, c, 1, ofile);
    }

    free(write_buffer);
    free(read_buffer);
    return 0;
}


int main() {
    FILE *c_in = fopen("ikun_basketball.bin", "rb");
    FILE *c_out = fopen("ikun_basketball_compressed.bin", "wb");
    stream_compress(c_in, c_out);
    fclose(c_in);
    fclose(c_out);
    return 0;
}
```

用[convert.py](convert.py)生成[ikun_basketball_compressed.h](ikun_basketball_compressed.h)  
上一步c语言执行的时候生成了一个数组,offset,也需要用


