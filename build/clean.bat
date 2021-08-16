echo "start clean DongLiProject"
cd ..
del DongLiProject.sln

echo "start clean application"
cd application/build
call clean.bat
cd ..
cd ..

echo "start clean src"
cd src/build
call clean.bat
cd ..
cd ..

echo "end clean DongLiProject"