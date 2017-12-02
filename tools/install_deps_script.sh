
echo "INSTALLING DEPENDENCIES FOR UBUNTU"

echo "Installing glew ********************"
wget "https://glew"
unzip glew
cd  glew
make
sudo make install

echo "Installing glfw ********************"
wget "https://glfw"
unzip glfw
cd  glfw
cmake .
make
sudo make install

echo "Installing glm ********************"
wget "https://glfm"
unzip glfm
cd  glfm
cmake .
make
sudo make install