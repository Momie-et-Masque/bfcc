#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Brainfuck compiler to C by Momie_et_Masque
// Some code generated with ChatGPT and AWS CodeWhisperer
// Some code snippets from w3schools.com/c

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Brainfuck compiler to C by Momie_et_Masque. Please pass a source BF file path and an output C file path.\n");
    return 0;
  }
  if (argc < 3)
  {
    printf("Error : Too few arguments. Please pass a source BF file path and an output C file path.\n");
    return 1;
  }

  if (!(argv[1][strlen(argv[1])-3] == '.' && argv[1][strlen(argv[1])-2] == 'b' && argv[1][strlen(argv[1])-1] == 'f'))
  {
    printf("Error : Input file is not a BF file.");
    return 1;
  }
  if (!(argv[2][strlen(argv[2])-2] == '.' && argv[2][strlen(argv[2])-1] == 'c'))
  {
    printf("Error : Output file is not a C file.");
    return 1;
  }

 ////

  FILE *file;
  char *buffer;
  long fileLength;

  // Open the file in binary mode
  file = fopen(argv[1], "rb");
  if (file == NULL) {
      printf("Error: Input file not found.\n");
      return 1;
  }

  // Get the file length
  fseek(file, 0, SEEK_END);
  fileLength = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Allocate memory for the buffer
  buffer = (char *)malloc(fileLength + 1);
  if (buffer == NULL) {
      printf("Memory allocation failed.\n");
      fclose(file);
      return 1;
  }

  // Read the file content into the buffer
  fread(buffer, fileLength, 1, file);
  buffer[fileLength] = '\0'; // Add null-terminator to make it a valid C string

  // Clean up
  fclose(file);
  
  ////

  long i;
  char output[fileLength * 15 + 52];
  sprintf(output, "#include<stdio.h>\nint main(){char a[30000];int p=0;");
  for (i = 0; i < fileLength; i++)
  {
    char c = buffer[i];
    char out[15];
    
    switch (c)
    {
      case '>':
        sprintf(out, "p++;");
        break;
      case '<':
        sprintf(out, "p--;");
        break;
      case '+':
        sprintf(out, "a[p]++;");
        break;
      case '-':
        sprintf(out, "a[p]--;");
        break;
      case '.':
        sprintf(out, "putchar(a[p]);");
        break;
      case ',':
        sprintf(out, "a[p]=getchar();");
        break;
      case '[':
        sprintf(out, "while(a[p]){");
        break;
      case ']':
        sprintf(out, "}");
        break;
      default:
        sprintf(out, "");
        break;
    }

    strcat(output, out);
  }
  strcat(output, "}");
  //printf("%s", output);
  
  //// write to file
  FILE *fptr;

  // Open a file in writing mode
  fptr = fopen(argv[2], "w");

  // Write some text to the file
  fprintf(fptr, output);

  // Close the file
  fclose(fptr); 
  ////

  free(buffer);
  return 0;
}