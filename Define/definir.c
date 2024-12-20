#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// función auxiliar para "escribir" un nuevo nodo
void WNodo(FILE *f, int izq, int der, short len_nKey, short len_nDef, const char *nkey, const char *ndef) {
    fwrite(&izq, sizeof(int), 1, f); // nodo izq
    fwrite(&der, sizeof(int), 1, f); // nodo der
    fwrite(&len_nKey, sizeof(short), 1, f); // len llave
    fwrite(&len_nDef, sizeof(short), 1, f); // len def
    fwrite(nkey, sizeof(char), len_nKey, f); // llave
    fwrite(ndef, sizeof(char), len_nDef, f); // def
}
// función que retrocede el puntero en p pasos y guarda la pos actual
long back(FILE *f, int p) {
    fseek(f, -p, SEEK_CUR); 
    return ftell(f);
}

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "uso: ./definir <archivo> <llave> <definicion>\n");
                return 1;
  }

  char *nnom = argv[1], *nkey = argv[2], *ndef = argv[3]; 

  int len_nKey = strlen(nkey), len_nDef = strlen(ndef);

  FILE *f = fopen(nnom, "r+"); 
  
  if (f == NULL) {
    perror(nnom);
    return 1;
  }

  fseek(f, 0, SEEK_END);
  long fileSize = ftell(f);
  fseek(f, 0, SEEK_SET);

  int empty = -1;
  //si el archivo está vacío, se escribe en la raíz 
  if (fileSize == 0) {
    WNodo(f, empty, empty, len_nKey, len_nDef, nkey, ndef);
    fclose(f);
    return 0;
  }

  char key[100];
  int pos_izq = 0, pos_der = 0;
  short len_key = 0, len_def = 0;
  // aquí leemos el nodo raíz
  fread(&pos_izq, sizeof(int), 1, f); 
  fread(&pos_der, sizeof(int), 1, f); 
  fread(&len_key, sizeof(short), 1, f); 
  fread(&len_def, sizeof(short), 1, f); 
  
  if (len_key > sizeof(key)) {
    fprintf(stderr, "La llave es demasiado larga\n");
    fclose(f);
    return 1;
  }
  fread(key, sizeof(char), len_key, f); 
  key[len_key] = '\0';

  int catch = 1;

  while(catch){
    int compare = strcmp(key, nkey);

    // si las llaves coinciden, no se puede modificar
    if (compare == 0) {
        fprintf(stderr, "Llave existente: no se puede modificar la llave %s\n", key);
        fclose(f);
        return 1;
    } 
    else if (compare < 0 && pos_der == -1) { 
        long pos_1 = back(f, 8 + len_key);
        fseek(f, 0, SEEK_END);
        long pos_2 = ftell(f); 
        WNodo(f, empty, empty, len_nKey, len_nDef, nkey, ndef);
        fseek(f, pos_1, SEEK_SET); 
        fwrite(&pos_2, sizeof(int), 1, f);
        catch = 0;
    }
    else if (compare > 0 && pos_izq == -1) { 
        long pos_1 = back(f, 12 + len_key);
        fseek(f, 0, SEEK_END);
        long pos_2 = ftell(f); 
        WNodo(f, empty, empty, len_nKey, len_nDef, nkey, ndef);
        fseek(f, pos_1, SEEK_SET); 
        fwrite(&pos_2, sizeof(int), 1, f);
        catch = 0; 
    }
    else if (compare < 0) {
        fseek(f, pos_der, SEEK_SET);
        fread(&pos_izq, sizeof(int), 1, f); 
        fread(&pos_der, sizeof(int), 1, f); 
        fread(&len_key, sizeof(short), 1, f); 
        fread(&len_def, sizeof(short), 1, f); 
        fread(key, sizeof(char), len_key, f); 
        key[len_key] = '\0';
        
    }
    else if (compare > 0) {
        fseek(f, pos_izq, SEEK_SET);
        fread(&pos_izq, sizeof(int), 1, f); 
        fread(&pos_der, sizeof(int), 1, f); 
        fread(&len_key, sizeof(short), 1, f); 
        fread(&len_def, sizeof(short), 1, f);
        fread(key, sizeof(char), len_key, f); 
        key[len_key] = '\0';
    }
  }
  fclose(f);
  return 0;
}
