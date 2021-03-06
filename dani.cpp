#include "c:/verano2014/shell.cpp"
#include <limits.h>
#include <stdlib.h>

Window W("prueba",950,590);

typedef struct{ int nr, nc; COLORREF **img;
}imagen;

typedef struct{ imagen img; int posx, posy;
}accesorio;

typedef struct{ imagen img; int posx, posy; bool dispara;
}bala;

imagen pez, pantalla, fondo, menu, menu1, bomba, pez1, pez01, pez2, pezmuerte, coli;
imagen uno, dos, tres, cuatro, cinco, seis, siete, ocho, nueve, cero, puntaje;

imagen tiburon, pezespada, tiburon2, tiburonmuerto, instrucciones;
accesorio estrella, cangrejo;
bala bala1, bala2, bala3;
int max;
int ypos[4]={-120, -220, -440, -190};
COLORREF **Matrizcol(int n, int m);

int Nivel_2();
void Clic(int *gravedad, int y);
void Libera(imagen *miImagen);
void leeImagen(imagen *miImagen, char *dic);
void LeeImagenes();
void LeeImagenes2();
void LiberaImagenes2();
int pegaimagenBALA(imagen miImagen, imagen miImagen1, int x, int y);
int Nivel_1();
void Marcador(imagen a, int cont, int x, int y);
void reiniciapantalla();
void LiberaImagenes();
void pegaimagen(imagen miImagen, imagen miImagen1 ,int x, int y);
int pegaimagenPez(imagen miImagen, imagen miImagen1 ,int x, int y);
void Bomba(int xbomba1, int xbomba2, int xbomba3, int ybomba1, int ybomba2, int ybomba3);
int Menu();

int main()
{
	FILE *da;
	da=fopen("puntaje.txt","rt");
	fscanf(da,"%d", &max);
	fclose(da);
	int k, estado=1, z, w;
	while(estado==1)
	{
		k=Menu();
		if(k==0)
		{
			return 1;
		}
		if(k==1)
		{
			W.Cls();
			leeImagen(&instrucciones,"instrucciones1.bmp");
			W.PlotCBitmap(instrucciones.img,instrucciones.nr,instrucciones.nc, 0 ,0 , 1);
			while(1)
			{
				if(MouseHit(&z,&w)==1)
				{
					estado=Nivel_1();
					LiberaImagenes();
					break;
				}
			}
		}
		if(k==2)
		{
			W.Cls();
			leeImagen(&instrucciones,"instrucciones2.bmp");
			W.PlotCBitmap(instrucciones.img,instrucciones.nr,instrucciones.nc, 0 ,0 , 1);
			while(1)
			{
				if(MouseHit(&z,&w)==1)
				{
					estado=Nivel_2();
					LiberaImagenes2();
					break;
				}
			}
		}
	}
}


