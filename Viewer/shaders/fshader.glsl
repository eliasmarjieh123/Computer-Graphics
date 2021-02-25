

#version 330 core
#define PHONGSHADING 999
#define WIREFRAME 990
#define TEXTURED 900
#define REFLECTION 909



struct Material
{
	sampler2D textureMap;
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 ambientColor;

	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
};

// We set this field's properties from the C++ code
uniform Material material;
uniform int LightsCount;
uniform vec3 AmbientColor[10];
uniform vec3 DiffuseColor[10];
uniform vec3 SpecularColor[10];
uniform vec3 lightsPositions[10];
uniform mat4x4 lightTransformations[10];
uniform vec3 LightsDirections[10];
uniform int LightsTypes[10];
uniform vec3 eye;
uniform int Method;
uniform int Alpha[10];
// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
// The final color of the fragment (pixel)
out vec4 color;

void main()
{
	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
	vec3 I,FinalAmbient,FinalDiffuse,FinalSpecular;
		if(Method==2)	
	     {
		    color=vec4(0.f,0.f,0.f,1.f);
			for(int i=0;i<LightsCount;i++)
			{
				if(LightsTypes[i]==1){I=normalize(fragPos-vec3(lightTransformations[i]* vec4(lightsPositions[i],1.f)));}
				else {I=LightsDirections[i];}
				FinalAmbient=vec3(AmbientColor[i].x*material.ambientColor.x,AmbientColor[i].y*material.ambientColor.y,AmbientColor[i].z*material.ambientColor.z);
				FinalDiffuse=vec3(DiffuseColor[i].x * material.diffuseColor.x, DiffuseColor[i].y * material.diffuseColor.y, DiffuseColor[i].z * material.diffuseColor.z)*dot((-fragNormal), I);
				FinalSpecular = vec3(SpecularColor[i].x * material.specularColor.x, SpecularColor[i].y * material.specularColor.y, SpecularColor[i].z * material.specularColor.z);
				vec3 r = (2.f * dot(-fragNormal, I) * fragNormal - I);
				float Power = pow(max(0.0f, dot((r), (eye))), Alpha[i]);
				FinalSpecular*=Power;
			    color += vec4((FinalSpecular+FinalDiffuse+FinalAmbient),0.f);
			}
		}
		else if(Method==0)
		{
			color=vec4(material.ambientColor,1.f);
		}
		else if(Method==1){
		color=vec4(textureColor,1.f);
		}
		else if(Method==3){
		color=vec4(material.ambientColor.x,material.ambientColor.y,material.ambientColor.z,1.f);
		}
		else{
		   color=vec4(0.f,0.f,0.f,1.f);
           for(int i=0;i<LightsCount;i++)
			{
			if(LightsTypes[i]==1){I=normalize(fragPos-vec3(lightTransformations[i]* vec4(lightsPositions[i],1.f)));}
			else {I=LightsDirections[i];}
			   float intensity = dot(I, fragNormal);
               if(intensity < 0)
                  intensity = 0;
               // Calculate what would normally be the final color, including texturing and diffuse lighting
               vec3 color1 = vec3(fragTexCoords,1.f) * DiffuseColor[i]*  material.diffuseColor;
                // Discretize the intensity, based on a few cutoff points
                if (intensity > 0.95)
                    color1 = vec3(1.0,1,1) * color1;
                else if (intensity > 0.5)
                    color1 = vec3(0.7,0.7,0.7) * color1;
                else if (intensity > 0.05)
                    color1 = vec3(0.35,0.35,0.35) * color1;
                else
                    color1 = vec3(0.1,0.1,0.1) * color1;
              color+=vec4(color1,0.f);
            }
       }
}
