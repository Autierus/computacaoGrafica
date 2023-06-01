#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


#define janela_altura 800
#define janela_largura 800
#define PI 3.1415926535898

float tirX = 5;
float humX = 0;
float humY = 0;
float tiroX = 0;
float tiroY = 0;
float subX = 0;
float subY = 0;
float posX = 0;
float posY = 0;
float movX = 10;
float movY = 0;
float transX = 10;
float transY = 0;
float barX = -200;
bool dir = false;
bool ataque = false;
GLfloat ang, raioX, raioY;

void animaTub(int);
void animaSub(int);
void animaHumano(int);
void animaTiro(int);
void tub(int, int);
void humano(int, int);
void vilao(int, int);
void tubarao(int, int);
void display(void);
void tiro(int, int);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // suporte a janelas
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// PADRAO DE CORES
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("colisao_quadrado"); // cria janela

	//glutFullScreen();
	glutKeyboardFunc(&keyboard); // chama teclado
	glutReshapeFunc(tela); // configura a tela
	glutDisplayFunc(display);

	glutTimerFunc(300, animaTub, 1);
	glutTimerFunc(300, animaSub, 1);
	glutTimerFunc(200, animaHumano, 1);

	glutMainLoop(); // redesenhar
	return(0);
}

void keyboard(unsigned char tecla, int x, int y)
{
	//printf("\ntecla %c\n", tecla);
	//printf("\n\nDigite 1 para esquerda: ");
	//printf("\ntecla %c\n", tecla);
	//printf("\no mouse estava em %d x %d\n\n", x, y);

	if (tecla == 'a')
	{
		dir = false;
		transX = transX - 5;
		posX = posX - 5;
		//printf("\n o valor de translacao e %.2f\n", transX);
	}
	if (tecla == 'd')
	{
		dir = true;
		transX = transX + 5;
		posX = posX + 5;
		//printf("\n o valor de translacao e %.2f\n", transX);
	}
	if (tecla == 's')
	{
		transY = transY - 5;
		barX = barX + 1;
		if ((barX == -201) || (barX == 201)) {
			barX = barX - 1;
		}
		//printf("\n o valor de translacao e %.2f\n", transY);
	}
	if (tecla == 'w')
	{
		transY = transY + 5;
		barX = barX - 1;
		if ((barX == -201) || (barX == 201)) {
			barX = barX + 1;
		}

		//printf("\n o valor de translacao e %.2f\n", transY);
	}
	if (tecla == ' ')
	{
		ataque = true;
		tiroX = transX;
		tiroY = transY;

	}
	


	glutPostRedisplay();

}

