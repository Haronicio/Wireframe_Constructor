/*optimisation mineure
Compteur de FPS*/  
/*                                      
  _____ _    _          _   _  _____ ______ _      ____   _____ 
 / ____| |  | |   /\   | \ | |/ ____|  ____| |    / __ \ / ____|
| |    | |__| |  /  \  |  \| | |  __| |__  | |   | |  | | |  __ 
| |    |  __  | / /\ \ | . ` | | |_ |  __| | |   | |  | | | |_ |
| |____| |  | |/ ____ \| |\  | |__| | |____| |___| |__| | |__| |
 \_____|_|  |_/_/    \_\_| \_|\_____|______|______\____/ \_____|*/


/*-------Inclusion compilateur-------*/
	#include <SDL.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <string.h>
	#include <time.h>
/*-------Inclusion externe-------*/
	#include "shapeinput.h"
/*-------Directive-------*/
	#define TRUE 1
	#define FALSE 0

enum type_of_render {Software, Accelered};
enum type_of_render rendu_1 = Accelered;
int size;
int main(int argc, char *argv[])
{

	if (SDL_GetNumRenderDrivers() < 0)
	{
		printf("---------------------------------------\n|Alerte : pas d'accélération matérielle|\n---------------------------------------\n");
		SDL_Delay(3000);
		rendu_1 = Software;
	}
	printf("-----------------------------------\n|Acceleration materielle disponible|\n-----------------------------------\n");
	printf("RAM : %d Mo\n",SDL_GetSystemRAM() );
	void quadri(float* x,float* y,float* z,float d, float xp ,float yp,SDL_Renderer * renderer);
	void clear(SDL_Renderer * renderer);

	/*FPS*/
	float FPS(int * t);
	int actual_time = SDL_GetTicks();
	int * Frameclock = &actual_time;
	// float temp1 = 0;
	// float temp2 = 0;
	printf("%d\n",(int)CLOCKS_PER_SEC );

	float* x;
	float* y;
	float* z;
	x = calloc(40000,sizeof(float));//150
	y = calloc(40000,sizeof(float));
	z = calloc(40000,sizeof(float));
	// double pi = 3.14159265358979323846264338327950288419716939937510;
	int Largeur = 800;
	int Hauteur = 600;
	
	// int Ox = Largeur/2;
	// int Oy = Hauteur/2;							   //10
	// float x[17]={-50,50, 50,-50,-50,-50, 50, 50,-50,-50,-50,50, 50, 50, 50,-50,-50};
	// float y[17]={ 50,50,-50,-50, 50, 50, 50,-50,-50, 50, 50,50, 50,-50,-50,-50,-50};
	// float z[17]={ 50,50, 50, 50, 50,-50,-50,-50,-50,-50, 50,50,-50,-50, 50, 50,-50};
	
	size = input(x,y,z);
	printf("%d\n",size );
	printf("Welcome !\n");
	SDL_Delay(1000);


	float angleX = 0;
	float angleY = 0.4;
	float angleZ = 0;


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
	renderer = SDL_CreateRenderer(window,-1,rendu_1);//SDL_RENDERER_SOFTWARE//SDL_RENDERER_ACCELERATED      ACCELERATED = 2*SOFTWARE
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
    	
    	/*FPS*/
    	// temp1 = temp2;
    	// temp2 = SDL_GetTicks();
    	// printf("FPS :%f\n",/*FPS*/ 1/((temp2 - temp1)/CLOCKS_PER_SEC ));
    	printf("FPS :%f\n", FPS(Frameclock));

		quadri(x,y,z,d,xp,yp,renderer);
		SDL_RenderPresent(renderer);	
		for (i = 0; i < size; ++i)//17 pr cube
		{
			
			/*rotation axe Z*/
			if (angleZ != 0)
			{
				xp = x[i]* cos(angleZ/57.2958) - y[i] * sin(angleZ/57.2958);
				y[i] = y[i]* cos(angleZ/57.2958) + x[i] * sin(angleZ/57.2958);
				x[i]=xp;
				// printf("%f %f\n",x[i],y[i] );
			}
		
		

			/*rotation axe X*/
			if (angleX != 0)
			{
				zp = z[i]* cos(angleX/57.2958) - y[i] * sin(angleX/57.2958);
				y[i] = y[i]* cos(angleX/57.2958) + z[i] * sin(angleX/57.2958);
				z[i]=zp;
				// printf("%f %f\n",z[i],y[i] );
			}
		


			/*rotation axe Y*/
			if (angleY != 0)
			{
				xp = x[i]* cos(angleY/57.2958) - z[i] * sin(angleY/57.2958);
				z[i] = z[i]* cos(angleY/57.2958) + x[i] * sin(angleY/57.2958);
				x[i]=xp;
				// printf("%f %f\n",x[i],z[i] );
			}
		}

		// SDL_Delay(00)
		clear(renderer);
	}

	
}
void quadri(float* x,float* y,float* z, float d,float xp,float yp,SDL_Renderer * renderer)
{
	float xs;
	float ys;
	int i;
	int zoom = 1;//13
	int clipx = 100;
	int clipy = 100;
	for (i = 0; i < size -1; ++i)//16 pr cube
	{

		
		xp=(d*x[i])/(d+z[i]);
		yp=(d*y[i])/(d+z[i]);
		xs=(d*x[i+1])/(d+z[i+1]);
		ys=(d*y[i+1])/(d+z[i+1]);
		SDL_RenderDrawLine(renderer,(xp+clipx)*zoom,(yp+clipy)*zoom,(xs+clipx)*zoom,(ys+clipy)*zoom);//400 300 400 300
		// printf("%f %f\n",x[i],y[i] );

	}	

	
}
void clear(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
}

float FPS(int * t)
{
	float t_last = SDL_GetTicks();
	float FPS = 1/((t_last - *t)/CLOCKS_PER_SEC );
	*t = t_last;
	return FPS;
}
	



// Suppression des doublons rapidité /2
/*void quadri(float* x,float* y,float* z, float d,float xp,float yp,SDL_Renderer * renderer)
{
	float xs;
	float ys;
	int i,j;
	int vect[size][2];
	for (i = 0; i < size -1; ++i)
	{

		vect [i][0]= x[i+1]-x[i];
		vect [i][1]= y[i+1]-x[i];
		for (j = 0; j < size; ++j)
		{
			if (fabs(vect [i][0]) != fabs(vect [j][0]) && fabs(vect [i][0]) != fabs(vect [j][0]))
			{
				xp=(d*x[i])/(d+z[i]);
				yp=(d*y[i])/(d+z[i]);
				xs=(d*x[i+1])/(d+z[i+1]);
				ys=(d*y[i+1])/(d+z[i+1]);
				SDL_RenderDrawLine(renderer,xp+400,yp+300,xs+400,ys+300);
				printf("%f %f\n",x[i],y[i] );
			}
			else
			{
				printf("doublon\n");
			}
		}
		
		
		
	}	
	SDL_RenderPresent(renderer);
}
*/