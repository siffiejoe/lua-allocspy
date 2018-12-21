/* Lua module for monitoring memory allocations */

#include <stddef.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>


/* Lua version compatibility */
#if LUA_VERSION_NUM == 501
#  define luaL_newlib( L, r ) \
  (lua_newtable( L ), luaL_register( L, NULL, r ))
#endif


typedef struct {
  lua_Alloc alloc;
  void*     ud;
  ptrdiff_t bytes;
  unsigned char enabled;
  unsigned char verbose;
} alloc_state;


static char const allocspy_id[ 1 ] = { 0 };

static alloc_state* get_alloc_state( lua_State* L ) {
  alloc_state* state = NULL;
  lua_pushlightuserdata( L, (void*)allocspy_id );
  lua_rawget( L, LUA_REGISTRYINDEX );
  state = (alloc_state*)lua_touserdata( L, -1 );
  lua_pop( L, 1 );
  return state;
}


static int allocspy_enable( lua_State* L ) {
  alloc_state* state = get_alloc_state( L );
  if( state != NULL ) {
    state->verbose = lua_toboolean( L, 1 );
    state->enabled = 1;
  }
  return 0;
}


static int allocspy_disable( lua_State* L ) {
  alloc_state* state = get_alloc_state( L );
  if( state != NULL ) {
    state->enabled = 0;
    lua_pushinteger( L, state->bytes );
    state->bytes = 0;
  } else
    lua_pushinteger( L, 0 );
  return 1;
}


static int allocspy_gc( lua_State* L ) {
  alloc_state* state = (alloc_state*)lua_touserdata( L, 1 );
  lua_setallocf( L, state->alloc, state->ud );
  return 0;
}


static void* allocspy_allocate( void* ud, void* ptr, size_t osize, size_t nsize ) {
  alloc_state* as = (alloc_state*)ud;
  if( as->enabled ) {
    if( ptr != NULL ) { /* realloc or free */
      as->bytes += (ptrdiff_t)nsize - (ptrdiff_t)osize;
      if( as->verbose ) {
        if( nsize > osize )
          fprintf( stderr, "(re-)allocating %zu bytes\n", nsize - osize );
        else
          fprintf( stderr, "freeing %zu bytes\n", osize - nsize );
      }
    } else { /* alloc */
      as->bytes += (ptrdiff_t)nsize;
      if( as->verbose ) {
        switch( osize ) {
#if LUA_VERSION_NUM > 501
          case LUA_TSTRING:
            fprintf( stderr, "allocating %zu bytes for a string\n", nsize );
            break;
          case LUA_TTABLE:
            fprintf( stderr, "allocating %zu bytes for a table\n", nsize );
            break;
          case LUA_TFUNCTION:
            fprintf( stderr, "allocating %zu bytes for a function\n", nsize );
            break;
          case LUA_TUSERDATA:
            fprintf( stderr, "allocating %zu bytes for a userdata\n", nsize );
            break;
          case LUA_TTHREAD:
            fprintf( stderr, "allocating %zu bytes for a thread\n", nsize );
            break;
#endif
          default:
            fprintf( stderr, "allocating %zu bytes\n", nsize );
            break;
        }
      }
    }
  }
  return as->alloc( as->ud, ptr, osize, nsize );
}


#ifndef EXPORT
#  define EXPORT extern
#endif

EXPORT int luaopen_allocspy( lua_State* L ) {
  luaL_Reg const funcs[] = {
    { "enable", allocspy_enable },
    { "disable", allocspy_disable },
    { NULL, 0 }
  };
  lua_pushlightuserdata( L, (void*)allocspy_id );
  lua_rawget( L, LUA_REGISTRYINDEX );
  if( lua_isnil( L, -1 ) ) {
    alloc_state* state = (alloc_state*)lua_newuserdata( L, sizeof( alloc_state ) );
    luaL_Reg const metamethods[] = {
      { "__gc", allocspy_gc },
      { NULL, 0 }
    };
    luaL_newlib( L, metamethods );
    lua_pushlightuserdata( L, (void*)allocspy_id );
    lua_pushvalue( L, -3 );
    lua_rawset( L, LUA_REGISTRYINDEX );
    state->enabled = 0;
    state->verbose = 0;
    state->bytes = 0;
    state->alloc = lua_getallocf( L, &(state->ud) );
    lua_setallocf( L, allocspy_allocate, state );
    lua_setmetatable( L, -2 );
  }
  luaL_newlib( L, funcs );
  return 1;
}


