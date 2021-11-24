#pragma once

#define WINDOW_LENGTH 800
#define WINDOW_HEIGHT 800

// opengl 관련 헤더 파일

#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

// c++ 관련 헤더 파일
#include <math.h>
#include <iostream>
#include <vector>

// 프로그램에 필요한 추가 헤더
#include "Shader.h"
#include "Objloader.h"
#include "GameFramework.h"
#include "scene.h"
#include "MenuScene.h"

