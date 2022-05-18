include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Anwar"
  architecture "x86_64"
  startproject "Anwar-Editor"

  configurations
  {
    "Debug",
    "Release",
    "Dist"
  }

  solution_items
  {
    ".editorconfig"
  }

  flags
  {
    "MultiProcessorCompile"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependecies"
  include "vendor/premake"
  include "Anwar/vendor/GLFW"
  include "Anwar/vendor/Glad"
  include "Anwar/vendor/imgui"
  include "Anwar/vendor/yaml-cpp"
group ""

include "Anwar"
include "Anwar Editor"
include "Sandbox"
