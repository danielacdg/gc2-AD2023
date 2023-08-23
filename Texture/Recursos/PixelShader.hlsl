//PixelShader.hlsl
//
//
//

//Constantes Globales para la Textura

//Estructura de Entrada para el Shader

float4 PS_Main(float4 pos : SV_POSITION) : SV_TARGET
{
    //Pintar el pixel con la textura
    
    return float4(0.0f, 0.0f, 0.5f, 1.0f);
}
