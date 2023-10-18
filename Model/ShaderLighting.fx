// ShaderLighting.fx : Implements the shader.
//
//
//


Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);


cbuffer cbChangesEveryFrame : register(b0)
{
    matrix worldMatrix;
};

cbuffer cbNeverChanges : register(b1)
{
    matrix viewMatrix;
};

cbuffer cbChangeOnResize : register(b2)
{
    matrix projMatrix;
};

cbuffer cbCameraPos : register(b3)
{
    float3 cameraPos;
}

cbuffer cdLightPos2 : register(b4)
{
    float3 lightPosCB2; //posicion de la luz
}
struct VS_Input
{
    float4 pos  : POSITION;
    float2 tex0 : TEXCOORD0;
    float3 norm : NORMAL;
};


struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD0;
    float3 norm : NORMAL;
    float3 lightVec : TEXCOORD1;
    float3 cameraVec : TEXCOORD2;
    float3 lightVec2 : TEXCOORD3;
};


PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input)0;

    // Initial transformations
    float4 worldPos = mul(vertex.pos, worldMatrix);
    vsOut.pos = mul(worldPos, viewMatrix);
    vsOut.pos = mul(vsOut.pos, projMatrix);
    
    vsOut.tex0 = vertex.tex0;
    
    vsOut.norm = mul(vertex.norm, (float3x3)worldMatrix);
    vsOut.norm = normalize(vsOut.norm);

    // Set light position
    float3 lightPos = float3(100.0f, 10.0f, -14.0f); //10.0f, 100.0f, -100.0f
    //float3 lightPos2 = float3(10.0f, -100.0f, 100.0f);
    
    float3 lightPos2 = float3(lightPosCB2[0], lightPosCB2[1], lightPosCB2[2]);
    
    //float3 lightPos2 = cameraPos;

    // Calculate light vector
    vsOut.lightVec = normalize(lightPos - worldPos);
    
    
    vsOut.lightVec2 = normalize(lightPos2 - worldPos);
    // Calculate camera vector
    vsOut.cameraVec = normalize(cameraPos - worldPos);

    return vsOut;
}


float4 PS_Main(PS_Input frag) : SV_TARGET
{
    // Light colors
    
    // Ambient color
    float3 ambientColor = float3(0.2f, 0.2f, 0.2f);
   
    
    //Specular Color
    float specularColor = float3(0.8f,0.8f,0.8f); //color blanco comun
    float3 specularColor2 = float3(0.4f, 0.4f, 0.4f); // Color especular adicional
    
    // Diffuse color
    float3 diffuseColor = float3(0.8f, 0.4f, 0.6f);
    float3 diffuseColor2 = float3(0.6f, 0.4f, 0.8f);
    
    // Get parameters
    float3 normal = normalize(frag.norm);
    float3 lightVec = normalize(frag.lightVec);
    float3 lightVec2 = normalize(frag.lightVec2);
    float3 cameraVec = normalize(frag.cameraVec);

    // Calculate diffuse lighting
    float diffuseIntensity = saturate(dot(normal, lightVec));
    float diffuseIntensity2 = saturate(dot(normal, lightVec2));
    //Calculate specular lighting
    float3 R = normalize(lightVec + cameraVec);
    float3 R2 = normalize(lightVec2 + cameraVec);
    float3 specularInstansity = saturate(dot(normal,R));
    float3 specularInstansity2 = saturate(dot(normal, R2));
    specularInstansity = pow(specularInstansity, 100);
    specularInstansity2 = pow(specularInstansity2, 100);
    // Calculate final color
    //float3 finalColor = ambientColor + (diffuseColor * diffuseIntensity) + (diffuseColor2 * diffuseIntensity2) + (specularColor + specularInstansity) ;
    float3 finalColor = ambientColor + ((((diffuseColor * diffuseIntensity) + (specularColor * specularInstansity)) +
                                       ((diffuseColor2 * diffuseIntensity2) + (specularColor2 * specularInstansity2))));

    
    
    float4 textura = colorMap.Sample(colorSampler, frag.tex0);

    // Without texture
    return float4(finalColor, 1.0f);

    // With texture
    //return colorMap.Sample(colorSampler, frag.tex0) * float4(color, 1.0f);
}
