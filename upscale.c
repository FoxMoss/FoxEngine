#include "upscale.h"
#include "math.h"

void upscaleImage(Image *buffer, int size, int upscale)
{
    Image newBuffer = GenImageColor(buffer->width, buffer->height, BLACK);

    for (int y = 0; y < buffer->height; y++)
    {
        for (int x = 0; x < buffer->width; x++)
        {
            Color newColor;
            float rpixelx = round(x/upscale)*upscale;
            float rpixely = round(y/upscale)*upscale;
            //printf("%i, %i\n", x, y);
            float distx = (x - rpixelx + 1)/upscale;
            float disty = (y - rpixely + 1)/upscale;
            if(rpixelx == -1)
            {
                //printf("%f\n", rpixelx);
            }
            //printf("%f, %f\n", distx, disty);
            Color color1 = GetImageColor(*buffer, rpixelx, rpixely);
            Color color2 = GetImageColor(*buffer, fmax(rpixelx+upscale, buffer->width), rpixely+0);
            Color color3 = GetImageColor(*buffer, fmin(rpixelx-upscale, 0), fmin(rpixely+0,0));
            Color color4 = GetImageColor(*buffer, fmin(rpixelx+0,0), fmax(rpixely+upscale, buffer->height));
            Color color5 = GetImageColor(*buffer, fmin(rpixelx+0,0), fmin(rpixely-upscale, 0));
            float newRed = (color1.r + color2.r*distx + color3.r*distx + color4.r*disty + color5.r*disty)/(1+(distx*2)+(disty*2));

            newColor = (Color){newRed, 0, 0, 255};
            ImageDrawPixel(&newBuffer, x, y, newColor);
            //ImageDrawRectangle(buffer, x*upscale, y*upscale, upscale/2, upscale/2, GetImageColor(*buffer, x, y));
        }
    }
    //ImageBlurBox(buffer, upscale);

    //UnloadImage(newBuffer);
    UnloadImage(*buffer);
    *buffer = ImageCopy(newBuffer);
    //ImageDraw(buffer, newBuffer, (Rectangle){buffer->width, buffer->height}, (Rectangle){buffer->width, buffer->height}, BLACK);
    UnloadImage(newBuffer);
}

