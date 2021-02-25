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
