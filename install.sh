sudo cp pythonize.hpp /usr/local/include/pythonize
sudo mkdir -p /usr/local/include/pythonized
for i in pythonized/*.hpp; do sudo cp "$i" /usr/local/include/"${i::-4}"; done
for i in /usr/local/include/pythonize /usr/local/include/pythonized/*;
	do sudo sed -i 's/#include "\(.*\).hpp"/#include "\1"/g' $i; done
