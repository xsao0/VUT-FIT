/*!
 * @file
 * @brief This file contains implementation of gpu
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <student/gpu.hpp>
#include <stdio.h>
#include <string.h>

uint32_t computeVertexID(GPUContext& ctx,uint32_t shaderInvocation){
  if(!ctx.vao.indexBuffer)return shaderInvocation;

  if(ctx.vao.indexType == IndexType::UINT32){
    uint32_t*ind = (uint32_t*)ctx.vao.indexBuffer;
    return ind[shaderInvocation];
  }
  if(ctx.vao.indexType == IndexType::UINT16){
    uint16_t*ind = (uint16_t*)ctx.vao.indexBuffer;
    return ind[shaderInvocation];
  }
  if(ctx.vao.indexType == IndexType::UINT8){
    uint8_t*ind = (uint8_t*)ctx.vao.indexBuffer;
    return ind[shaderInvocation];
  }
}



//! [drawTrianglesImpl]
void drawTrianglesImpl(GPUContext &ctx,uint32_t nofVertices){
  (void)ctx;
  (void)nofVertices;
  
  for(uint32_t v = 0; v < nofVertices; v++){
    InVertex inVertex;
    inVertex.gl_VertexID = computeVertexID(ctx, v);
    
    for(uint32_t i = 0; i < maxAttributes; i++){
      Attribute newAttribute;
      auto attrib = ctx.vao.vertexAttrib[i];
      auto data = (char*)attrib.bufferData + attrib.offset + attrib.stride * inVertex.gl_VertexID;
      if(attrib.type == AttributeType::FLOAT)
        memcpy( &newAttribute.v1, data, sizeof(float));
      if(attrib.type == AttributeType::VEC2)
        memcpy( &newAttribute.v2,  data, 2*sizeof(float));
      if(attrib.type == AttributeType::VEC3)
        memcpy( &newAttribute.v3,  data, 3*sizeof(float));
      if(attrib.type == AttributeType::VEC4)
        memcpy( &newAttribute.v4,  data, 4*sizeof(float));
      if(attrib.type == AttributeType::EMPTY){}
      inVertex.attributes[i] = newAttribute;
    }

    OutVertex outVertex;
    ctx.prg.vertexShader(outVertex, inVertex, ctx.prg.uniforms);
  }
}
//! [drawTrianglesImpl]

/**
 * @brief This function reads color from texturv
 * @param uv uv coordinates
 *
 * @return color 4 floats
 */
glm::vec4 read_texture(Texture const&texture,glm::vec2 uv){
  if(!texture.data)return glm::vec4(0.f);
  auto uv1 = glm::fract(uv);
  auto uv2 = uv1*glm::vec2(texture.width-1,texture.height-1)+0.5f;
  auto pix = glm::uvec2(uv2);
  //auto t   = glm::fract(uv2);
  glm::vec4 color = glm::vec4(0.f,0.f,0.f,1.f);
  for(uint32_t c=0;c<texture.channels;++c)
    color[c] = texture.data[(pix.y*texture.width+pix.x)*texture.channels+c]/255.f;
  return color;
}

/**
 * @brief This function clears framebuffer.
 *
 * @param ctx GPUContext
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel
 */
void clear(GPUContext&ctx,float r,float g,float b,float a){
  auto&frame = ctx.frame;
  auto const nofPixels = frame.width * frame.height;
  for(size_t i=0;i<nofPixels;++i){
    frame.depth[i] = 10e10f;
    frame.color[i*4+0] = static_cast<uint8_t>(glm::min(r*255.f,255.f));
    frame.color[i*4+1] = static_cast<uint8_t>(glm::min(g*255.f,255.f));
    frame.color[i*4+2] = static_cast<uint8_t>(glm::min(b*255.f,255.f));
    frame.color[i*4+3] = static_cast<uint8_t>(glm::min(a*255.f,255.f));
  }
}

