#include "stdafx.h"
#include "GameFramework.h"

GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid mouse(int button, int state, int x, int y);
GLvoid mouseMotion(int x, int y);

GameFramework GameManager;

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{

	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(WINDOW_LENGTH, WINDOW_HEIGHT); // �������� ũ�� ����
	glutCreateWindow("Rolling Space"); // ������ ����(������ �̸�)

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	GameManager.Create();

	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouse);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ��Լ� ����
	glutTimerFunc(10, TimerFunction, 1);

	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene()
{
	GameManager.OnDraw();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	GameManager.KeyBoard(key, x, y);
	glutPostRedisplay();
}
GLvoid TimerFunction(int value) {
	GameManager.curFrameTime = clock();
	GameManager.OnUpdate(GameManager.GetTick());
	glutTimerFunc(10, TimerFunction, 0);
	GameManager.prevFrameTime = GameManager.curFrameTime;

	glutPostRedisplay();
}
GLvoid mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}
	glutPostRedisplay();
}
GLvoid mouseMotion(int x, int y) {

}
