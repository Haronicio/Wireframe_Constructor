#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shapeinput.h"
#include <windows.h>
#include <Commdlg.h>

static char filename[200] ="";

int input(float *x, float *y,float *z)
{
	open();
	FILE * fichier;
	int i;
	char chaine[100];
	int A = 0;

	fichier = fopen(filename/*"C:/Users/Haron/Desktop/Wireframe constructor/shape/pyramide.shape"*/,"r");
	if (fichier == NULL)
	{
		printf("erreur fichier introuvable ou corrompu\n");
		exit (-1);
	}
	printf("ouvert\n");
	fgets(chaine, sizeof(chaine), fichier);
	printf("%s",chaine);
	if (strcmp(chaine,"[newshape]\n") == 0)
	{
		chaine[0] = '\0';
		fscanf(fichier,"Vertex = %d\n",&A);
		printf("nombre de Vertex attendue %d\n",A );
		fgets(chaine, sizeof(chaine), fichier);
		printf("%s",chaine);
		if (strcmp(chaine,"[x]\n") == 0)
		{
			realloc(x,A* sizeof(float));
			if (x == NULL)
			{
				printf("erreur x\n");
			}
			for (i = 0; i < A ; ++i)
				{
					fscanf(fichier,"%f",&x[i]);
					printf("x :%f\n",x[i] );
					
				}
			chaine[0] = '\0';
			fgets(chaine, sizeof(chaine), fichier);
			chaine[0] = '\0';
			fgets(chaine, sizeof(chaine), fichier);
			printf("%s",chaine);
				if (strcmp(chaine,"[y]\n") == 0)
					{
						realloc(y,A* sizeof(float));
						for (i = 0; i < A ; ++i)
							{
								fscanf(fichier,"%f",&y[i]);
								printf("y :%f\n",y[i]);
							}
						chaine[0] = '\0';
						fgets(chaine, sizeof(chaine), fichier);
						chaine[0] = '\0';
						fgets(chaine, sizeof(chaine), fichier);
						printf("%s",chaine);
						if (strcmp(chaine,"[z]\n") == 0)
					{
						realloc(z,A * sizeof(float));
						for (i = 0; i < A ; ++i)
							{
								fscanf(fichier,"%f",&z[i]);
								printf("z :%f\n",z[i] );
							}
						chaine[0] = '\0';
						fgets(chaine, sizeof(chaine), fichier);
						chaine[0] = '\0';
						fgets(chaine, sizeof(chaine), fichier);
						printf("%s",chaine);
						if (strcmp(chaine,"[/newshape]") == 0)
						{
							fclose(fichier);
							printf("fichier charge avec succes\n");
							

							// free(x);
							// free(y);
							// free(z);
							// exit(0);
						}
						else
						{
							printf("le programme a rencontre des problemes lors de la fermeture verifier les arguments\n");
						}
					}
					else
					{
						printf("erreur coordonnee z\n");
						exit (-1);
					}		
					}
					else
					{
						printf("erreur coordonnee y\n");
						exit (-1);
					}		
		}
		else
		{
			printf("erreur coordonnee x\n");
			exit (-1);
		}		
	}
	else
	{
		printf("Erreur d arguments construisez comme suit : [newshape] Vertex [x] [y] [z] [/newshape]\n");
		exit (-1);
	}
	// exit (0);
	return A;
}
void open(void)
{
	printf("%d\n",sizeof(filename) );
 	OPENFILENAME open;
 	ZeroMemory(&open,sizeof(OPENFILENAME));
 	open.lStructSize = sizeof(OPENFILENAME);
 	open.hwndOwner = NULL;
 	open.lpstrFilter = "Shape Files (*.shape)\0*.shape\0All Files (*.*)\0*.*\0";
 	open.nFilterIndex =1;
 	open.lpstrFile = filename;
 	open.nMaxFile = 200;
 	open.nMaxFileTitle = 0;
 	open.lpstrInitialDir =NULL;
 	open.lpstrTitle = "Open shape file";
 	open.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST;

 	GetOpenFileName(&open);
 	printf(" file : %s\n",filename );
 	
}
