#ifndef IMAGES_H
#define IMAGES_H

// TODO
/* 输出一张图片 */
void ouputImage(const unsigned char** img, const int width, const int height,
                const char* fname);

/* ppm 6 的格式输出一张图片 */
void P6(const unsigned char** img, const int width, const int height,
        const char* fname);

#endif