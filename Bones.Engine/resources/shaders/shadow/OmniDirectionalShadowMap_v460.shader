VERTEX_SHADER
#version 460

layout(location = 0) in vec3 a_position;

uniform mat4 u_transform;

void main()
{
	// world pos
	gl_Position = u_transform * vec4(a_position, 1.0);
}

GEOMETRY_SHADER
#version 460

layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

uniform mat4 u_lightProjectionView[6];

out vec4 v_fragmentPos;

void main()
{
	// for each face of cube map
	for (int face = 0; face < 6; face++)
	{
		// use face
		gl_Layer = face;
		for (int i = 0; i < 3; i++)
		{
			// where in world model is
			v_fragmentPos = gl_in[i].gl_Position;

			// pos according to light view.
			gl_Position = u_lightProjectionView[face] * v_fragmentPos;

			// vertex
			EmitVertex();
		}

		// end triangle
		EndPrimitive();
	}
}

FRAGMENT_SHADER
#version 460

in vec4 v_fragmentPos;

uniform vec3 u_lightPos;
uniform float u_farPlane;

void main()
{
	// from light pos to fragment
	float distance = length(v_fragmentPos.xyz - u_lightPos);

	// fragment depth can be only between 0 and 1.
	distance = distance / u_farPlane;
	gl_FragDepth = distance;
}