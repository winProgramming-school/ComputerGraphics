#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


class Shader
{
public:
    unsigned int ID;

    // �����ڴ� shader�� �а� �����մϴ�.
    void InitShader(const char* vertexPath, const char* fragmentPath);
    // shader�� Ȱ��ȭ�ϰ� ����մϴ�.
    void use();
};
#endif