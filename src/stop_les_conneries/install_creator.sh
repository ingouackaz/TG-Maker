#!/bin/sh
#passer un unique .cpp (avec headers utilisateurs en dur, seuls les headers systeme/SFML sont #include <>), cela genere un "./installatorz" qui compile et installe votre jeu
# --> vous aussi faites les malins avec votre installatorz! (note: installatorz en majuscule se dit INSTALLATOTZ et non INSTALLATORZ)
#le fichier template.do_not_alter est requis

out="./my_install"
echo "La notice est dans le script"
echo "Gzipping..."
cp $1 ".tmp"
gzip ".tmp" 
echo "Finalizing..."
cp template.do_not_alter $out
base64 ".tmp.gz" >> $out
chmod +x $out
echo "Cleaning up..."
rm -f ".tmp.gz"
echo "Voila"
