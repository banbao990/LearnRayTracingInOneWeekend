// TODO
#include <images.hpp>

#include <iostream>

void ouputImage(const unsigned char** img, const int width, const int height,
                const char* fname) {
    P6(img, width, height, fname);
}

// TODO
void P6(const unsigned char** img, const int width, const int height,
        const char* fname) {
    FILE* fp = fopen(fname, "wb");
    // 1. 文件头
    fprintf(fp, "P6\n%d %d\n255\n", width, height);

    // 2. 文件数据
    // 图片的 x 轴向右, y 轴向下
    // RGB
    fwrite(img, 1, width * height, fp);
    fclose(fp);
}
