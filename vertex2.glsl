#version 330 core
layout (location = 0) in vec3 vPos;		//--- 응용 프로그램에서 받아온 도형 좌표값
layout (location = 1) in vec2 vTexCoord;	//--- 응용 프로그램에서 받아온 도형 uv값

out vec2 TexCoord;

//uniform mat4 modelTransform; //--- 모델링 변환 행렬: uniform 변수로 선언
//uniform mat4 viewTransform; projectionTransform * viewTransform * modelTransform *
//uniform mat4 projectionTransform;

void main()
{
	gl_Position = vec4(vPos, 1.0);
	TexCoord = vTexCoord;
}