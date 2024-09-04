@echo off

cd %~dp0
cd ..

python yourgamelib/init/init.py yourgame --clone --noTemplate --extProj lua miniaudio bullet
