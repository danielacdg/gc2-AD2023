//PixelShader.hlsl
//
//
//

//Constantes Globales para la Textura
Texture2D colorMap : register(t0);//tipo de dato que representa textura o mapa de colores
Texture2D colorMap2 : register(t1);
SamplerState colorSampler : register(s0);

//Estructura de Entrada para el Shader
struct VS_Output //salida de vertex shader 
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};


float4 PS_Main(VS_Output vertex) : SV_TARGET
{
    //Pintar el pixel con la textura
    float4 pixColor = colorMap.Sample(colorSampler, vertex.uv); //pixel es como el fragment shader
    float4 pixColorB = colorMap2.Sample(colorSampler, vertex.uv)* float4(3.0f, -2.0f, -3.0f, 1.0f);
    float4 pixColorResult = pixColor + pixColorB;

    return pixColorResult;
}
