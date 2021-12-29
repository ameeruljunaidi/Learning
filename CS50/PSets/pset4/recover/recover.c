#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int JPEG_SIZE = 512;

int main(int argc, char *argv[])
{
  // Check command-line arguments
  if (argc != 2)
  {
    printf("Usage: ./recover image\n");
    return 1;
  }

  // Open files
  FILE *input = fopen(argv[1], "r");
  if (input == NULL)
  {
    printf("Could not open file.\n");
    return 1;
  }

  FILE *output = fopen("000.jpg", "w");
  if (output == NULL)
  {
    printf("Could not open file.\n");
    return 1;
  }

  int fileCount = 0;
  char *filename = malloc(sizeof(char) * FILENAME_MAX);

  BYTE buffer[JPEG_SIZE];

  while (fread(&buffer, sizeof(buffer), 1, input))
  {
    int condition1 = buffer[0] == 0xff;
    int condition2 = buffer[1] == 0xd8;
    int condition3 = buffer[2] == 0xff;
    int condition4 = (buffer[3] & 0xf0) == 0xe0;
    int newJPEG = condition1 && condition2 && condition3 && condition4;

    // If start of new JPEG
    if (newJPEG)
    {
      fileCount++;
      sprintf(filename, "%03i.jpg", fileCount - 1);

      if (fileCount == 1)
      {
        fwrite(&buffer, sizeof(buffer), 1, output);
      }
      else
      {
        fclose(output);

        output = fopen(filename, "w");
        if (output == NULL)
        {
          printf("Could not open file.\n");
          return 1;
        }

        fwrite(&buffer, sizeof(buffer), 1, output);
      }
    }
    else if (fileCount > 0)
    {
      fwrite(&buffer, sizeof(buffer), 1, output);
    }
  }

  // Free malloc
  free(filename);

  // Close file
  fclose(input);
}
