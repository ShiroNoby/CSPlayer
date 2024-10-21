build 

    cmake ..
    cmake --build . --config release
    cmake --install . --config release --prefix "install_dir"
    
clear build

for work player, need to

    install to "install_dir"
    coppy elements and sound dir to "install_dir"
    coppy CSPlayer from source_dir/bin to "install_dir"/bin
