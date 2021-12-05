#version 330 core
layout (location = 0) in vec3 vPos;		//--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
layout (location = 1) in vec2 vTexCoord;	//--- ���� ���α׷����� �޾ƿ� ���� uv��

out vec2 TexCoord;

//uniform mat4 modelTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����
//uniform mat4 viewTransform; projectionTransform * viewTransform * modelTransform *
//uniform mat4 projectionTransform;

void main()
{
	gl_Position = vec4(vPos, 1.0);
	TexCoord = vTexCoord;
}