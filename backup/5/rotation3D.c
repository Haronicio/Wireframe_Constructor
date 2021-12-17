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
#include "shapeinput.h"


int main(int argc, char *argv[])
{
	void quadri(float* x,float* y,float* z,float d, float xp ,float yp,SDL_Renderer * renderer);
	float* x;
	float* y;
	float* z;
	x = calloc(150,sizeof(float));
	y = calloc(150,sizeof(float));
	z = calloc(150,sizeof(float));
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
	for (j = 0; j < 10; ++j)//17 pour cube
	{
		printf("x %f\n",x[j] );
		printf("y %f\n",y[j] );
		printf("z %f\n",z[j] );
		SDL_Delay(000);
	}
	float angle =0.1;
	float xp =0;
	float yp = 0;
	float zp = 0;
	float d = -256;
	int i;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Erreur dans l'initialisation de SDL %s\n",SDL_GetError());
		free(x);
		free(y);
		free(z);
		return -1;
	}
				
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Event quit;
				
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
		SDL_PollEvent(&quit);
  		if(quit.type == SDL_QUIT)
    	{
    		SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			free (x);
			free (y);
			free (z);
			SDL_Quit();
	return 0;
    	}

		
		quadri(x,y,z,d,xp,yp,renderer);
		for (i = 0; i < 10; ++i)//17 pr cube
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

	
}
void quadri(float* x,float* y,float* z, float d,float xp,float yp,SDL_Renderer * renderer)
{
	float xs;
	float ys;
	int i;
	for (i = 0; i < 10-1; ++i)//16 pr cube
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


