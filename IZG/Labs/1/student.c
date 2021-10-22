/******************************************************************************
 * Laborator 01 - Zaklady pocitacove grafiky - IZG
 * ihulik@fit.vutbr.cz
 *
 * $Id: $
 * 
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * - ibobak@fit.vutbr.cz, orderedDithering
 */

#include "student.h"
#include "globals.h"

#include <time.h>

const int M[] = {
    0, 204, 51, 255,
    68, 136, 187, 119,
    34, 238, 17, 221,
    170, 102, 153, 85
};

const int M_SIDE = 4;

/******************************************************************************
 ******************************************************************************
 Funkce vraci pixel z pozice x, y. Je nutne hlidat frame_bufferu, pokud 
 je dana souradnice mimo hranice, funkce vraci barvu (0, 0, 0).
 Ukol za 0.25 bodu */
S_RGBA getPixel(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height){
        return frame_buffer[ width * y + x];
	}
	else {
    	return COLOR_BLACK; 
	}
}
/******************************************************************************
 ******************************************************************************
 Funkce vlozi pixel na pozici x, y. Je nutne hlidat frame_bufferu, pokud 
 je dana souradnice mimo hranice, funkce neprovadi zadnou zmenu.
 Ukol za 0.25 bodu */
void putPixel(int x, int y, S_RGBA color)
{
	if (x >= 0 && x < width && y >= 0 && y < height){
    	frame_buffer[width * y + x] = color;
   	}
	

}
/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na odstiny sedi. Vyuziva funkce GetPixel a PutPixel.
 Ukol za 0.5 bodu */
void grayScale()
{
	unsigned char intensity;
	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			S_RGBA color = getPixel(x, y);
			intensity = ROUND(color.red * 0.299 + color.green * 0.587 + color.blue * 0.114); 
			color.red =  intensity;
			color.blue = intensity;
			color.green =  intensity;
			putPixel(x, y, color);
		}
    }
}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci algoritmu maticoveho rozptyleni.
 Ukol za 1 bod */

void orderedDithering()
{
	grayScale();
    for (int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            S_RGBA color = getPixel(x, y);
            int i = x % M_SIDE;
            int j = y % M_SIDE;
            if(color.red > M[j*M_SIDE + i]){
                putPixel(x,y, COLOR_WHITE);
			}
            else{
                putPixel(x,y, COLOR_BLACK);
			}
        }
    }
}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci algoritmu distribuce chyby.
 Ukol za 1 bod */
void errorDistribution()
{   
	grayScale();
	int error;
	for (int y = 0; y < height; ++y){	
		for (int x = 0; x < width; ++x){
			S_RGBA color = getPixel(x, y);
			int a = color.red;
			if(a <= 128){
				error = a;
				putPixel(x, y, COLOR_BLACK);
			}
			else{
				error = a - 255;
				putPixel(x, y, COLOR_WHITE);
			}
			int c;
			if(x >= 0 && x < width){
				S_RGBA color= getPixel(x+1,y);
				c = ROUND((3.0/8.0)*error);
				c = color.red + c;
				if(c > 0 && c < 255){
					color.red = c;
					color.blue = c;
					color.green = c;
					putPixel(x+1 , y, color);
				}
				if(c < 0){
					putPixel(x+1, y , COLOR_BLACK);
				}
				if(c > 255){
					putPixel(x+1, y, COLOR_WHITE);
				}
			}
			if(y >= 0 && y < height){
				S_RGBA color= getPixel(x,y+1);
				c = ROUND((3.0/8.0)*error);
				c = color.red + c;
				if(c > 0 && c < 255){
					color.red = c;
					color.blue = c;
					color.green = c;
					putPixel(x, y+1, color);
				}
				if(c < 0){
					putPixel(x, y+1, COLOR_BLACK);
				}
				if(c > 255){
					putPixel(x, y+1, COLOR_WHITE);
				}	
			}
			if(x >= 0 && x < width && y >= 0 && y < height){
				S_RGBA color= getPixel(x+1,y+1);
				c = ROUND((1.0/4.0)*error);
				c = color.red + c;
				if(c > 0 && c < 255){
					color.red = c;
					color.blue = c;
					color.green = c;
					putPixel(x+1, y+1, color);
				}
				if(c < 0){
					putPixel(x+1, y+1, COLOR_BLACK);
				}
				if(c > 255){
					putPixel(x+1, y+1, COLOR_WHITE);
				}		
			}	
		}
	}
}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci metody prahovani.
 Demonstracni funkce */
void thresholding(int Threshold)
{
	/* Prevedeme obrazek na grayscale */
	grayScale();

	/* Projdeme vsechny pixely obrazku */
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			/* Nacteme soucasnou barvu */
			S_RGBA color = getPixel(x, y);

			/* Porovname hodnotu cervene barevne slozky s prahem.
			   Muzeme vyuzit jakoukoli slozku (R, G, B), protoze
			   obrazek je sedotonovy, takze R=G=B */
			if (color.red > Threshold)
				putPixel(x, y, COLOR_WHITE);
			else
				putPixel(x, y, COLOR_BLACK);
		}
}

/******************************************************************************
 ******************************************************************************
 Funkce prevadi obrazek na cernobily pomoci nahodneho rozptyleni. 
 Vyuziva funkce GetPixel, PutPixel a GrayScale.
 Demonstracni funkce. */
void randomDithering()
{
	/* Prevedeme obrazek na grayscale */
	grayScale();

	/* Inicializace generatoru pseudonahodnych cisel */
	srand((unsigned int)time(NULL));

	/* Projdeme vsechny pixely obrazku */
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			/* Nacteme soucasnou barvu */
			S_RGBA color = getPixel(x, y);
			
			/* Porovname hodnotu cervene barevne slozky s nahodnym prahem.
			   Muzeme vyuzit jakoukoli slozku (R, G, B), protoze
			   obrazek je sedotonovy, takze R=G=B */
			if (color.red > rand()%255)
			{
				putPixel(x, y, COLOR_WHITE);
			}
			else
				putPixel(x, y, COLOR_BLACK);
		}
}
/*****************************************************************************/
/*****************************************************************************/