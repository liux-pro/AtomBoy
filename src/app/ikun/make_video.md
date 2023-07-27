[ikun.py](ikun.py) 把[ikun_basketball.mp4](ikun_basketball.mp4),扣去绿幕,转成单色64x64分辨率,每帧0.5kb(64x64比特)的头文件



用quicklz压缩,读取刚刚生成的头文件,生成[ikun_basketball_compressed.bin](ikun_basketball_compressed.bin)
```c
#include <stdio.h>
#include <malloc.h>
#include "quicklz.h"
#include "IMAGE_ikun_basketball_ikun_basketball.h"

#define MAX_BUF_SIZE (512)


int stream_compress(FILE *ofile) {
    char *read_buffer, *write_buffer;
    size_t d, c, compressed_size;
    qlz_state_compress state_compress = {0};


    compressed_size = MAX_BUF_SIZE + 1024; //是有可能越压越大的
    write_buffer = (char *) malloc(compressed_size);


    for (int i = 0; i < sizeof(IMAGE_ikun_basketball_ikun_basketball) / MAX_BUF_SIZE; ++i) {
        c = qlz_compress(IMAGE_ikun_basketball_ikun_basketball+i*MAX_BUF_SIZE, write_buffer, MAX_BUF_SIZE, &state_compress);
        printf("%ld,", ftell(ofile));
        fwrite(write_buffer, c, 1, ofile);
    }

    free(write_buffer);
    return 0;
}


int main() {
    FILE *c_out = fopen("ikun_basketball_compressed.bin", "wb");
    stream_compress(c_out);
    fclose(c_out);
    return 0;
}
```

用[convert.py](convert.py)生成[ikun_basketball_compressed.h](ikun_basketball_compressed.h)  
上一步c语言执行的时候打印了一个数组,offset,用来分割每一帧压缩数据


