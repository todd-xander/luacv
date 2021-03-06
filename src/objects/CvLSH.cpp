#include "CvLSH.h"

void pushCvLSH(lua_State *L,CvLSH *data)
{
  luacv_obj<void> *obj=(luacv_obj<void>*)lua_newuserdata(L,sizeof(luacv_obj<void>));
  obj->data=data;
  luaL_getmetatable(L,CVLSH_NAME);
  lua_setmetatable(L,-2);
}


static int CvLSH_tostring(lua_State*L)
{
  lua_pushfstring(L,CVLSH_NAME" object %p\n",checkCvLSH(L,1));
  return 1;
}

static int CvLSH_gc(lua_State*L)
{
  luacv_obj<CvLSH>*obj=(luacv_obj<CvLSH>*)luaL_checkudata(L,1,CVLSH_NAME);
  if (obj->dealloc_data)
    cvReleaseLSH(&obj->data);

  return 0;
}

const luaL_Reg CvLSH_m[]=
{
  {"__tostring",CvLSH_tostring},
  {"__gc",CvLSH_gc},
  {NULL,NULL}
};


