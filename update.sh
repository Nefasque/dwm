cd /home/nefasque/workspace/dwm-6.4/

sudo make uninstall
sudo make clean install

# remove all the stuff we don't need
rm -rf dwm
rm -rf config.h
rm -f *.o 
rm -f *.orig
rm -f *.rej
