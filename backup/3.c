/*L'erreur ici est que le fichier se stop au return (0) de Input car le programme est considéré comme terminer*/  
/*                                _      
  _____ _    _          _   _  _____ ______ _      ____   _____ 
 / ____| |  | |   /\   | \ | |/ ____|  ____| |    / __ \ / ____|
| |    | |__| |  /  \  |  \| | |  __| |__  | |   | |  | | |  __ 
| |    |  __  | / /\ \ | . ` | | |_ |  __| | |   | |  | | | |_ |
| |____| |  | |/ ____ \| |\  | |__| | |____| |___| |__| | |__| |
 \_____|_|  |_/_/    \_\_| \_|\_____|______|______\____/ \_____|*/


#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include "shapeinput.h"

int input(float *x,float *y,float *z);

int main(int argc, char *argv[])
{
	void quadri(float* x,float* y,float* z,float d, float xp ,float yp,SDL_Renderer * renderer);
	int input(float *x,float *y,float *z);
	float* x;
	float* y;
	float* z;
	x = malloc(sizeof(float));
	y = malloc(sizeof(float));
	z = malloc(sizeof(float));
	int Hauteur = 600;
	// double pi = 3.14159265358979323846264338327950288419716939937510;
	int Largeur = 800;
	// int Ox = Largeur/2;
	// int Oy = Hauteur/2;							   //10
	// float x[17]={-50,50, 50,-50,-50,-50, 50, 50,-50,-50,-50,50, 50, 50, 50,-50,-50};
	// float y[17]={ 50,50,-50,-50, 50, 50, 50,-50,-50, 50, 50,50, 50,-50,-50,-50,-50};
	// float z[17]={ 50,50, 50, 50, 50,-50,-50,-50,-50,-50, 50,50,-50,-50, 50, 50,-50};
	
	int j;
	input(x,y,z);
	printf("hello ?\n");
	// for (j = 0; j < 17; ++j)
	// {
	// 	printf("%f\n",x[j] );
	// 	SDL_Delay(1000);
	// }
	float angle =0.1;
	float xp =0;
	float yp = 0;
	float zp = 0;
	float d = -256;
	int i;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Erreur dans l'initialisation de SDL %s\n",SDL_GetError());
		return -1;
	}
				
	SDL_Window * window;
	SDL_Renderer * renderer;
				
	window = SDL_CreateWindow("rotation",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Largeur,Hauteur, 0);
	if (window == NULL)
	{
		printf("Erreur lors de la creation de la fenetre %s\n",SDL_GetError());
		return -1;
	}
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED );
	if (renderer == NULL)
	{
		printf("erreur\n");
		return -1;
	}
	SDL_SetRenderDrawColor(renderer,255,255,255,255);


	// perspective(x,y,z,d);
	
	while (1) 
	{	

		
		quadri(x,y,z,d,xp,yp,renderer);
		for (i = 0; i <= 16; ++i)
		{
			
			//rotation axe Z
			xp = x[i]* cos(0/57.2958) - y[i] * sin(0/57.2958);
			y[i] = y[i]* cos(0/57.2958) + x[i] * sin(0/57.2958);
			x[i]=xp;
			printf("%f %f\n",x[i],y[i] );
		
		

			//rotation axe X
			zp = z[i]* cos(angle/57.2958) - y[i] * sin(angle/57.2958);
			y[i] = y[i]* cos(angle/57.2958) + z[i] * sin(angle/57.2958);
			z[i]=zp;
			printf("%f %f\n",z[i],y[i] );
		


			//rotation axe Y
			xp = x[i]* cos(0/57.2958) - z[i] * sin(0/57.2958);
			z[i] = z[i]* cos(0/57.2958) + x[i] * sin(0/57.2958);
			x[i]=xp;
			printf("%f %f\n",x[i],z[i] );

		}

		SDL_Delay(0);
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		
		
	}

	

	






	SDL_Delay(0);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
void quadri(float* x,float* y,float* z, float d,float xp,float yp,SDL_Renderer * renderer)
{
	float xs;
	float ys;
	int i;
	for (i = 0; i < 16; ++i)
	{
		xp=(d*x[i])/(d+z[i]);
		yp=(d*y[i])/(d+z[i]);
		xs=(d*x[i+1])/(d+z[i+1]);
		ys=(d*y[i+1])/(d+z[i+1]);

		SDL_RenderDrawLine(renderer,xp+400,yp+300,xs+400,ys+300);
		printf("%f %f\n",x[i],y[i] );
		
	}	
	SDL_RenderPresent(renderer);
}
int input(float *x, float *y,float *z)
{
	FILE * fichier;
	int i;
	// float * x;
	// float * y;
	// float * z;
	char chaine[100];
	int A = 0;

	fichier = fopen("./shape/cube.shape","r");
	if (fichier == NULL)
	{
		printf("erreur fichier introuvable ou corrompu\n");
		return -1;
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
			realloc(x,A * sizeof(float));
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
						realloc(y,A * sizeof(float));
						for (i = 0; i < A ; ++i)
							{
								fscanf(fichier,"%f",&y[i]);
								printf("%f\n",y[i] );
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
							free(x);
							free(y);
							free(z);
							return 0;
						}
						else
						{
							printf("le programme a rencontre des problemes lors de la fermeture verifier les arguments\n");
						}
					}
					else
					{
						printf("erreur coordonnee z\n");
						return -1;
					}		
					}
					else
					{
						printf("erreur coordonnee y\n");
						return -1;
					}		
		}
		else
		{
			printf("erreur coordonnee x\n");
			return -1;
		}		
	}
	else
	{
		printf("Erreur d arguments construisez comme suit : [newshape] Vertex [x] [y] [z] [/newshape]\n");
		return -1;
	}
	return 0;
}