int Menu()
{
	int x, y;
	leeImagen(&menu, "menu.bmp");
	leeImagen(&menu1, "menu1.bmp");
	pegaimagen(menu1, menu, 50 , 150 );
	W.PlotCBitmap(menu.img, menu.nr, menu.nc,0,-8,1);
	while(1)
	{
		if(MouseHit(&x,&y)==1)
		{
			if(x>120&&x<270&&y>200&&y<250)
			{
				Libera(&menu);
				Libera(&menu1);
				return 1;
			}
			if(x>120&&x<270&&y>270&&y<320)
			{
				Libera(&menu);
				Libera(&menu1);
				return 2;
			}
			if(x>120&&x<270&&y>340&&y<400)
			{
				Libera(&menu);
				Libera(&menu1);
				return 0;
			}
		}
	}
	
}    
int Nivel_1()
{
	randomize();
	int x=300, y=150, gravedad=0, velocidad=5, choque=0, cont=0, estado, v=1;
	int xbomba1=1210, xbomba2=1610, xbomba3=2010 ,ybomba1=ypos[(random(32)*3)%4], ybomba2=ypos[(random(45)+3)%4], ybomba3=ypos[(random(45)+1)%4];
	estrella.posx=1300;
	estrella.posy=550;
	cangrejo.posx=1500+ random(1000);
	cangrejo.posy=550;
	LeeImagenes();
	pegaimagen(pez, pantalla, x, y);
	W.PlotCBitmap(pantalla.img,pantalla.nr,pantalla.nc,0,0,1);
	reiniciapantalla();
	unsigned int k;
	while(1)
	{
		
		xbomba1-=velocidad;
		xbomba2-=velocidad;
		xbomba3-=velocidad;
		gravedad++;
		y=y+gravedad;
		if(xbomba1 <= -90)
		{
			xbomba1=1150;
			ybomba1=ypos[random(43)%4];
		}
		if(xbomba2 <= -90)
		{
			xbomba2=1150;
			ybomba2=ypos[random(30)%4];
		}
		if(xbomba3 <= -90)
		{
			xbomba3=1150;
			ybomba3=ypos[random(20)%4];
		}
		Bomba(xbomba1, xbomba2, xbomba3, ybomba1, ybomba2, ybomba3);
		pegaimagen(estrella.img,pantalla,estrella.posx,estrella.posy);
		pegaimagen(cangrejo.img,pantalla,cangrejo.posx,cangrejo.posy);
		estrella.posx-=5;
		cangrejo.posx-=5;
		if(estrella.posx<-90)
		{
			estrella.posx=random(300)+1300;
		}
		if(cangrejo.posx<-90)
		{
			cangrejo.posx=1800+random(1000);
		}
		if(choque==1||y>=500)
		{
			coli.nc=pantalla.nc;
			coli.nr=pantalla.nr;
			coli.img=Matrizcol(pantalla.nr,pantalla.nc);
			for(int j=0;j<pantalla.nr;j++)
			{
				for(int i=0;i<pantalla.nc;i++)
				{
					coli.img[j][i]=pantalla.img[j][i];
				}
			}
			for(int k=y;k<550;k+=15)
			{
				pegaimagen(pezmuerte, coli, x, k);
				if(cont>max)
				{
					max=cont;
					FILE *da;
					da=fopen("puntaje.txt","wt");
					fprintf(da,"%d",max);
				}
				Marcador(coli,cont,200,10);
				Marcador(coli,max,200,100);
				pegaimagen(puntaje, coli, 0,0);
				W.PlotCBitmap(coli.img,pantalla.nr,pantalla.nc,0,0,1);
				for(int j=0;j<pantalla.nr;j++)
				{
					for(int i=0;i<pantalla.nc;i++)
					{
						coli.img[j][i]=pantalla.img[j][i];
					}
				}
			}
			MessageOk("Adios");
			return 1;
		}
		if(gravedad<8)
		{
			if(v%19==0)
			{
				choque=pegaimagenPez(pez01, pantalla, x, y);
			}
			else
			{
				choque=pegaimagenPez(pez1, pantalla, x, y);
			}
			v++;
			if(v==1001) v=1;
		}
		if(gravedad>=8&&gravedad<=13)
		{
			choque=pegaimagenPez(pez, pantalla, x, y);
		}
		if(gravedad>13)
		{
			choque=pegaimagenPez(pez2, pantalla, x, y);
		}
		if(xbomba1>220&&xbomba1<226)
		{
			cont++;
			estado=1;
		}
		if(xbomba2>220&&xbomba2<226)
		{
			cont++;
			estado=1;
		}
		if(xbomba3>220&&xbomba3<226)
		{
			cont++;
			estado=1;
		}
		Marcador(pantalla,cont, 450, 0);
		W.PlotCBitmap(pantalla.img,pantalla.nr,pantalla.nc,0,0,1);
		reiniciapantalla();
		Clic(&gravedad, y);
	}
	MessageOk("holi");
}

