// ShaderLighting.fx : Implements the shader.
//
//
//


Texture2D colorMap : register(t0);
Texture2D colorMap2 : register(t1);
SamplerState colorSampler : register(s0);

// Mapas
Texture2D alphaMapText : register (t2);
Texture2D lightMapText : register (t3);
Texture2D BumpMapText : register (t4);
Texture2D specularMapText : register (t5);

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
    float3 tangent : TANGENT; 
    float3 binormal : BINORMAL; 
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
    float3 tangent; 

    float3 c1 = cross(vsOut.norm, float3(0.0, 0.0, 1.0));
    float3 c2 = cross(vsOut.norm, float3(0.0, 1.0, 0.0));;
    
    if (length(c1) > length(c2))
    {
        tangent = c1;
    }
    else {

        tangent = c2; 
    }

    vsOut.tangent = normalize(tangent); 

    // Binormal
    float3 binormal;
    binormal = cross(vsOut.norm, vsOut.tangent);
    vsOut.binormal = normalize(tangent);


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
    
    // AlphaMap
    float4 alphaMap = alphaMapText.Sample(colorSampler, frag.tex0);

    // LightMap
    float4 lightMap = lightMapText.Sample(colorSampler, frag.tex0);

    // BumpMap
    float4 bumpMap = BumpMapText.Sample(colorSampler, frag.tex0);
    bumpMap = (bumpMap * 2.0f) - 1.0f;
    
    // Calculate Bump Normals
    float3 bumpNormal = (bumpMap.x * frag.tangent) + (bumpMap.y * frag.binormal) + (bumpMap.z * frag.norm);

    bumpNormal = normalize(bumpNormal);
    // SpecularMap
    float4 specularMap = specularMapText.Sample(colorSampler, frag.tex0);
    
    // Light colors
    float3 ambientColor = float3(0.3f, 0.3f, 0.3f);
    float3 diffuseColor = float3(1.0f, 1.0f, 1.0f);
    float3 specularColor = float3(0.8f, 0.8f, 0.8f);

    // Get parameters
    float3 normal = normalize(frag.norm);
    float3 lightVec = normalize(frag.lightVec);
    float3 cameraVec = normalize(frag.cameraVec);
    

    // Calculate diffuse lighting
    //float diffuseTerm = saturate(dot(normal, lightVec));
    
    // Calculate diffuse lighting using the BumpMap
    float diffuseTerm = saturate(dot(bumpNormal, lightVec));

    // Calculate specular lighting
    float3 R = normalize(lightVec + cameraVec);
    float specularTerm = pow(saturate(dot(normal, R)), 32);
    
    // Calculate specular lighting base on specular map
    if (diffuseTerm > 0.0f) {

        R = normalize(lightVec + (2 * diffuseTerm * bumpNormal));
        specularTerm = pow(saturate(dot(cameraVec, R)), 32);

        specularMap = specularTerm * specularMap; 
    }

    // Calculate final color
   float3 finalColor = saturate(ambientColor + diffuseColor * diffuseTerm + specularColor * specularTerm);
    //float3 finalColor = saturate(ambientColor + diffuseColor * diffuseTerm);

    // Without texture
    //return float4(finalColor, 1.0f);

    
 

    // Simple Multitexture
    
    
    // Multitexture using AlphaMap
    
    
    // LightMap
   // return textura * lightMap * float4(finalColor, 1.0f);
    

       //Alpha map
  // return(textura * alphaMap) + (textura2 * (1.0 - alphaMap)) * float4(finalColor, 1.0f);
   
    // With BumpMap and SpecularMap
    

    // With texture and BumpMap
    return textura * float4(finalColor, 1.0f) + specularMap;
}
