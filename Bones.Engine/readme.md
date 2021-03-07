# BONES

## GLOSSARY

count - count of elements, not to be confused with length which is in bytes
length - length of array in bytes
size - usually size of component. For vec3 it would be 3


Bones is Luka Erkapic's engine with the main purpose of being able to run on web via webassembly and emscripten toolchain.

Common conventions of bones engine.

* every struct must end with Data 
* resources are handled by managers which expose static methods.

// TODO: 
- refactor SceneObject namespace
- BaseToolUIComponent abstract Destroy