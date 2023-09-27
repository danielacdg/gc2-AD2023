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
    vsOut.tex0 = vertex.tex0;
    

    // Set light position
    

    // Calculate light vector
    
    
    // Calculate camera vector
    

    return vsOut;
}


float4 PS_Main(PS_Input frag) : SV_TARGET
{
    // Light colors
    
    
    float3 color = float3(1.0f, 1.0f, 1.0f);

    // Get parameters
    

    // Calculate diffuse lighting
    

    // Calculate final color
    
    
    float4 textura = colorMap.Sample(colorSampler, frag.tex0);

    // Without texture
    //return float4(color, 1.0f);

    // With texture
    return colorMap.Sample(colorSampler, frag.tex0) * float4(color, 1.0f);
}
