//PixelShader.hlsl
//
//
//

Texture2D colorMap1 : register(t0);
Texture2D colorMap2 : register(t1);
SamplerState colorSampler : register(s0);

//Codigo agregado para unir las texturas
cbuffer ConstantBuffer : register(b0)
{
    float4 g_BlendFactors;  // Use this to control the blending amount
};

struct PS_Input {
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 PS_Main(PS_Input frag) : SV_TARGET
{
    float4 color1 = colorMap1.Sample(colorSampler, frag.uv);
    float4 color2 = colorMap2.Sample(colorSampler, frag.uv);

    //Pintar el pixel con la textura
    //float4 colorFinal = colorMap.Sample(colorSampler, frag.uv);

    float4 colorFinal = color1 + color2;

    // Blend the colors using the blend factors
    //float4 blendedColor = lerp(color1, color2, g_BlendFactors.x);

    return colorFinal;
    //return blendedColor;
}