# Assignment 3
### Name: Elias Marjieh
### ID No. 318386646
#
#
#
#
#### Phase 1:
Renderer::InitOpenGLRendering()
This function gets our screen ready to render models on it. 
glGenTextures(1, &gl_screen_tex_); this instruction prepares the texture's identifier in order to use textures.
glGenVertexArrays(1, &gl_screen_vtc_); Arrays (Buffers) that describes the objects that will be rendered on the screen.

The function creates to triangles that contains the content that will be stretched over the screen, basically it replaces our buffers from the previous assignments and GL will make sure everything is rendered correctly and the Z-buffer algorithm is activated.
#### Phase 2:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/MeshModelConstructor.JPG)
The MeshModel constructor now creates a list of vertexes that contains for each vertex its position, normal and texture coordinates (if there is any texture coordinates or normals for the model).
It also prepares the GL buffers, VAO, VBO, vertices and all the data that is needed by the GPU in order to render the models correctly on the screen.

#### Phase 3:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/vshader.JPG)

# vshader code:
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 LightTransformation;
uniform int lightType;
uniform bool VT;
// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

void main()
{
	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader
	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec3(model * vec4(pos, 1.0f));
	fragNormal =  normal;

	// Pass the vertex texture coordinates property as it is. Its interpolated value
	// will be avilable for us in the fragment shader
	if(VT){fragTexCoords = texCoords;}
	else{
	fragTexCoords = orig_fragPos.xy;
	}
	gl_Position = projection * view *  model * vec4(pos, 1.0f);
}

The vshader prepares the data (inputs) for the fragment shader in order to use it for to impolement the shaders.

#### Phase 4:
###### The fragment shader that gives the model a constant color which can be contorled by the ambient color
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
	color=vec4(material.ambientColor,1.f);
}
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/OneColor.JPG)

#### All fragment shader code:


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

#### Phase 5:
void Renderer::Render(Scene& scene)
{
	int cameraCount = scene.GetCameraCount();
	int LightsCount=scene.GetLightCount();
	glm::vec3 AmbientColor[10];
	glm::vec3 DiffuseColor[10];
	glm::vec3 SpecularColor[10];
	glm::vec3 lightsPositions[10];
	glm::mat4x4 lightTransformations[10];
	glm::vec3 lightsDirections[10];
	int lightTypes[10];
	int Alpha[10];
	if (cameraCount > 0)
	{
		int modelCount = scene.GetModelCount();
		const Camera& camera = scene.GetActiveCamera();
		for (int i = 0; i < scene.GetLightCount(); i++)
		{
			Light currentLight = scene.GetLight(i);
			if (currentLight.IsActive()) {
				AmbientColor[i] = currentLight.GetAmbientColor();
				DiffuseColor[i] = currentLight.GetDiffuseColor();
				SpecularColor[i] = currentLight.GetSpecularColor();
				lightsPositions[i] = currentLight.GetPosition();
				lightTransformations[i] = currentLight.GetTransformation();
				lightsDirections[i] = normalize(currentLight.GetDirection());
				lightTypes[i] = currentLight.GetIfPoint();
				Alpha[i] = currentLight.GetAlpha();
			}
			else {
				LightsCount--;
			}
		}
		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
		{
			MeshModel& currentModel = scene.GetModel(currentModelIndex);

			// Activate the 'colorShader' program (vertex and fragment shaders)
			colorShader.use();

			//colorShader.setUniform("reflection", false);
			colorShader.setUniform("AmbientColor", AmbientColor, LightsCount);
			colorShader.setUniform("DiffuseColor", DiffuseColor, LightsCount);
			colorShader.setUniform("SpecularColor", SpecularColor, LightsCount);
			colorShader.setUniform("lightsPositions", lightsPositions, LightsCount);
			colorShader.setUniform("lightTransformations", lightTransformations, LightsCount);
			colorShader.setUniform("LightsTypes", lightTypes, LightsCount);
			colorShader.setUniform("LightsDirections", lightsDirections, LightsCount);
			colorShader.setUniform("LightsCount", LightsCount);
			colorShader.setUniform("eye", normalize(camera.GetEye()));
			colorShader.setUniform("material.diffuseColor", currentModel.GetDiffuseColor());
			colorShader.setUniform("material.specularColor", currentModel.GetSpecularColor());
			colorShader.setUniform("material.ambientColor", currentModel.GetAmbientColor());
			colorShader.setUniform("Alpha", Alpha, scene.GetLightCount());
			colorShader.setUniform("Method", currentModel.GetMethod());
			colorShader.setUniform("model", currentModel.GetWorldTransformation() * currentModel.GetModelTransformation());
			colorShader.setUniform("view", camera.GetViewTransformation());
			colorShader.setUniform("projection", camera.GetProjectionTransformation());
			colorShader.setUniform("material.textureMap", 0);
			colorShader.setUniform("VT", currentModel.GetIfThereIsVT());

			if (currentModel.GetMethod() == 0)
			{
				// Drag our model's faces (triangles) in line mode (wireframe)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
			}
			else if (currentModel.GetMethod() == 2|| currentModel.GetMethod() == 4) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
			}
			else if(currentModel.GetMethod() == 1){
				texture1.bind(0);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
				texture1.unbind(0);
			}
			else if (currentModel.GetMethod() == 3) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBindVertexArray(currentModel.GetVAO());
				glDrawArrays(GL_TRIANGLES, 0, currentModel.GetModelVertices().size());
				glBindVertexArray(0);
			}
		}
	}
}	
In this function we send all the model's properties to the fragment shader in order to render the model in the correct way.
Then we specefy what method we want and according to the method we give the instructions

#### Phase 6:
Demonstrating Phong shading
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/BeetlePhong.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ManyModels.JPG)
In the last picture beethoven and the cow are rendered with phong shading.

#### Phase 7:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/CowWearingBoots.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/TeaPotBlackAndWithe.JPG)
#### Here Beethoven and the cow are phong shaded and watermelons are toon shaded
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ThoseAreMyWaterMelons.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/CrateTextured.JPG)
Those are models with Texture coordinates (The beetle with no texture coordinates).
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/Beetle.JPG)

#### Phase 8:
##### I decided to implement toon shading:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/CrateInToonShading.JPG)
#### Here we can see that part of the models are toon shaded
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ManyModels.JPG)
#### Beethoven, crate and watermelon toon shaded:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/ToonShading.JPG)
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/BeethovenToonShading.jpeg)
## Extras:
![](https://github.com/HaifaGraphicsCourses/computergraphics2021-eliass/blob/master/Assignment3Report/images/WireFrame.JPG)

### Although sometimes it was hard to understand the background calculations and implementations, it was so fun to do this cousre, thank you.
