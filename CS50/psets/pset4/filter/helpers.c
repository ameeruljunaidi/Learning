#include "helpers.h"
#include <math.h>

/**
 * Converting to grayscale
 * Takes the average of the current RGB value
 * 
 * Need two loops:
 * Loop 1 is down across the rows based on height of the image
 * Loop 2 is right acroess the columns based on the width of the image
 * 
 * Take the average of RGB value at that current position
 * Assign all the RGB value at that position to the average
 */
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      BYTE rgbRed = image[i][j].rgbtRed;
      BYTE rgbGreen = image[i][j].rgbtGreen;
      BYTE rgbBlue = image[i][j].rgbtBlue;

      BYTE avgRGB = round((rgbRed + rgbGreen + rgbBlue) / (double)3);

      image[i][j].rgbtRed = avgRGB;
      image[i][j].rgbtGreen = avgRGB;
      image[i][j].rgbtBlue = avgRGB;
    }
  }
  return;
}

/**
 * Reflect/mirror the image
 * 
 * Need two loops:
 * Loop 1 is down across the rows based on height of the image
 * Loop 2 is right acroess the columns based on the width of the image
 * image[height][width] we are only working with width, not flipping the height
 * In other words, only perform swapping operations on j
 * 
 * Need to swap right to left (might need to use pointers)
 * Create a buffer to store the BYTE and then swap the places
 */
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE temp[height][width];

  for (int i = 0; i < height; i++)
    for (int j = width - 1, currentPos = 0; j >= 0; j--, currentPos++)
      temp[i][currentPos] = image[i][j];

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image[i][j] = temp[i][j];

  return;
}

/**
 * Blurring images
 * 
 * Choose a spot x on the image grid, check for edge case
 * Need to create a 3x3 grid from the original image grid
 * If edge case, the grid will not be a 3x3, but something smaller
 * Average out the RGB values and x now will have that averaged out value
 */
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE temp[height][width];

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
    {
      int squares = 0;
      int rgbRedTotal = 0;
      int rgbGreenTotal = 0;
      int rgbBlueTotal = 0;

      for (int k = -1; k < 2; k++)
        for (int l = -1; l < 2; l++)
        {
          int v = i + k;
          int h = j + l;

          if (v >= 0 && h >= 0 && v < height && h < width)
          {
            squares++;
            rgbRedTotal += image[v][h].rgbtRed;
            rgbGreenTotal += image[v][h].rgbtGreen;
            rgbBlueTotal += image[v][h].rgbtBlue;
          }
        }

      int rgbRedAvg = (int)round(rgbRedTotal / (double)squares);
      int rgbGreenAvg = (int)round(rgbGreenTotal / (double)squares);
      int rgbBlueAvg = (int)round(rgbBlueTotal / (double)squares);

      temp[i][j].rgbtRed = rgbRedAvg;
      temp[i][j].rgbtGreen = rgbGreenAvg;
      temp[i][j].rgbtBlue = rgbBlueAvg;
    }

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image[i][j] = temp[i][j];

  return;
}

/**
 * Detect edges
 * 
 * Gx
 * -1  0  1
 * -2  0  2
 * -1  0  1
 * 
 * Gy
 * -1 -2 -1
 *  0  0  0
 *  1  2  1
 */
void edges(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE temp[height][width];

  int gX[3][3];
  int gY[3][3];

  gX[0][0] = -1;
  gX[0][1] = 0;
  gX[0][2] = 1;
  gX[1][0] = -2;
  gX[1][1] = 0;
  gX[1][2] = 2;
  gX[2][0] = -1;
  gX[2][1] = 0;
  gX[2][2] = 1;

  gY[0][0] = -1;
  gY[0][1] = -2;
  gY[0][2] = -1;
  gY[1][0] = 0;
  gY[1][1] = 0;
  gY[1][2] = 0;
  gY[2][0] = 1;
  gY[2][1] = 2;
  gY[2][2] = 1;

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
    {
      int gXValRed = 0;
      int gXValGreen = 0;
      int gXValBlue = 0;
      int gYValRed = 0;
      int gYValGreen = 0;
      int gYValBlue = 0;

      for (int k = -1, x = 0; k < 2; k++, x++)
        for (int l = -1, y = 0; l < 2; l++, y++)
        {
          int v = i + k;
          int h = j + l;

          if (v >= 0 && h >= 0 && v < height && h < width)
          {
            gXValRed += gX[x][y] * image[v][h].rgbtRed;
            gXValGreen += gX[x][y] * image[v][h].rgbtGreen;
            gXValBlue += gX[x][y] * image[v][h].rgbtBlue;

            gYValRed += gY[x][y] * image[v][h].rgbtRed;
            gYValGreen += gY[x][y] * image[v][h].rgbtGreen;
            gYValBlue += gY[x][y] * image[v][h].rgbtBlue;
          }
        }

      int finalRed = round(sqrt(pow(gXValRed, 2) + pow(gYValRed, 2)));
      int finalGreen = round(sqrt(pow(gXValGreen, 2) + pow(gYValGreen, 2)));
      int finalBlue = round(sqrt(pow(gXValBlue, 2) + pow(gYValBlue, 2)));

      if (finalRed > 255)
        finalRed = 255;
      if (finalGreen > 255)
        finalGreen = 255;
      if (finalBlue > 255)
        finalBlue = 255;

      temp[i][j].rgbtRed = finalRed;
      temp[i][j].rgbtGreen = finalGreen;
      temp[i][j].rgbtBlue = finalBlue;
    }

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image[i][j] = temp[i][j];

  return;
}
