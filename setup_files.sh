#!/bin/bash

CURRENT_DIR=$(pwd)
PREMAKE_DIR="./Vendor/premake"
PREMAKE_EXEC_OSX="${PREMAKE_DIR}/bin/release/premake5"
PREMAKE_EXEC_LINUX="${PREMAKE_DIR}/bin/release/premake5"
PREMAKE_EXEC_WIN="${PREMAKE_DIR}/bin/release/premake5.exe"

GenerateOSXFiles() {
	"$PREMAKE_EXEC_OSX" gmake2
}

GenerateWinFiles() {
	"$PREMAKE_EXEC_WIN" vs2022
}

GenerateLinuxFiles() {
	"$PREMAKE_EXEC_LINUX" gmake2
}

git submodule update --init

if [ "$1" == "osx" ]
then
	if [[ -f "$PREMAKE_EXEC_OSX" ]]
	then
		GenerateOSXFiles
	else
		make -C "$PREMAKE_DIR" -f Bootstrap.mak osx
		GenerateOSXFiles
	fi
elif [ "$1" == "win" ]
then
	if [[ -f "$PREMAKE_EXEC_WIN" ]]
	then
		GenerateWinFiles
	else
		make -C "$PREMAKE_DIR" -f Bootstrap.mak windows
		GenerateWinFiles
	fi
elif [ "$1" == "linux" ]
then
	if [[ -f "$PREMAKE_EXEC_LINUX" ]]
	then
		GenerateLinuxFiles
	else
		make -C "$PREMAKE_DIR" -f Bootstrap.mak linux
		GenerateLinuxFiless
	fi
else
	echo "Unkown platform!"
fi