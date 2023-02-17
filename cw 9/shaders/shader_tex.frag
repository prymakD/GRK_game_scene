#version 430 core

float AMBIENT = 0.03;
float PI = 3.14;

uniform sampler2D depthMapSun;

uniform vec3 cameraPos;

uniform vec3 color;

uniform vec3 sunDir;
uniform vec3 sunColor;

uniform vec3 lightPos;
uniform vec3 lightColor;


uniform vec3 laserLightPos0;
uniform vec3 laserLightPos1;
uniform vec3 laserLightPos2;
uniform vec3 laserLightPos3;
uniform vec3 laserLightPos4;
uniform vec3 laserLightPos5;
uniform vec3 laserLightPos6;
uniform vec3 laserLightPos7;
uniform vec3 laserLightPos8;
uniform vec3 laserLightPos9;
uniform vec3 laserLightPos10;
uniform vec3 laserLightPos11;
uniform vec3 laserLightPos12;
uniform vec3 laserLightPos13;
uniform vec3 laserLightPos14;
uniform vec3 laserLightPos15;
uniform vec3 laserLightPos16;
uniform vec3 laserLightPos17;
uniform vec3 laserLightPos18;
uniform vec3 laserLightPos19;


uniform vec3 laserLightColor;


uniform sampler2D colorTexture;
in vec2 vecTex;

uniform vec3 spotlightPos;
uniform vec3 spotlightColor;
uniform vec3 spotlightConeDir;
uniform vec3 spotlightPhi;

uniform float metallic;
uniform float roughness;

uniform float exposition;

in vec3 vecNormal;
in vec3 worldPos;

out vec4 outColor;


in vec3 viewDirTS;
in vec3 lightDirTS;
in vec3 spotlightDirTS;
in vec3 sunDirTS;

in vec4 sunSpacePos;

in vec3 test;
uniform float time;

