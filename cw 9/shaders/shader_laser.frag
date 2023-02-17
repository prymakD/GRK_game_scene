#version 430 core


out vec4 out_color;
flat in vec4 color;
in vec4 pos_local;
in vec4 pos_global;

uniform float time;
uniform vec3 laserColor;


float hash(float n)
{
    return fract(sin(n) * 1399763.5453123);
}

float noise(vec3 x)
{
    vec3 p = floor(x);
    vec3 f = fract(x);
    f = f * f * (3.0 - 2.0 * f);
    float n = p.x + p.y * 57.0 + 113.0 * p.z;

    vec4 test1 = mix(vec4(hash(n + 170.0)), vec4(hash(n + 171.0)), sin(time));
    vec4 test2 = mix(vec4(hash(n + 113.0)), vec4(hash(n + 114.0)), sin(time));
    vec4 test3 = mix(test2,  test1, sin(time));
    vec4 test4 = mix(vec4(hash(n + 57.0)), vec4(hash(n + 58.0)), sin(time));
    vec4 test5 = mix(vec4(hash(n + 0.0)), vec4(hash(n + 1.0)), sin(time));
    vec4 test6 = mix(test5, test4, sin(time));
    vec4 test7 = mix(test6, test3, sin(time));



    return test7.z;

//    return mix(mix(mix(hash(n + 0.0), hash(n + 1.0)), mix(hash(n + 57.0), hash(n + 58.0))), mix(mix(hash(n + 113.0), hash(n + 114.0)), mix(hash(n + 170.0), hash(n + 171.0))), f);
}

void main()
{
	//out_color = vec4(0.8,0.2,0.9,1.0);
//    vec4 mixColor = mix(color, vec4(0.0f, 0.3f, 0.3f, 1.0f), sin(time));
//    out_color = mixColor / sin(time);

//    vec4 mixColor = mix(time * abs(pos_local), vec4(0.0f, 0.3f, 0.3f, 1.0f), sin(time));
//    out_color = mixColor / sin(time);


    vec3 newPosLocal = vec3(pos_local.x, pos_local.y, pos_local.z);
    float laserIntensity = pow(sin(time * 10.0), 2.0);//sin(time * 5.0) * 0.5 + 0.5;
//    vec3 laserDistortion = vec3(noise(newPosLocal * 8.0 + vec3(0, time * 4.0, time * 2.0)) * 0.1);


    vec3 laserDistortion = mix(vec4(laserColor, 1), vec4(0.0f, 0.3f, 0.3f, 1.0f), sin(time)).xyz;
    out_color = vec4(laserColor * laserIntensity/* + laserDistortion*/, 1.0);

//    vec4 mixColor = mix(pos_global, vec4(0.0f, 0.3f, 0.3f, 1.0f), sin(time));
//    out_color = mixColor / sin(time);
    //out_color = color / time;
}