void desenhar()
{

	GLfloat circ_pnt = 300;
	GLfloat ang, raioX = 19.0f, raioY = 19.0f;

	//ceu
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f); //azul
	glVertex2f(450, 400);
	glVertex2f(-450, 400);
	glColor3f(1, 1, 0); //amarelo
	glVertex2f(-450, 300);
	glVertex2f(450, 300);
	glEnd();
	glPopMatrix();

	




	//-------HUMANO--------
	glPushMatrix();
	humano(movX, movY);
	glTranslatef(-100, 100, 0);
	humano(movX, movY);
	glPopMatrix();


	//-------HUMANO--------
	glPushMatrix();
		humano(movX, movY);
		glTranslatef(100, 300, 0);
		humano(movX, movY);
	glPopMatrix();

	//----TUbarao--- 
	glPushMatrix();
	glTranslatef(-200, 50, 0);
	tub(movX, movY);
	glPopMatrix();

	//----TUbarao--- 
	glPushMatrix();
	glTranslatef(-400, 100, 0);
	tub(movX, movY);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-500, -200, 0);
		tub(movX, movY);
	glPopMatrix();

	/*glPushMatrix();


	glTranslatef(-200, 60, 0);
	glPushMatrix();
	tubarao(movX, movY);
	glTranslatef(50, 50, 0);
	tubarao(movX, movY);
	glPopMatrix();

	glPopMatrix();*/


	glPushMatrix();
		glTranslatef(500, -100, 0);
		vilao(movX, movY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500, 250, 0);
	vilao(movX, movY);
	glPopMatrix();

	//barra inferior
	glBegin(GL_QUADS);
	glColor3f(0.100, 0.80, 0.80); // cor
	glVertex2f(-450, -250);
	glVertex2f(-450, -400);
	glVertex2f(450, -400);
	glVertex2f(450, -250);
	glEnd();

	//barra de oxigenio
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0); // cor
	glVertex2f(-200, -320);
	glVertex2f(-200, -350);
	glVertex2f(200, -350);
	glVertex2f(200, -320);
	glEnd();

	//valor da barra de oxigenio
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1); // cor
	glVertex2f(barX, -320);
	glVertex2f(barX, -350);
	glVertex2f(200, -350);
	glVertex2f(200, -320);
	glEnd();

	glPushMatrix();

	if (dir) {

		glPushMatrix();

		//meio
		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(0, 0, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor
		glVertex2f(40, 7);
		glVertex2f(120, 0);
		glVertex2f(120, 40);
		glVertex2f(40, 32);
		glEnd();
		glPopMatrix();

		//perna baixa

		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(0, 0, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor
		glVertex2f(40, 0);
		glVertex2f(40, 15);
		glVertex2f(30, 15);
		glVertex2f(30, 0);
		glEnd();
		glPopMatrix();

		//perna de cima
		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(0, 25, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor
		glVertex2f(40, 0);
		glVertex2f(40, 15);
		glVertex2f(30, 15);
		glVertex2f(30, 0);
		glEnd();
		glPopMatrix();


		//torre de cima
		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(75, 33, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor
		glVertex2f(40, 0);
		glVertex2f(40, 25);
		glVertex2f(30, 25);
		glVertex2f(30, 0);
		glEnd();
		glPopMatrix();

		//ponta da torre
		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(80, 48, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor
		glVertex2f(40, 0);
		glVertex2f(40, 10);
		glVertex2f(30, 10);
		glVertex2f(30, 0);
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(120, 43, 0);
		glColor3f(5.4, 2.27, 0.7); // cor amarelo claro
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, (sin(ang) * raioY) - 23);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(120, 45, 0);
		raioX = 8;
		raioY = 8;
		glColor3f(0.0, 0.0, 1.0); // cor 
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, (sin(ang) * raioY) - 23);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();



		glPopMatrix();


	}
	else {


		glPushMatrix();
		//submarino lado esquerdo
		glPushMatrix();


		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor

		glVertex2f(40, 40);
		glVertex2f(120, 32);
		glVertex2f(120, 7);
		glVertex2f(40, 0);

		glEnd();
		glPopMatrix();



		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(75, 33, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor

		glVertex2f(-32, 0);
		glVertex2f(-32, 25);
		glVertex2f(-22, 25);
		glVertex2f(-22, 0);

		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(80, 48, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor

		glVertex2f(-32, 0);
		glVertex2f(-32, 10);
		glVertex2f(-42, 10);
		glVertex2f(-42, 0);

		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(0, 25, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor

		glVertex2f(120, 15);
		glVertex2f(120, 0);
		glVertex2f(130, 0);
		glVertex2f(130, 15);

		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glBegin(GL_QUADS);
		glColor3f(5.4, 2.27, 0.7); // cor

		glVertex2f(120, 15);
		glVertex2f(120, 0);
		glVertex2f(130, 0);
		glVertex2f(130, 15);

		glEnd();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(40, 43, 0);
		glColor3f(5.4, 2.27, 0.7); // cor amarelo claro
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, (sin(ang) * raioY) - 23);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(transX, transY, 0);
		glTranslatef(40, 45, 0);
		raioX = 8;
		raioY = 8;
		glColor3f(0, 0, 1); // cor
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, (sin(ang) * raioY) - 23);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();
	}
	//glPushMatrix();

	
	if (ataque) {
		/*tiro(transX, transY);*/
		glPushMatrix();

		//movimentq o tiro
		glTranslatef(tiroX, tiroY, 0);
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0); //vermelho
		glVertex2f(8, 0);
		glVertex2f(8, 5);
		glVertex2f(0, 5);
		glVertex2f(0, 0);
		glEnd();

		glPopMatrix();

		glutTimerFunc(100, animaTiro, 1);
	}



	//-------HUMANO--------
	//humano(movX, movY);
	//glTranslatef(50, 50, 0);
	//humano(movX, movY);
}



void display()
{

	float distancia = 0;
	float dx = 0;
	float dy = 0;

	dx = 0 - transX;
	dy = 0 - transY;

	distancia = sqrt(dx * dx + dy * dy);
	printf("\n distancia %f\n", distancia);

	glMatrixMode(GL_MODELVIEW); //coordenadas de desenho
	glLoadIdentity();


	if (distancia > (raioX + raioY))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo azul
	}
	else
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // cor do fundo branco
	}


	//if ()
	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA
	// Especificar o local aonde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush(); // execute o desenho
}

void tela(GLsizei w, GLsizei h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// cria a janela (esq, direita, embaixo, em cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);
}

void submarino() {


}