int Nivel_2()
{
	LeeImagenes2();
	int x=0, y=100, vx=15, vy=15, kk, estado=0, xt=820, yt=0, vyt=12, contbala=0, vidapez, vidatiburon=3, tiempo=0, lechito=0;
	int contcarga=0, aux=0;
	unsigned int k;
	pegaimagen(pezespada,pantalla,x,y);
	pegaimagen(tiburon,pantalla, xt, yt);
	W.PlotCBitmap(pantalla.img,pantalla.nr,pantalla.nc,0,0,1);
	reiniciapantalla();
	bala1.dispara=false;
	bala2.dispara=false;
	bala3.dispara=false;
	while(1)
	{
		tiempo++;
		if(tiempo%900==899)
		{
			estado=1;
		}
		if(tiempo==900)	tiempo=1;
		kk=Kbhit(&k);
		if(kk==1)
		{
			switch(k)
			{
				case 37:
					{
						if(estado==1)
						{
							x=x-vx;
						}
						break;
					}
				case 38:
					{
						y=y-vy;
						break;
					}
				case 39:
					{
						if(estado==1)
						{
							x+=vx;
						}
						break;
					}
				case 40:
					{
						y+=vy;
						break;
					}
			}
		}
		if(x<0)
		{
			x=0;
		}
		if(x>900)
		{
			x=870;
		}
		if(y<0)
		{
			y=0;
		}
		if(y>520)
		{
			y=520;
		}
		if(estado==0)
		{
			yt+=vyt;
			if(yt>520||yt<0)
			{
				vyt=-vyt;
			}
			if(contbala%60==0&&bala1.dispara==false)
			{
				bala1.posy=yt+50;
				bala1.posx=xt;
				bala1.dispara=true;
			}
			if(bala1.dispara)
			{
				pegaimagen(bala1.img,pantalla, bala1.posx, bala1.posy);
				bala1.posx-=20;
				if(bala1.posx<0)
				{
					bala1.dispara=false;
				}
			}
			if(contbala%60==20&&bala2.dispara==false)
			{
				bala2.posy=yt+50;
				bala2.posx=xt;
				bala2.dispara=true;
			}
			if(bala2.dispara)
			{
				pegaimagen(bala2.img,pantalla, bala2.posx, bala2.posy);
				bala2.posx-=20;
				if(bala2.posx<0)
				{
					bala2.dispara=false;
				}
			}
			if(contbala%60==40&&bala3.dispara==false)
			{
				bala3.posy=yt+50;
				bala3.posx=xt;
				bala3.dispara=true;
			}
			if(bala3.dispara)
			{
				pegaimagen(bala3.img,pantalla, bala3.posx, bala3.posy);
				bala3.posx-=20;
				if(bala3.posx<0)
				{
					bala3.dispara=false;
				}
			}
			if(vidapez==1)
			{
				reiniciapantalla();
				pegaimagen(tiburon,pantalla,xt,yt);
				pegaimagen(pezmuerte,pantalla,x,y);
				W.PlotCBitmap(pantalla.img,pantalla.nr,pantalla.nc,0,0,1);
				MessageOk("Moriste");
				return 1;
			}
			contbala++;
			if(contbala==10000) contbala=0;
		}
		if(estado==1)
		{
			yt+=vyt;
			if(yt>520||yt<0)
			{
				vyt=-vyt;
			}
			pegaimagen(pezespada,pantalla,x,y);
			lechito=pegaimagenBALA(tiburon2,pantalla,xt,yt);
			if(lechito==1)
			{
				pegaimagen(tiburonmuerto,pantalla,xt,yt);
				W.PlotCBitmap(pantalla.img,pantalla.nr,pantalla.nc,0,0,1);
				MessageOk("Ganaste");
				return 1;
			}
			
		}
		pegaimagen(tiburon,pantalla, xt, yt);
		if(estado==0)
		{
			vidapez=pegaimagenBALA(pezespada,pantalla,x,y);
		}
		W.PlotCBitmap(pantalla.img,pantalla.nr,pantalla.nc,0,0,1);
		reiniciapantalla();
	}
	return 1;
}

