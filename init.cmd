@echo off

cd %~dp0
cd ..

python yourgamelib/init.py yourgame --noStub --clone --extProj lua miniaudio bullet