float DistributionGGX(vec3 normal, vec3 H, float roughness){
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(normal, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}
float GeometrySchlickGGX(float NdotV, float roughness){
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 normal, vec3 V, vec3 lightDir, float roughness){
    float NdotV = max(dot(normal, V), 0.0);
    float NdotL = max(dot(normal, lightDir), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}
vec3 fresnelSchlick(float cosTheta, vec3 F0){
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
} 

vec3 PBRLight(vec3 lightDir, vec3 radiance, vec3 normal, vec3 V){
	float diffuse=max(0,dot(normal,lightDir));

	//vec3 V = normalize(cameraPos-worldPos);
	vec3 F0 = vec3(0.04); 
    F0 = mix(F0, color, metallic);

    vec3 H = normalize(V + lightDir);    
        
    // cook-torrance brdf
    float NDF = DistributionGGX(normal, H, roughness);        
    float G   = GeometrySmith(normal, V, lightDir, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;	  
        
    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(normal, V), 0.0) * max(dot(normal, lightDir), 0.0) + 0.0001;
    vec3 specular     = numerator / denominator;  
            
    // add to outgoing radiance Lo
    float NdotL = max(dot(normal, lightDir), 0.0);   
	return (kD * color / PI + specular) * radiance * NdotL;
}


float calculateShadow() {

	vec4 sunSpacePosNormalized =  (0.5 * sunSpacePos / (sunSpacePos.w)) + 0.5;

    float closestDepth = texture2D(depthMapSun, sunSpacePosNormalized.xy).x;//r?

    float diff = (0.001+closestDepth) - sunSpacePosNormalized.z;//sunSpacePosNormalized.z;

    return (0.5*(diff)/abs(diff))+0.5;
}

void main()
{	
	vec3 lightDir = normalize(lightPos-worldPos);
	vec3 normal = normalize(vecNormal);
    vec3 textureColor = texture2D(colorTexture, vecTex).xyz;
	float diffuse=max(0,dot(normal,lightDir));

    vec3 viewDir = normalize(cameraPos-worldPos);

	vec3 ambient = AMBIENT*color;
	vec3 attenuatedlightColor = lightColor/pow(length(lightPos-worldPos),2);
	vec3 ilumination;
	ilumination = ambient+PBRLight(lightDir,attenuatedlightColor,normal,viewDir);


    //lasers light direction
    vec3 laserLightDir0 = normalize(laserLightPos0-worldPos);
    vec3 laserLightDir1 = normalize(laserLightPos1-worldPos);
    vec3 laserLightDir2 = normalize(laserLightPos2-worldPos);
    vec3 laserLightDir3 = normalize(laserLightPos3-worldPos);
    vec3 laserLightDir4 = normalize(laserLightPos4-worldPos);
    vec3 laserLightDir5 = normalize(laserLightPos5-worldPos);
    vec3 laserLightDir6 = normalize(laserLightPos6-worldPos);
    vec3 laserLightDir7 = normalize(laserLightPos7-worldPos);
    vec3 laserLightDir8 = normalize(laserLightPos8-worldPos);
    vec3 laserLightDir9 = normalize(laserLightPos9-worldPos);
    vec3 laserLightDir10 = normalize(laserLightPos10-worldPos);
    vec3 laserLightDir11 = normalize(laserLightPos11-worldPos);
    vec3 laserLightDir12 = normalize(laserLightPos12-worldPos);
    vec3 laserLightDir13 = normalize(laserLightPos13-worldPos);
    vec3 laserLightDir14 = normalize(laserLightPos14-worldPos);
    vec3 laserLightDir15 = normalize(laserLightPos15-worldPos);
    vec3 laserLightDir16 = normalize(laserLightPos16-worldPos);
    vec3 laserLightDir17 = normalize(laserLightPos17-worldPos);
    vec3 laserLightDir18 = normalize(laserLightPos18-worldPos);
    vec3 laserLightDir19 = normalize(laserLightPos19-worldPos);


    //LASERS LIGHTING
    float laserIntensity = pow(sin(time * 10.0), 2.0);
     
    if((laserLightPos0.y > 0 && laserLightPos0.y < 2.2) && (laserLightPos0.z > -2.2 && laserLightPos0.z < 2.1) && (laserLightPos0.x > -1.72 && laserLightPos0.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos0-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir0,attenuatedlightColor,normal,viewDir);
    }

    if((laserLightPos1.y > 0 && laserLightPos1.y < 2.2) && (laserLightPos1.z > -2.2 && laserLightPos1.z < 2.1) && (laserLightPos1.x > -1.72 && laserLightPos1.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos1-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir1,attenuatedlightColor,normal,viewDir);
    }

    if((laserLightPos2.y > 0 && laserLightPos2.y < 2.2) && (laserLightPos2.z > -2.2 && laserLightPos2.z < 2.1) && (laserLightPos2.x > -1.72 && laserLightPos2.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos2-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir2,attenuatedlightColor,normal,viewDir);
    }

    if((laserLightPos3.y > 0 && laserLightPos3.y < 2.2) && (laserLightPos3.z > -2.2 && laserLightPos3.z < 2.1) && (laserLightPos3.x > -1.72 && laserLightPos3.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos3-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir3,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos4.y > 0 && laserLightPos4.y < 2.2) && (laserLightPos4.z > -2.2 && laserLightPos4.z < 2.1) && (laserLightPos4.x > -1.72 && laserLightPos4.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos4-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir4,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos5.y > 0 && laserLightPos5.y < 2.2) && (laserLightPos5.z > -2.2 && laserLightPos5.z < 2.1) && (laserLightPos5.x > -1.72 && laserLightPos5.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos5-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir5,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos6.y > 0 && laserLightPos6.y < 2.2) && (laserLightPos6.z > -2.2 && laserLightPos6.z < 2.1) && (laserLightPos6.x > -1.72 && laserLightPos6.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos6-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir6,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos7.y > 0 && laserLightPos7.y < 2.2) && (laserLightPos7.z > -2.2 && laserLightPos7.z < 2.1) && (laserLightPos7.x > -1.72 && laserLightPos7.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos7-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir7,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos8.y > 0 && laserLightPos8.y < 2.2) && (laserLightPos8.z > -2.2 && laserLightPos8.z < 2.1) && (laserLightPos8.x > -1.72 && laserLightPos8.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos8-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir8,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos9.y > 0 && laserLightPos9.y < 2.2) && (laserLightPos9.z > -2.2 && laserLightPos9.z < 2.1) && (laserLightPos9.x > -1.72 && laserLightPos9.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos9-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir9,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos10.y > 0 && laserLightPos10.y < 2.2) && (laserLightPos10.z > -2.2 && laserLightPos10.z < 2.1) && (laserLightPos10.x > -1.72 && laserLightPos10.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos10-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir10,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos11.y > 0 && laserLightPos11.y < 2.2) && (laserLightPos11.z > -2.2 && laserLightPos11.z < 2.1) && (laserLightPos11.x > -1.72 && laserLightPos11.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos11-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir11,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos12.y > 0 && laserLightPos12.y < 2.2) && (laserLightPos12.z > -2.2 && laserLightPos12.z < 2.1) && (laserLightPos12.x > -1.72 && laserLightPos12.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos12-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir12,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos13.y > 0 && laserLightPos13.y < 2.2) && (laserLightPos13.z > -2.2 && laserLightPos13.z < 2.1) && (laserLightPos13.x > -1.72 && laserLightPos13.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos13-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir13,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos14.y > 0 && laserLightPos14.y < 2.2) && (laserLightPos14.z > -2.2 && laserLightPos14.z < 2.1) && (laserLightPos14.x > -1.72 && laserLightPos14.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos14-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir14,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos15.y > 0 && laserLightPos15.y < 2.2) && (laserLightPos15.z > -2.2 && laserLightPos15.z < 2.1) && (laserLightPos15.x > -1.72 && laserLightPos15.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos15-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir15,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos16.y > 0 && laserLightPos16.y < 2.2) && (laserLightPos16.z > -2.2 && laserLightPos16.z < 2.1) && (laserLightPos16.x > -1.72 && laserLightPos16.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos16-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir16,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos17.y > 0 && laserLightPos17.y < 2.2) && (laserLightPos17.z > -2.2 && laserLightPos17.z < 2.1) && (laserLightPos17.x > -1.72 && laserLightPos17.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos17-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir17,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos18.y > 0 && laserLightPos18.y < 2.2) && (laserLightPos18.z > -2.2 && laserLightPos18.z < 2.1) && (laserLightPos18.x > -1.72 && laserLightPos18.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos18-worldPos),1.5); 
	    ilumination=ilumination+PBRLight(laserLightDir18,attenuatedlightColor,normal,viewDir); 
    }

    if((laserLightPos19.y > 0 && laserLightPos19.y < 2.2) && (laserLightPos19.z > -2.2 && laserLightPos19.z < 2.1) && (laserLightPos19.x > -1.72 && laserLightPos19.x < 1.78)){
        attenuatedlightColor = laserIntensity * laserLightColor/pow(length(laserLightPos19-worldPos),1.5);
	    ilumination=ilumination+PBRLight(laserLightDir19,attenuatedlightColor,normal,viewDir); 
    }


    //flashlight
	//vec3 spotlightDir= normalize(spotlightDirTS);
	vec3 spotlightDir= normalize(spotlightPos-worldPos);
	

    float angle_atenuation = clamp((dot(-normalize(spotlightPos-worldPos),spotlightConeDir)-0.5)*3,0,1);
	attenuatedlightColor = angle_atenuation*spotlightColor/pow(length(spotlightPos-worldPos),2);
	ilumination=ilumination+PBRLight(spotlightDir,attenuatedlightColor,normal,viewDir);

	//sun
	ilumination=ilumination+PBRLight(sunDir, sunColor *  calculateShadow(), normal, viewDir);

    //outColor = vec4(textureColor*min(1,AMBIENT+diffuse), 1.0);
    //outColor = vec4(vec3(1.0) - exp(-ilumination*exposition),1);

    outColor = vec4(textureColor*min(1,AMBIENT+diffuse) - 1*exp(-ilumination*exposition),1);
}

