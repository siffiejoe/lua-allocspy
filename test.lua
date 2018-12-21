#!/usr/bin/env lua

local spy = require( "allocspy" )

spy.enable( true )
local t = { 1, 2, 3 }
local bytes = spy.disable()
local t2 = { 1, 2, 3 }
print( "bytes allocated:", bytes )

