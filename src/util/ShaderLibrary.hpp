/*
 * adapted from Kolton Yager's code
 */
#pragma once
#ifndef SHADERLIBRARY_H_
#define SHADERLIBRARY_H_

#include <unordered_map>
#include <vector>
#include <string>
#include "../Program.h"

using namespace std;

class ShaderLibrary{

public:
	static ShaderLibrary& getInstance(){
		static ShaderLibrary instance;
		return(instance);
	}

	// Add a shader to the library by name and pointer
	void add(const string &name, Program* program);
	void add(const char* name, Program* program){add(string(name), program);}

	bool loadFromShaderCollection(string path, bool silent = false);

	bool buildAndAdd(string name, const string &vpath, const string &fpath);
	bool buildAndAdd(const char* const name, const string &vpath, const string &fpath) {return(buildAndAdd(string(name), vpath, fpath));}
	bool buildAndAdd(string name, const string& cpath);
	bool buildAndAdd(const char* const name, const string& cpath) { return(buildAndAdd(string(name), cpath)); }


	void printLibary() const;

	// Bind the program stored under the given name and mark it as active
	void makeActive(const string &name);
	void makeActive(const char* name){makeActive(string(name));}

	// Automatically swaps to and binds on the given program pointer. This enables calls to be made to the
	// library during rendering that skip the overhead of the hash-table whilst avoiding redundant bind calls.
	void fastActivate(Program* prog);

	Program& getActive();

	// Should only be used in combination with fastActivate()! Do not use to bind manually!
	Program* getActivePtr();

	Program* operator[](const string& name) {return(getPtr(name));}
	Program* operator[](const char* name) {return(getPtr(string(name)));}

	// Same as getActivePtr but for any program in the library. If the given name is not found returns NULL
	Program* getPtr(const string &name);
	Program* getPtr(const char* name){return(getPtr(string(name)));}

	void dumpBinary(const string& name);
	void dumpBinary(const char* name){dumpBinary(string(name));}

	ShaderLibrary(ShaderLibrary const&) = delete;
	void operator=(ShaderLibrary const&) = delete;
private:
	ShaderLibrary();
	
	// Hash-table associative array linking GLSL programs to a simple name such as "blinn-phong" 
	// Most pointers should point to an element of 'localPrograms', but don't need to. 
	unordered_map<string, Program*> programs;
	
	// Collection of Program objects scoped within the class for the sake of unambiguous memory management.
	vector<Program> localPrograms; 

	// Always initialized "error shader" that can be fallen back on if another shader is missing or fails
	Program fallback;

	// Pointer to active shader which is currently bound in OpenGL
	Program* active;

	// Hardcoded fallback shadercode
    constexpr const static char* errorvs = "vertex.glsl";

    constexpr const static char* errorfs = "fragment.glsl";

};

#endif
