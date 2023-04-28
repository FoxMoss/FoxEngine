#include "upscale.h"
#include "math.h"

void upscaleImage(Image *buffer, int size)
{
    Image newBuffer = GenImageColor(buffer->width, buffer->height, BLACK);

    for (int y = 0; y < buffer->height / size; y++)
    {
        for (int x = 0; x < buffer->width / size; x++)
        {
            Color A, B, C, D, E, F, G, H, I;
            Color E0, E1, E2, E3, E4, E5, E6, E7, E8;
            A = GetImageColorSafe(buffer, x*size - size, y*size - size);
            B = GetImageColorSafe(buffer, x*size, y*size - size);
            C = GetImageColorSafe(buffer, x*size + size, y*size - size);
            D = GetImageColorSafe(buffer, x*size - size, y*size);
            E = GetImageColorSafe(buffer, x*size, y*size);
            F = GetImageColorSafe(buffer, x*size + size, y*size);
            G = GetImageColorSafe(buffer, x*size - size, y*size + size);
            I = GetImageColorSafe(buffer, x*size + size, y*size + size);
            H = GetImageColorSafe(buffer, x*size, y*size + size);

            if (!coloreqeq(B, H) && !coloreqeq(D, F))
            {
                E0 = coloreqeq(D, B) ? D : E;
                E1 = (coloreqeq(D, B) && !coloreqeq(E, C)) || (coloreqeq(B, F) && !coloreqeq(E, A)) ? B : E;
                E2 = coloreqeq(B, F) ? F : E;
                E3 = (coloreqeq(D, B) && !coloreqeq(E, G)) || (coloreqeq(D, H) && !coloreqeq(E, A)) ? D : E;
                E4 = E;
                E5 = (coloreqeq(B, F) && !coloreqeq(E, I)) || (coloreqeq(H, F) && !coloreqeq(E, C)) ? F : E;
                E6 = coloreqeq(D, H) ? D : E;
                E7 = (coloreqeq(D, H) && !coloreqeq(E, I)) || (coloreqeq(H, F) && !coloreqeq(E, G)) ? H : E;
                E8 = coloreqeq(H, F) ? F : E;
            }
            else
            {
                E0 = E;
                E1 = E;
                E2 = E;
                E3 = E;
                E4 = E;
                E5 = E;
                E6 = E;
                E7 = E;
                E8 = E;
            }
            ImageDrawRectangle(&newBuffer, x*size - size/3, y*size - size/3, size/3, size/3, E0);
            ImageDrawRectangle(&newBuffer, x*size + size/3, y*size - size/3, size/3, size/3, E2);
            ImageDrawRectangle(&newBuffer, x*size, y*size - size/3, size/3, size/3, E1);
            ImageDrawRectangle(&newBuffer, x*size - size/3, y*size, size/3, size/3, E3);
            ImageDrawRectangle(&newBuffer, x*size + size/3, y*size, size/3, size/3, E5);
            ImageDrawRectangle(&newBuffer, x*size, y*size, size/3, size/3, E4);
            ImageDrawRectangle(&newBuffer, x*size - size/3, y*size + size/3, size/3, size/3, E6);
            ImageDrawRectangle(&newBuffer, x*size + size/3, y*size + size/3, size/3, size/3, E8);
            ImageDrawRectangle(&newBuffer, x*size, y*size + size/3, size/3, size/3, E7);

            // ImageDrawRectangle(buffer, x*size*upscale, y*size*upscale, upscale/2, upscale/2, GetImageColorSafe(buffer, x*size, y*size));
        }
    }
    // ImageBlurBox(buffer, upscale);

    //UnloadImage(newBuffer);
    UnloadImage(*buffer);
    *buffer = newBuffer;
    // ImageDraw(buffer, newBuffer, (Rectangle){buffer->width, buffer->height}, (Rectangle){buffer->width, buffer->height}, BLACK);
    UnloadImage(newBuffer);
}

bool coloreqeq(Color x, Color y)
{
    return (x.r == y.r) && (x.g == y.g) && (x.b == y.b);
}
Color GetImageColorSafe(Image *image, int x, int y)
{
    int width = image->width;
    int height = image->height;

    if (x < 0 || x >= width || y < 0 || y >= height) {
        return BLACK;
    }

    return GetImageColor(*image, x, y);

}