void Marcador(imagen a, int cont, int x, int y)
{
	int unidades, decenas;
	unidades=cont%10;
	decenas=(cont-unidades)/10;
	switch(unidades)
	{
		case 0: 
		{
			leeImagen(&cero,"0.bmp");
			pegaimagen(cero,a,x,y);
			Libera(&cero);
			break;
		}
		case 1: 
		{
			leeImagen(&uno,"1.bmp");
			pegaimagen(uno,a,x,y);
			Libera(&uno);
			break;
		}
		case 2: 
		{
			leeImagen(&dos,"2.bmp");
			pegaimagen(dos,a,x,y);
			Libera(&dos);
			break;
		}
		case 3: 
		{
			leeImagen(&tres,"3.bmp");
			pegaimagen(tres,a,x,y);
			Libera(&tres);
			break;
		}
		case 4: 
		{
			leeImagen(&cuatro,"4.bmp");
			pegaimagen(cuatro,a,x,y);
			Libera(&cuatro);
			break;
		}
		case 5: 
		{
			leeImagen(&cinco,"5.bmp");
			pegaimagen(cinco,a,x,y);
			Libera(&cinco);
			break;
		}
		case 6:
			{
				leeImagen(&seis,"6.bmp");
				pegaimagen(seis,a,x,y);
				Libera(&seis);
				break;
			}
		case 7:
			{
				leeImagen(&siete,"7.bmp");
				pegaimagen(siete,a,x,y);
				Libera(&siete);
				break;
			}
		case 8:
			{
				leeImagen(&ocho,"8.bmp");
				pegaimagen(ocho,a,x,y);
				Libera(&ocho);
				break;
			}	
		case 9:
			{
				leeImagen(&nueve,"9.bmp");
				pegaimagen(nueve,a,x,y);
				Libera(&nueve);
				break;
			}
	}
	switch(decenas)
	{
		case 0: 
		{
			break;
		}
		case 1: 
		{
			leeImagen(&uno,"1.bmp");
			pegaimagen(uno,a,x-50,y);
			Libera(&uno);
			break;
		}
		case 2: 
		{
			leeImagen(&dos,"2.bmp");
			pegaimagen(dos,a,x-50,y);
			Libera(&dos);
			break;
		}
		case 3: 
		{
			leeImagen(&tres,"3.bmp");
			pegaimagen(tres,a,x-50,y);
			Libera(&tres);
			break;
		}
		case 4: 
		{
			leeImagen(&cuatro,"4.bmp");
			pegaimagen(cuatro,a,x-50,y);
			Libera(&cuatro);
			break;
		}
		case 5: 
		{
			leeImagen(&cinco,"5.bmp");
			pegaimagen(cinco,a,x-50,y);
			Libera(&cinco);
			break;
		}
		case 6:
			{
				leeImagen(&seis,"6.bmp");
				pegaimagen(seis,a,x-50,y);
				Libera(&seis);
				break;
			}
		case 7:
			{
				leeImagen(&siete,"7.bmp");
				pegaimagen(siete,a,x-50,y);
				Libera(&siete);
				break;
			}
		case 8:
			{
				leeImagen(&ocho,"8.bmp");
				pegaimagen(ocho,a,x-50,y);
				Libera(&ocho);
				break;
			}	
		case 9:
			{
				leeImagen(&nueve,"9.bmp");
				pegaimagen(nueve,a,x-50,y);
				Libera(&nueve);
				break;
			}
	}
}

void Bomba(int xbomba1, int xbomba2, int xbomba3, int ybomba1, int ybomba2, int ybomba3)
{
	for(int j=0; j<bomba.nr; j++)
	{
		for(int i=0; i<bomba.nc; i++)
		{
			if( ybomba1+j>0 && ybomba1+j< pantalla.nr  && xbomba1+i>0 && xbomba1+i < pantalla.nc)
			{
				if(bomba.img[j][i]!=RGB(0,255,0))
				{
					pantalla.img[j+ybomba1][i+xbomba1]=bomba.img[j][i];
				}
			}
			if( ybomba2+j>0 && ybomba2+j< pantalla.nr  && xbomba2+i>0 && xbomba2+i < pantalla.nc)
			{
				if(bomba.img[j][i]!=RGB(0,255,0))
				{
					pantalla.img[j+ybomba2][i+xbomba2]=bomba.img[j][i];
				}
			}
			if( ybomba3+j>0 && ybomba3+j< pantalla.nr  && xbomba3+i>0 && xbomba3+i < pantalla.nc)
			{
				if(bomba.img[j][i]!=RGB(0,255,0))
				{
					pantalla.img[j+ybomba3][i+xbomba3]=bomba.img[j][i];
				}
			}
		}
	}	
}

void LiberaImagenes2()
{
	Libera(&tiburon);
	Libera(&pezespada);
	Libera(&tiburon2);
	Libera(&tiburonmuerto);
}

void LiberaImagenes()
{
	Libera(&pez);
	Libera(&pez01);
	Libera(&pez1);
	Libera(&pez2);
	Libera(&pezmuerte);
	Libera(&pantalla);
	Libera(&fondo);
	Libera(&bomba);
	Libera(&coli);
}

void Clic(int *gravedad, int y)
{
	int g, h;
		if(MouseHit(&g,&h)==1)
		{
			*gravedad=-12;
		}
		if(y<5)
		{
			*gravedad=5;
		}
}

