#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


class Shader
{
public:
    unsigned int ID;

    // 생성자는 shader를 읽고 생성합니다.
    void InitShader(const char* vertexPath, const char* fragmentPath);
    // shader를 활성화하고 사용합니다.
    void use();
};
#endif