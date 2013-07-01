#!/bin/sh
as2transitionPath="./as2transition/src/as2transition"
cplus2asp_binPath="./cplus2asp.bin/build/cplus2asp.bin"
cplus2aspDir="./cplus2asp/src"
f2lpPath="./f2lp/src/f2lp"
normal2incPath="./normal2inc/src/normal2inc"

if [ $# -lt 1 ]
then
    installBaseDir="/usr/local"
else
    installBaseDir="$1"
fi
#installBaseDir="/usr/local"
#installBaseDir="."

if [ ! -d "$installBaseDir/bin/" ]; then
    mkdir -p $installBaseDir/bin/
fi

if [ ! -d "$installBaseDir/lib/" ]; then
    mkdir -p $installBaseDir/lib
fi

echo "Installing as2transition..."
cp $as2transitionPath "$installBaseDir/bin/"

echo "Installing cplus2asp.bin..."
cp $cplus2asp_binPath "$installBaseDir/bin/"

echo "Installing normal2inc..."
cp $normal2incPath "$installBaseDir/bin/"

echo "Installing cplus2asp..."
rm -r "$installBaseDir/lib/cplus2asp" 2>/dev/null
mkdir "$installBaseDir/lib/cplus2asp"

cp "$cplus2aspDir/cplus2asp" "$installBaseDir/lib/cplus2asp/"
cp "$cplus2aspDir/cplus2asp_std.f2lp" "$installBaseDir/lib/cplus2asp/"
cp "$cplus2aspDir/cplus2asp_additive.f2lp" "$installBaseDir/lib/cplus2asp/"
cp "$cplus2aspDir/cplus2asp_macro.f2lp" "$installBaseDir/lib/cplus2asp/"

cp "$cplus2aspDir/cplus2asp_base.sh" "$installBaseDir/bin/cplus2asp"
echo "$installBaseDir/lib/cplus2asp/cplus2asp \"\$@\"" >> "$installBaseDir/bin/cplus2asp"

echo "Installing f2lp..."
cp $f2lpPath "$installBaseDir/bin/"

echo "Done!"

echo "You Must Add \"$installBaseDir/bin\" in your \$PATH before you can run 'cplus2asp'"
echo "You can run \"echo export PATH=\$PATH:$installBaseDir/bin >> ~/.bashrc\" to do this"
