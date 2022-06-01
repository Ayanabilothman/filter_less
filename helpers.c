#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int pixel;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            pixel = round((image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed) / 3.0);
            image[r][c].rgbtBlue = pixel;
            image[r][c].rgbtGreen = pixel;
            image[r][c].rgbtRed = pixel;
        }
    }
    return;
}

// to ensure that the value does not exceed 255
int max(int max)
{
    if (max > 255)
    {
        max = 255;
    }
    return max;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int values[3];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            values[0] = max(round(0.272 * image[r][c].rgbtRed + 0.534 * image[r][c].rgbtGreen + 0.131 * image[r][c].rgbtBlue));
            values[1] = max(round(0.349 * image[r][c].rgbtRed + 0.686 * image[r][c].rgbtGreen + 0.168 * image[r][c].rgbtBlue));
            values[2] = max(round(0.393 * image[r][c].rgbtRed + 0.769 * image[r][c].rgbtGreen + 0.189 * image[r][c].rgbtBlue));

            image[r][c].rgbtBlue = values[0];
            image[r][c].rgbtGreen = values[1];
            image[r][c].rgbtRed = values[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int c = width - 1;
    int W = round(width / 2);
    int widthcopy = width - W;
    RGBTRIPLE copy[height][widthcopy];

    for (int r = 0; r < height; r++)
    {
        for (int half_w = 0; half_w < widthcopy; half_w++)
        {
            copy[r][half_w] = image[r][half_w];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j < W)
            {
                image[i][j] = image[i][c];
            }
            else
            {
                image[i][j] = copy[i][c];
            }
            c--;
        }
        c = width - 1;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int value[3];
    int values_sum[3] = {0, 0, 0};
    float pixels_count = 0.0;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // rr and cc are the positions of kernel
            for (int rr = r - 1; rr < r + 2; rr++)
            {
                for (int cc = c - 1; cc < c + 2; cc++)
                {
                    // condition to sure that it isn't outside the image
                    if (rr < 0 || rr > height - 1 || cc < 0 || cc > width - 1)
                    {
                        value[0] = 0;
                        value[1] = 0;
                        value[2] = 0;
                    }
                    else
                    {
                        value[0] = copy[rr][cc].rgbtBlue;
                        value[1] = copy[rr][cc].rgbtGreen;
                        value[2] = copy[rr][cc].rgbtRed;
                        pixels_count++;
                    }
                    values_sum[0] += value[0];
                    values_sum[1] += value[1];
                    values_sum[2] += value[2];
                }
            }
            image[r][c].rgbtBlue =  round(values_sum[0] / pixels_count);
            image[r][c].rgbtGreen = round(values_sum[1] / pixels_count);
            image[r][c].rgbtRed = round(values_sum[2] / pixels_count);
            pixels_count = 0.0;
            values_sum[0] = 0;
            values_sum[1] = 0;
            values_sum[2] = 0;
        }
    }
    return;
}
