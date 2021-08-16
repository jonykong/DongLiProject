@echo on
cd ..
qmake -spec win32-msvc -r -tp vc DongLiProject.pro
cd build
@pause
