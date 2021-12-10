#version 330 core
//--- out_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- FragColor: ����� ������ ������ ������ ���۷� ���� ��. 

out vec4 FragColor; //--- ���� ���

in vec2 TexCoord;

uniform sampler2D texture1; //--- texture sampler texture1

void main(void) 
{
	vec3 result;
	result = vec3(texture(texture1, TexCoord).x, texture(texture1, TexCoord).y, texture(texture1, TexCoord).z);
	FragColor = vec4(result, 0.5f);
	//FragColor = (texture (texture1, TexCoord) + texture (texture2, TexCoord) ) / 2.0; 
}
