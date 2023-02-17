#version 430 core


out vec4 out_color;
flat in vec4 color;
in vec4 pos_local;
in vec4 pos_global;

uniform float time;
uniform vec3 laserColor;

void main()
{
    float laserIntensity = pow(sin(time * 10.0), 2.0);

    vec3 laserDistortion = mix(vec4(laserColor, 1), vec4(0.0f, 0.3f, 0.3f, 1.0f), sin(time)).xyz;
    out_color = vec4(laserColor * laserIntensity/* + laserDistortion*/, 1.0);
}