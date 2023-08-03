// This is a texture plus flat color shader combination

#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoordinates;
layout(location = 3) in float a_TextureIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;
// uniform mat4 u_Transform;

out vec4 v_Color;
out vec2 v_TextureCoordinates;
out float v_TextureIndex;
out float v_TilingFactor;


void main(){
	v_Color = a_Color;
	v_TextureCoordinates = a_TextureCoordinates;
	v_TextureIndex = a_TextureIndex;
	v_TilingFactor = a_TilingFactor;

	// gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TextureCoordinates;
in float v_TextureIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];
// uniform sampler2DArray u_Textures;

uniform sampler2D u_Texture00;
uniform sampler2D u_Texture01;
uniform sampler2D u_Texture02;
uniform sampler2D u_Texture03;
uniform sampler2D u_Texture04;
uniform sampler2D u_Texture05;
uniform sampler2D u_Texture06;
uniform sampler2D u_Texture07;
uniform sampler2D u_Texture08;
uniform sampler2D u_Texture09;
uniform sampler2D u_Texture10;
uniform sampler2D u_Texture11;
uniform sampler2D u_Texture12;
uniform sampler2D u_Texture13;
uniform sampler2D u_Texture14;
uniform sampler2D u_Texture15;
uniform sampler2D u_Texture16;
uniform sampler2D u_Texture17;
uniform sampler2D u_Texture18;
uniform sampler2D u_Texture19;
uniform sampler2D u_Texture20;
uniform sampler2D u_Texture21;
uniform sampler2D u_Texture22;
uniform sampler2D u_Texture23;
uniform sampler2D u_Texture24;
uniform sampler2D u_Texture25;
uniform sampler2D u_Texture26;
uniform sampler2D u_Texture27;
uniform sampler2D u_Texture28;
uniform sampler2D u_Texture29;
uniform sampler2D u_Texture30;
uniform sampler2D u_Texture31;


void main(){
	if (v_TextureIndex == 0.0) {
		color =  texture(u_Texture00, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 1.0) {
		color =  texture(u_Texture01, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 2.0) {
		color =  texture(u_Texture02, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 3.0) {
		color =  texture(u_Texture03, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 4.0) {
		color =  texture(u_Texture04, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 5.0) {
		color =  texture(u_Texture05, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 6.0) {
		color =  texture(u_Texture06, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 7.0) {
		color =  texture(u_Texture07, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 8.0) {
		color =  texture(u_Texture08, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 9.0) {
		color =  texture(u_Texture09, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 10.0) {
		color =  texture(u_Texture10, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 11.0) {
		color =  texture(u_Texture11, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 12.0) {
		color =  texture(u_Texture12, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 13.0) {
		color =  texture(u_Texture13, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 14.0) {
		color =  texture(u_Texture14, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 15.0) {
		color =  texture(u_Texture15, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 16.0) {
		color =  texture(u_Texture16, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 17.0) {
		color =  texture(u_Texture17, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 18.0) {
		color =  texture(u_Texture18, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 19.0) {
		color =  texture(u_Texture19, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 20.0) {
		color =  texture(u_Texture20, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 21.0) {
		color =  texture(u_Texture21, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 22.0) {
		color =  texture(u_Texture22, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 23.0) {
		color =  texture(u_Texture23, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 24.0) {
		color =  texture(u_Texture24, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 25.0) {
		color =  texture(u_Texture25, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 26.0) {
		color =  texture(u_Texture26, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 27.0) {
		color =  texture(u_Texture27, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 28.0) {
		color =  texture(u_Texture28, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 29.0) {
		color =  texture(u_Texture29, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 30.0) {
		color =  texture(u_Texture30, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}
	if (v_TextureIndex == 31.0) {
		color =  texture(u_Texture31, v_TextureCoordinates * v_TilingFactor) * v_Color;
	}

	// color =  texture(u_Textures[int(v_TextureIndex)], v_TextureCoordinates * v_TilingFactor) * v_Color;
}