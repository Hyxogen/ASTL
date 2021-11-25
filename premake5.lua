workspace "ASTL"
	architecture "x86_64"

	configurations {"Debug", "Release", "Distribution"}
	platforms {"Win64", "osx"}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"

include "ASTL"
include "Sandbox"