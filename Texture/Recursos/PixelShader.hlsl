//PixelShader.hlsl
//
//
//

//Constantes Globales para la Textura
Texture2D colorMap : register(t0);
Texture2D colorMap1 : register(t1);     //2da textura
SamplerState colorSampler : register(s0);

//Estructura de Entrada para el Shader
struct PS_Output
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 PS_Main(PS_Output frag) : SV_TARGET
{
    //Pintar el pixel con la textura
    
    float4 color = colorMap.Sample(colorSampler, frag.uv);
    color = color * colorMap1.Sample(colorSampler, frag.uv)
     + float4(0.3f, 0.0f, 0.0f, 0.7f);
    return color; 
    
    //return float4 (0.0f, 0.0f, 0.5f, 1.4f);
}
