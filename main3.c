#include "encrypt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void * memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen)
{
    if (needlelen == 0)        return (void*)haystack;
    if (needlelen > haystacklen) return NULL;

    for (size_t i = 0; i <= haystacklen - needlelen; i++) {
        if (memcmp((char*)haystack + i, needle, needlelen) == 0) {
            return (void*)((char*)haystack + i);
        }
    }
    return NULL;
}
char* readfile(FILE *f) {
  // f invalid? fseek() fail?

 fseek(f, 0, SEEK_END);
  long length = ftell(f);

  rewind(f);
  char *buffer = (char *) malloc(length + 1);
      if (!f || fread(buffer, 1, length, f) != length) {
        fprintf(stderr, "Failure to read file magic.\n");
        return NULL;
    }
    return buffer;
}
char * retreiveString(FILE *f,const char *delimitter,int delimitersize ){
   
    fseek(f,0,SEEK_END);
    int filesize = ftell(f);
    rewind(f);
    char * buffer = (char *) malloc (filesize+1);
    if (buffer==NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }
    buffer=readfile(f);
    const char * delimitterpos = memmem((char *) buffer,(size_t)filesize,(char *)delimitter,delimitersize);
    printf("delpos %d\n",delimitterpos[0]);
    if (delimitterpos==NULL)
    {
        perror("delimiter not found");
        return NULL;
    }
    int delimitterposindex = delimitterpos-buffer;
    int stringpos = delimitterposindex+strlen(delimitter);
    char * extractedstring= (char *) malloc (filesize-stringpos+1);
    if (extractedstring==NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }
    buffer+=stringpos;
    strncpy (extractedstring, buffer,filesize-stringpos);
    extractedstring[filesize-stringpos]='\0';
    return extractedstring;
    
    
}
int main ()
{
     char *stringtoadd;
    const char *delimitter = "$_$_$";
    const char* filepath;
    printf("type the path of the file you want to insert the secret text in\n");

    scanf("%ms",&filepath);
    printf("type the string you want to insert the secret text in\n");
    scanf("%ms",&stringtoadd);
    FILE *fp = fopen(filepath, "ab");
    FILE *fchecksize=fopen(filepath,"rb");
    if (fp == NULL)
    {
        perror("Failed to open file");
        return EXIT_FAILURE;
        fclose(fp);
    }
    if(fchecksize==NULL)
     {
        perror("Failed to open file");
        return EXIT_FAILURE;
        fclose(fchecksize);
    }
    fseek(fchecksize,0,SEEK_END);
    int initialsize = ftell(fchecksize);

fclose(fchecksize);
int key = rand()%26+1;
    char* encryptedMes = (char*) malloc (strlen(stringtoadd));
strcpy(encryptedMes,stringtoadd);
  encryptCaesar(encryptedMes,key);

    int successaddenter=fputc('\n',fp);
int successadddelimit= fputs(delimitter,fp);
int successaddenter2=fputc('\n',fp);
int successaddstring=fputs(encryptedMes,fp);

    int filesize = 0;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    printf("%d",filesize);
    if (filesize == 0)
    {
        perror("Failed to seek to end of file");
        fclose(fp);
        return EXIT_FAILURE;
    }





fclose(fp);
FILE *fred;
fred=fopen(filepath,"rb");
    char * buffer= ( char * ) malloc ( filesize+1);
    buffer = readfile(fred);
    buffer[filesize]='\0';
//for (int i =0 ; i<filesize;i++){
  //  printf("%02c", buffer[i]);
//}
printf("\nInit file size%d\n",initialsize);
printf("new file size %d\n",filesize);

char * extractedstring = retreiveString(fred,delimitter,strlen(delimitter));
printf("%s\n",extractedstring);
const char* outpath;
printf("write the path name for extracted text \n");
scanf("%ms",&outpath);
FILE * fwrite = fopen(outpath,"wb");
if(fwrite==NULL)
{
    perror("Failed to open file");
    return EXIT_FAILURE;
    fclose(fwrite);
}
int succesEnc= fputs(extractedstring,fwrite);
if (succesEnc==EOF)
{
    perror("Failed to write to file");
    return EXIT_FAILURE;
    fclose(fwrite);
}
char* decryptedMes = (char*) malloc (strlen(extractedstring));
strcpy(decryptedMes,extractedstring);
  decryptCaesar(decryptedMes,key);
  printf("\n%s\n",decryptedMes);

char* decryptpath;
printf("\nchoose the outpath path for decrypted file\n");
scanf("%ms",&decryptpath);
if(strcmp(outpath,decryptpath)==0)
{
    perror("decrypted path is same as encrypted path");
    return EXIT_FAILURE;
}
 FILE * dwrite= fopen(decryptpath,"wb");
 if(dwrite==NULL)
 {
    perror("Failed to open file");
    return EXIT_FAILURE;
    fclose(dwrite);
 }
 int decsuccess=fputs(decryptedMes,dwrite);
 if (decsuccess==EOF)
 {
    perror("Failed to write to file");
    return EXIT_FAILURE;
    fclose(dwrite);
 }

fclose(fred); free ( buffer);
free(extractedstring);
free(stringtoadd);
fclose(fwrite);
return 0;
}
