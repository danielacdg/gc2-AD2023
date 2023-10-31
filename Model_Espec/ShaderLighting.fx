// ShaderLighting.fx : Implements the shader.
//
//
//


Texture2D colorMap : register(t0);
Texture2D colorMap2 : register(t1);
SamplerState colorSampler : register(s0);

// Mapas



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

cbuffer cbChangesOccasionally : register(b3)
{
    float3 cameraPos;
};

cbuffer cbLightPosition : register(b4)
{
    float3 lightPosRegister;
};

cbuffer cbDiffuseColorRegister : register(b5)
{
    float3 diffuseColor;
};


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
};


PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input)0;

    // Initial transformations
    float4 worldPos = mul(vertex.pos, worldMatrix);
    vsOut.pos = mul(worldPos, viewMatrix);
    vsOut.pos = mul(vsOut.pos, projMatrix);
    
    // UV
    vsOut.tex0 = vertex.tex0;
    
    // Normal
    vsOut.norm = mul(vertex.norm, (float3x3)worldMatrix);
    vsOut.norm = normalize(vsOut.norm);
    
    // Tangente
    
    
    // Binormal
    

    // Set light position
    float3 lightPos = float3(10.0f, 100.0f, -100.0f);

    // Calculate light vector
    vsOut.lightVec = normalize(lightPos - worldPos);
    
    // Calculate camera vector
    vsOut.cameraVec = normalize(cameraPos - worldPos);

    return vsOut;
}


float4 PS_Main(PS_Input frag) : SV_TARGET
{
    // Textura
    float4 textura = colorMap.Sample(colorSampler, frag.tex0);
    
    // Textura 2
    float4 textura2 = colorMap2.Sample(colorSampler, frag.tex0);
    
    // LightMap
    
    
    // AlphaMap
    
    
    // BumpMap
    
    
    // Calculate Bump Normals
    
    
    // SpecularMap
    
    
    // Light colors
    float3 ambientColor = float3(0.3f, 0.3f, 0.3f);
    float3 diffuseColor = float3(1.0f, 1.0f, 1.0f);
    float3 specularColor = float3(0.8f, 0.8f, 0.8f);

    // Get parameters
    float3 normal = normalize(frag.norm);
    float3 lightVec = normalize(frag.lightVec);
    float3 cameraVec = normalize(frag.cameraVec);
    

    // Calculate diffuse lighting
    float diffuseTerm = saturate(dot(normal, lightVec));
    
    // Calculate diffuse lighting using the BumpMap
    

    // Calculate specular lighting
    float3 R = normalize(lightVec + cameraVec);
    float specularTerm = pow(saturate(dot(normal, R)), 32);
    
    // Calculate specular lighting base on specular map
    

    // Calculate final color
    float3 finalColor = saturate(ambientColor + diffuseColor * diffuseTerm + specularColor * specularTerm);
    //float3 finalColor = saturate(ambientColor + diffuseColor * diffuseTerm);

    // Without texture
    //return float4(finalColor, 1.0f);

    // With texture and BumpMap
    return textura * float4(finalColor, 1.0f);
    
    // Simple Multitexture
    
    
    // Multitexture using AlphaMap
    
    
    // LightMap
    
    
    // With BumpMap and SpecularMap
    
    
}
