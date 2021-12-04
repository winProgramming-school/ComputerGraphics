#version 330 core
layout (location = 0) in vec3 vPos;		//--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
layout (location = 1) in vec2 vTexCoord;	//--- ���� ���α׷����� �޾ƿ� ���� uv��

out vec2 TexCoord;

uniform mat4 modelTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0); //--- ��ǥ���� modelTransform ��ȯ�� �����Ѵ�.
	TexCoord = vTexCoord;
}