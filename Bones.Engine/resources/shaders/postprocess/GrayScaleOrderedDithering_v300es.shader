VERTEX_SHADER
#version 300 es

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoords;

out vec2 v_texCoords;

void main()
{
    gl_Position = vec4(a_position, 0., 1.);
    v_texCoords = a_texCoords;
}

FRAGMENT_SHADER
#version 300 es

precision mediump float;

in vec2 v_texCoords;

uniform sampler2D u_screenTexture;

out vec4 o_color;

const float threshold[16] = float[16](
    1. / 16., 9. / 16., 3. / 16., 11. / 16.,
    13. / 16., 5. / 16., 15. / 16., 7. / 16.,
    4. / 16., 12. / 16., 2. / 16., 10. / 16.,
    16. / 16., 8. / 16., 14. / 16., 6. / 16.);

float FindClosest(int x, int y, float v)
{
    return step(threshold[4 * y + x], v);
}

void main()
{
    vec4 col = texture(u_screenTexture, v_texCoords);

    // https://en.wikipedia.org/wiki/Ordered_dithering
    int x = int(v_texCoords.x) % 4;
    int y = int(v_texCoords.y) % 4;

    // https://en.wikipedia.org/wiki/Luma_(video)
    float lum = dot(vec3(0.2126, 0.7152, 0.0722), col.rgb);
    lum = FindClosest(x, y, lum);

    // Output to screen
    o_color = vec4(vec3(lum), 1.0);
}