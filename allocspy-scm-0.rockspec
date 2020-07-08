package="allocspy"
version="scm-0"

source = {
  url = "git://github.com/siffiejoe/lua-allocspy.git",
}

description = {
  summary = "Logging of memory (de-)allocations.",
  detailed = [[
  ]],
  homepage = "https://github.com/siffiejoe/lua-allocspy/",
  license = "MIT",
}

dependencies = {
  "lua >= 5.1, < 5.5"
}

build = {
  type = "builtin",
  modules = {
    allocspy = "allocspy.c",
  }
}

