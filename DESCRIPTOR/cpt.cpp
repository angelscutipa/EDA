#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <vector>

using namespace std;

void error(const char *s);
vector<string> selec_carpetas(vector<string> archivo);

vector<string> optener_carpetas( char *direccion)
{
  vector<string> nombre;
  vector<string> carpetas;
  DIR *dir;
  struct dirent *ent;
  dir = opendir (direccion);
  if (dir == NULL) 
    error("No puedo abrir el directorio");

  
  while ((ent = readdir (dir)) != NULL) 
  {
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
    {
      
      nombre.push_back(ent->d_name);
    }
  }
  closedir (dir);
  carpetas=selec_carpetas(nombre);

  for (int i = 0; i < carpetas.size(); ++i)
  {
    cout<<carpetas[i]<<endl;
  }

  return carpetas;
} 

vector<string> optener_archivos( char *direccion)
{
  vector<string> nombre;
  DIR *dir;
  struct dirent *ent;
  dir = opendir (direccion);
  if (dir == NULL) 
    error("No puedo abrir el directorio");

  
  while ((ent = readdir (dir)) != NULL) 
  {
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
    {
      
      nombre.push_back(ent->d_name);
    }
  }
  closedir (dir);

  /*for (int i = 0; i < nombre.size(); ++i)
  {
    cout<<nombre[i]<<endl;
  }*/

  return nombre;
} 

void error(const char *s)
{
  perror (s);
  exit(EXIT_FAILURE);
}

vector<string> selec_carpetas(vector<string> archivo){
  vector<string> carpetas;
  bool a=true;
  for (int i = 0; i < archivo.size(); ++i)
  {
    for (int j = 0; j < archivo[i].size(); ++j)
    {
      if(archivo[i][j]=='.'){
        a=false;
      }
    }
    if (a==true)
    {
      carpetas.push_back(archivo[i]);
    }
    a=true;
      
  }
  
  return carpetas;
}