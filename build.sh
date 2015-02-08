make

executables/load_model

mv executables/vim_smile_plugin /usr/local/bin
mv model.yml /usr/local/include/

cp song.mp3 /usr/local/include
cp song2.mp3 /usr/local/include
cp endscript.sh /usr/local/bin

echo 'alias vim="sh /usr/local/bin/startscript.sh"' >> ~/.bashrc

echo ":command S w | !sh /usr/local/bin/endscript.sh" >> ~/.vimrc
echo ":command Q q | !killall afplay" >> ~/.vimrc
echo ":cabbrev w S" >> ~/.vimrc

echo 'alias sadness="killall afplay"' >> ~/.bashrc

source ~/.bashrc