void tubarao(int posisaoX, int posisaoY) {




	glPushMatrix();
	GLfloat circ_pnt = 300;
	GLfloat ang, raioX = 0, raioY = 0;
	glTranslatef(posX, posY, 0);
	//corpo
	glPushMatrix();
	glTranslatef(posX, posY, 0);
	glTranslatef(40, 100, 0);
	raioX = 35;
	raioY = 10;
	glColor3f(50, 1, 1); // cor
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, (sin(ang) * raioY) - 23);
		//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();
	glPopMatrix();

	//olho
	glPushMatrix();
	glTranslatef(posX, posY, 0);
	glTranslatef(58, 100, 0);
	raioX = 3;
	raioY = 3;
	glColor3f(1, 0, 0); // cor
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, (sin(ang) * raioY) - 23);
		//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();
	glPopMatrix();


	//rabo baixo
	glPushMatrix();
	glTranslatef(posX, posY, 0);
	glTranslatef(35, 99, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(60, 1, 1);
	glVertex2f(-45, 2);
	glVertex2f(-35, -35);
	glVertex2f(-10, -25);
	glEnd();
	glPopMatrix();

	//barbatana
	glPushMatrix();
	glTranslatef(posX, posY, 0);
	glTranslatef(35, 99, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(60, 1, 1);
	glVertex2f(2, 5);
	glVertex2f(2, -15);
	glVertex2f(30, -15);

	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void humano(int posisaoX, int posisaoY) {

	glTranslatef(humX, humY, 0);
	//humano
	glPushMatrix();
	glTranslatef(200, 200, 0);

	//cabeca
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0); // cor
	glVertex2f(9, 5);
	glVertex2f(14, 5);
	glVertex2f(14, 10);
	glVertex2f(9, 10);
	glEnd();

	//corpo
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0); // cor
	glVertex2f(15, 3);
	glVertex2f(15, -10);
	glVertex2f(10, -10);
	glVertex2f(10, 3);
	glEnd();

	//braço esquerdo
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0); // cor
	glVertex2f(15, 0);
	glVertex2f(15, -2);
	glVertex2f(-2, -2);
	glVertex2f(-2, 0);
	glEnd();
	//braco direito
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0); // cor
	glVertex2f(15, -1);
	glVertex2f(25, -1);
	glVertex2f(25, -3);
	glVertex2f(15, -3);
	glEnd();
	//perna esquerda
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0); // cor
	glVertex2f(10, -10);
	glVertex2f(8, -10);
	glVertex2f(8, -20);
	glVertex2f(10, -20);
	glEnd();

	//perna direira
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0); // cor
	glVertex2f(15, -10);
	glVertex2f(17, -10);
	glVertex2f(17, -20);
	glVertex2f(15, -20);
	glEnd();

	glPopMatrix();
}

void vilao(int posisaoX, int posisaoY) {
	glTranslatef(subX, subY, 0);
	//corpo
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.0, 0.13); //vermelho
	glVertex2f(60, 0);
	glVertex2f(60, 20);
	glVertex2f(0, 20);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	//rabo
	glPushMatrix();
	glTranslatef(60, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.0, 0.13); //vermelho
	glVertex2f(10, 0);
	glVertex2f(10, 30);
	glVertex2f(-4, 30);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	//torre
	glPushMatrix();
	glTranslatef(10, 20, 0);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.0, 0.13); //vermelho
	glVertex2f(5, 0);
	glVertex2f(5, 15);
	glVertex2f(0, 15);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	//camera
	glPushMatrix();
	glTranslatef(5, 30, 0);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.0, 0.13); //vermelho
	glVertex2f(5, 0);
	glVertex2f(5, 5);
	glVertex2f(0, 5);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	//olho
	glPushMatrix();
	glTranslatef(10, 10, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0); //vermelho
	glVertex2f(5, 0);
	glVertex2f(5, 5);
	glVertex2f(0, 5);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
}

void tiro(int posisaoX, int posisaoY) {

	glPushMatrix();
	glTranslatef(tiroX, tiroY, 0); 
	glBegin(GL_QUADS);
	glColor3f(1, 0 , 0); //vermelho
	glVertex2f(8, 0);
	glVertex2f(8, 5);
	glVertex2f(0, 5);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
}

void animaTiro(int valor) {
	tiroX = tiroX - 2;
	glutPostRedisplay();
	glutTimerFunc(100, animaTiro, 1);
}

void animaTub(int valor) {
	movX = movX + 5;
	glutPostRedisplay();
	glutTimerFunc(300, animaTub, 1);
}

void animaSub(int valor) {
	subX = subX - 5;
	glutPostRedisplay();
	glutTimerFunc(300, animaSub, 1);
}

void animaHumano(int valor) {
	
	if (humY > -450) {
		humY = humY - 4;
		glutPostRedisplay();
		glutTimerFunc(200, animaHumano, 1);
	}
	else {
		

	}
}


void tub(int posisaoX, int posisao) {

	glTranslatef(movX, movY, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0); //Amarelo
	glVertex2f(50, 0);
	glVertex2f(50, 20);
	glVertex2f(0, 15);
	glVertex2f(0, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 10, 0); 
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0); //vermelho
	glVertex2f(5, 0);
	glVertex2f(5, 5);
	glVertex2f(0, 5);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	//barbatana
	glPushMatrix();
	glTranslatef(35, 20, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex2f(-5, 10);
	glVertex2f(-3, 0);
	glVertex2f(10, 0);

	glEnd();
	glPopMatrix();

	//calda
	glPushMatrix();
	glTranslatef(5, 10, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex2f(0, 0);
	glVertex2f(-10, 15);
	glVertex2f(-10, -15);

	glEnd();
	glPopMatrix();

	//calda
	glPushMatrix();
	glTranslatef(60, 10, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex2f(0, 0);
	glVertex2f(-10, 10);
	glVertex2f(-10, -10);

	glEnd();
	glPopMatrix();

}