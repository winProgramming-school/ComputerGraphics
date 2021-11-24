#version 330 core

in vec3 FragPos; //--- ��ġ��
in vec3 Normal; //--- ���ؽ� ���̴����� ���� ��ְ�
out vec4 FragColor; //--- ���� ���

uniform vec3 inputColor;
uniform vec3 texCoord;
uniform vec3 lightPos; //--- ������ ��ġ
uniform vec3 lightColor; //--- ������ ��

uniform vec3 viewPos;

void main(void) 
{
	float ambientLight = 0.5;
	vec3 ambient = ambientLight * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseLight = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = diffuseLight * lightColor;

	int shininess = 128;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float specularLight = max(dot(viewDir, reflectDir), 0.0);
	specularLight = pow(specularLight, shininess);
	vec3 specular = specularLight * lightColor;

	vec3 result = (ambient + diffuse + specular) * inputColor;

	FragColor = vec4(result, 1.0f);
}