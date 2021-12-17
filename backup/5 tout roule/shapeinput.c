#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shapeinput.h"

void input(float *x, float *y,float *z)
{
	FILE * fichier;
	int i;
	// float * x;
	// float * y;
	// float * z;
	char chaine[100];
	int A = 0;

	fichier = fopen("./shape/pyramide.shape","r");
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
					printf("%f\n",x[i] );
					
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
								printf("y%f\n",y[i]);
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
								printf("%f\n",z[i] );
							}
						chaine[0] = '\0';
						fgets(chaine, sizeof(chaine), fichier);
						chaine[0] = '\0';
						fgets(chaine, sizeof(chaine), fichier);
						printf("%s",chaine);
						if (strcmp(chaine,"[/newshape]\n") == 0)
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
}
