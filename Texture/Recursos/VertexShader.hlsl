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

struct VS_Output //salida de vertex shader 
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD; //en este caso no se tiene que cambiar la salida ya que solo es una referencia que parte de la textura y no se ve alterado
};


VS_Output VS_Main(VS_Input vertex) //el vertice no se representa solo por pocisiones sino seria mas adelante una estructura que contenga uv, normales, vertices, coordenadas etc 
{
    VS_Output vsOut = (VS_Output) 0;

    vsOut.pos = vertex.pos;
    vsOut.uv = vertex.uv;

    return vsOut;
}