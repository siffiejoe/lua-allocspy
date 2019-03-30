[![Build Status](https://travis-ci.org/siffiejoe/lua-allocspy.svg?branch=master)](https://travis-ci.org/siffiejoe/lua-allocspy)

#           Allocspy -- Monitoring Memory Allocation in Lua          #

##                           Introduction                           ##

If you are interested when Lua allocates how much memory for what,
this helper module is for you. It replaces the standard memory
allocator for Lua values and counts the allocated memory. It may also
log all (de-)allocations to `stderr`.


##                          Getting Started                         ##

This module can be `require`d as a normal Lua module. It provides two
functions:

*   `enable( verbose )`

    Start counting the number of bytes allocated by Lua. If the
    `verbose` flag is truish, every (de-)allocation is logged to
    `stderr`.

*   `disable()`

    Stop counting the number of bytes allocated by Lua. Returns the
    number of bytes allocated since this module was last `enable`d.


##                              Contact                             ##

Philipp Janda, siffiejoe(a)gmx.net

Comments and feedback are always welcome.


##                              License                             ##

**allocspy** is *copyrighted free software* distributed under the MIT
license (the same license as Lua 5.1). The full license text follows:

    allocspy (c) 2019 Philipp Janda

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

