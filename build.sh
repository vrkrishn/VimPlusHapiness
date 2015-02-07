make

executables/load_model

mv executables/vim_smile_plugin /usr/local/bin
mv model.yml /usr/local/include/

echo "alias VIM vim_smile_plugin /usr/local/include/model.yml; vim" >> ~/.bashrc
source ~/.bashrc

echo ":command S w | !vim_smile_plugin /usr/local/include/model.yml" >> ~/.vimrc
echo ":cabbrev w S" >> ~/.vimrc
