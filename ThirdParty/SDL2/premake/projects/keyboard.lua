-- Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>
--
-- This software is provided 'as-is', without any express or implied
-- warranty.  In no event will the authors be held liable for any damages
-- arising from the use of this software.
--
-- Permission is granted to anyone to use this software for any purpose,
-- including commercial applications, and to alter it and redistribute it
-- freely.
--
-- Meta-build system using premake created and maintained by
-- Benjamin Henning <b.henning@digipen.edu>

--[[
keyboard.lua

	This file defines the keyboard demo project for iOS. This project is only
	compatible on iOS and depends on SDL2. It is a windowed application.
]]

SDL_project "keyboard"
	SDL_kind "WindowedApp"
	SDL_os "ios"
	SDL_language "C"
	SDL_sourcedir "../Xcode-iOS/Demos"
	SDL_projectLocation "Demos"
	SDL_projectDependencies { "SDL2" }
	SDL_files { "/src/common.*", "/src/keyboard.*", "/Info.plist", "/data/bitmapfont/kromasky_16x16.bmp" }