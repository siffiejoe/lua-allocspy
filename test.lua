#!/usr/bin/env lua

local spy = require( "allocspy" )

spy.enable()
local t = { 1, 2, 3 }
spy.disable()
local t2 = { 1, 2, 3 }

