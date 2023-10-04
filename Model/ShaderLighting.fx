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
// ---------- Constantes para la Luz Especular


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
    // ---------- Luz Especular
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
    //float3 lightPos = float3(10.0f, 100.0f, -100.0f);
    float3 lightPos = cameraPos;

    // Calculate light vector
    vsOut.lightVec = normalize(lightPos - worldPos);
    
    // Calculate camera vector
    
    // ---------- Luz Especular
    

    return vsOut;
}


float4 PS_Main(PS_Input frag) : SV_TARGET
{
    // Light colors
    float3 ambientColor = float3(0.2f, 0.2f, 0.2f);
    float3 diffuseColor = float3(0.8f, 0.8f, 0.8f);
    // ---------- Color de la Luz Especular

    // Get parameters
    float3 normal = normalize(frag.norm);
    float3 lightVec = normalize(frag.lightVec);
    // ---------- Luz Especular

    // Calculate diffuse lighting
    float diffuseTerm = saturate(dot(normal, lightVec));

    // ---------- Calcular la intensidad de la Luz Especular
    
    // Calculate final color
    // ---------- Agregar al cálculo la Luz Especular
    float3 finalColor = ambientColor + (diffuseColor * diffuseTerm);
    
    float4 textura = colorMap.Sample(colorSampler, frag.tex0);

    // Without texture
    return float4(finalColor, 1.0f);

    // With texture
    //return colorMap.Sample(colorSampler, frag.tex0) * float4(color, 1.0f);
}
