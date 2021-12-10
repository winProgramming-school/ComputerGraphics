#version 330 core
//--- out_Color: 버텍스 세이더에서 입력받는 색상 값
//--- FragColor: 출력할 색상의 값으로 프레임 버퍼로 전달 됨. 

out vec4 FragColor; //--- 색상 출력

in vec2 TexCoord;

uniform sampler2D texture1; //--- texture sampler texture1

void main(void) 
{
	vec3 result;
	result = vec3(texture(texture1, TexCoord).x, texture(texture1, TexCoord).y, texture(texture1, TexCoord).z);
	FragColor = vec4(result, 0.5f);
	//FragColor = (texture (texture1, TexCoord) + texture (texture2, TexCoord) ) / 2.0; 
}
