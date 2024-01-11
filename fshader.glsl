#version 330 core


struct DirectionalLight {
	vec4 ambient, diffuse, specular, direction;
};


struct Material {
	float shininess;
	vec4 ambient, diffuse, specular;
};

in vec3 normal, position;
in vec2 texCoord;

uniform vec3 camera;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform sampler2D tex;

out vec4 color;

vec4 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(camera - position);

	vec4 result = CalculateDirectionalLight(directionalLight, norm, viewDir);

	color = result;

	color.a = 1.0;
}



vec4 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) 
{
	vec4 ambient = light.ambient * material.ambient * texture(tex, texCoord);

	vec3 lightDir = normalize(- light.direction.xyz);

	float Kd = max(dot(normal, lightDir), 0.0);
	vec4 diffuse = Kd * light.diffuse * material.diffuse * texture(tex, texCoord);

	vec3 reflectDir = reflect(-lightDir, normal);
	float Ks = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec4 specular = Ks * light.specular * material.specular * texture(tex, texCoord);

	return ambient + diffuse + specular;
}