void reiniciapantalla()
{
	for(int v=0; v<pantalla.nr; v++)
		{
			for(int u=0;u<pantalla.nc; u++)
			{
				pantalla.img[v][u]=fondo.img[v][u];
			}
		}
}

void pegaimagen(imagen miImagen, imagen miImagen1, int x, int y)
{
	for(int j=0; j<miImagen.nr; j++)
	{
		for(int i=0; i<miImagen.nc; i++)
		{
			if( y+j>0 && y+j< miImagen1.nr  && x+i>0 && x+i < miImagen1.nc)
			{
				if(miImagen.img[j][i]!=RGB(0,255,0))
				{
					miImagen1.img[j+y][i+x]=miImagen.img[j][i];
				}
			}
		}
	}
}

int pegaimagenBALA(imagen miImagen, imagen miImagen1, int x, int y)
{
	int choque=0;
	for(int j=0; j<miImagen.nr; j++)
	{
		for(int i=0; i<miImagen.nc; i++)
		{
			if( y+j>0 && y+j< miImagen1.nr  && x+i>0 && x+i < miImagen1.nc)
			{
				if(miImagen1.img[j+y][i+x]==RGB(255,0,0))
				{
					choque=1;
				}
				if(miImagen.img[j][i]!=RGB(0,255,0))
				{
					miImagen1.img[j+y][i+x]=miImagen.img[j][i];
				}
			}
		}
	}
	return choque;
}

int pegaimagenPez(imagen miImagen, imagen miImagen1 ,int x, int y)
{
	int choque=0;
	for(int j=0; j<miImagen.nr; j++)
	{
		for(int i=0; i<miImagen.nc; i++)
		{
			if( y+j>0 && y+j< miImagen1.nr  && x+i>0 && x+i < miImagen1.nc)
			{
				if(miImagen.img[j][i]!=RGB(0,255,0))
				{
					if(miImagen1.img[j+y][i+x]==RGB(0,0,0))
					{
						choque=1;
					}
					miImagen1.img[j+y][i+x]=miImagen.img[j][i];
				}
			}
		}
	}
	return choque;
}

void LeeImagenes2()
{
	leeImagen(&fondo,"fondo2.bmp");
	leeImagen(&pantalla,"fondo2.bmp");
	leeImagen(&pezespada,"Jimmyespada.bmp");
	leeImagen(&tiburon,"TiburonManuel.bmp");
	leeImagen(&(bala1.img),"bala.bmp");
	leeImagen(&(bala2.img),"bala.bmp");
	leeImagen(&(bala3.img),"bala.bmp");
	leeImagen(&pezmuerte,"JimmyMuerte.bmp");
	leeImagen(&tiburon2,"TiburonManuel1.bmp");
	leeImagen(&tiburonmuerto,"TiburonManuel2.bmp");
}

void LeeImagenes()
{
	leeImagen(&pez,"Jimmy.bmp");
	leeImagen(&pantalla, "Fondo1.bmp");
	leeImagen(&fondo, "Fondo1.bmp");
	leeImagen(&bomba, "bomba1.bmp");
	leeImagen(&pez1,"Jimmy1.bmp");
	leeImagen(&pez01,"Jimmy01.bmp");
	leeImagen(&pez2,"Jimmy2.bmp");
	leeImagen(&pezmuerte,"JimmyMuerte.bmp");
	leeImagen(&(estrella.img),"estrella.bmp");
	leeImagen(&(cangrejo.img),"cangrejo.bmp");
	leeImagen(&puntaje,"puntaje.bmp");	
}  

void Libera(imagen *miImagen)
{
	for(int i=0; i<miImagen->nr; i++)
	{
		free((miImagen->img)[i]);
	}
	free(miImagen->img);
}

void leeImagen(imagen *miImagen, char *dic)
{
	DimensionesBmp(dic, &(miImagen->nr), &(miImagen->nc));
	miImagen->img=Matrizcol(miImagen->nr,miImagen->nc);
	LeeBmpColor(miImagen->img,dic);
}

COLORREF **Matrizcol(int n, int m)
{
	COLORREF **a;
	a=(COLORREF**)malloc(n*sizeof(COLORREF*));
	for(int i=0;i<n;i++)
	{
		a[i]=(COLORREF*)malloc(m*sizeof(COLORREF));
	}
	return a;
}
