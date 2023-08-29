//VertexShader.hlsl
//
//
//

//Estructura de Entrada y de Salida para el Shader
struct VS_Input
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct PS_Output
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

PS_Output VS_Main(VS_Input vertex)
{
    PS_Output psOut = (PS_Output) 0;
    
    psOut.pos = vertex.pos;
    psOut.uv = vertex.uv;
    return psOut;
}